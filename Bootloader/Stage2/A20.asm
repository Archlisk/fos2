[BITS 16]
SECTION .text

a20_kb_enable:
	push ax
	cli

	call .wait
	mov	al, 0xad
	out	0x64, al

	call .wait
	mov	al, 0xd0
	out 0x64, al

	call .wait2
	in al, 0x60
	push eax

	call .wait
	mov	al, 0xd1
	out 0x64, al

	call .wait
	pop eax
	or al, 2
	out 0x60, al

	call .wait
	mov al, 0xae
	out 0x64, al

	call .wait
	sti
	ret

	.wait:
		in al, 0x64
		test al, 2
		jnz .wait
		ret

	.wait2:
		in al, 0x64
		test al, 1
		jz .wait2
		ret
	pop ax
	ret

a20_BIOS_enable:
	push ax

	mov ax, 0x2403
	int 0x15

	jb .end
	cmp ah, 0
	jnz .end

	mov ax, 0x2401
	int 0x15

	.end:
	pop ax
	ret

a20_fast_enable:
	push ax

	in al, 0x92
	test al, 2
	jnz end
	or al, 2
	and al, 0xfe
	out 0x92, al
	end:

	pop ax
	ret

a20_io_enable:
	in al, 0xee
	ret

a20_enable:
	push ax
	push cx
	push dx

	; Return if the A20 line has been enabled
	call a20_check
	cmp ax, 0
	jne .end

	call a20_BIOS_enable

	; Return if the A20 line has been enabled
	call a20_check
	cmp ax, 0
	jne .end

	call a20_kb_enable

	; Wait for ((cx << 16) | dx) microseconds
	mov ah, 0x86
	mov cx, 0
	mov dx, 0xFFFF
	int 0x15

	; Return if the A20 line has been enabled
	call a20_check
	cmp ax, 0
	jne .end

	call a20_fast_enable

	; Wait for ((cx << 16) | dx) microseconds
	mov ah, 0x86
	mov cx, 0
	mov dx, 0xFFFF
	int 0x15

	; Return if the A20 line has been enabled
	call a20_check
	cmp ax, 0
	jne .end

	call a20_io_enable

	; Wait for ((cx << 16) | dx) microseconds
	mov ah, 0x86
	mov cx, 0
	mov dx, 0xFFFF
	int 0x15

	; Return if the A20 line has been enabled
	call a20_check
	cmp ax, 0
	jne .end

	print "Failed to enable A20 line"
	cli
	hlt

	.end:
	pop dx
	pop cx
	pop ax
	ret

a20_check:
	pushf
	push ds
	push es
	push di
	push si

	cli

	xor ax, ax ; ax = 0
	mov es, ax

	not ax ; ax = 0xFFFF
	mov ds, ax

	mov di, 0x0500
	mov si, 0x0510

	mov al, byte [es:di]
	push ax

	mov al, byte [ds:si]
	push ax

	mov byte [es:di], 0x00
	mov byte [ds:si], 0xFF

	cmp byte [es:di], 0xFF

	pop ax
	mov byte [ds:si], al

	pop ax
	mov byte [es:di], al

	mov ax, 0
	je .end

	mov ax, 1

	.end:
	pop si
	pop di
	pop es
	pop ds
	popf
	ret
