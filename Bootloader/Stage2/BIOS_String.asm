[BITS 16]

%macro print 1
SECTION .data
	%%__str: db %1, 0x00
SECTION .text
	push si
	mov si, %%__str
	call printstr
	pop si
%endmacro


SECTION .text

putchar:
	push ax
	push bx
	push cx
	push dx

	mov ah, 0x0A
	xor bh, bh
	mov cx, 1
	int 0x10

	mov ah, 0x03
	mov bh, 0
	int 0x10

	mov ah, 0x02
	mov bh, 0
	inc dl
	int 0x10

	pop dx
	pop cx
	pop bx
	pop ax
	ret

strlen:
	push si
	xor ax, ax

	.loop:
		cmp byte [si], 0
		je .end
		inc ax
		inc si
		jmp .loop
	.end:

	pop si
	ret

revstr:
	push si
	push ax
	push bx
	push cx

	call strlen
	cmp ax, 1
	jle .end

	mov bx, ax
	add bx, si
	dec bx

	shr ax, 1

	.loop:

		mov cl, [si]
		mov ch, [bx]

		mov [bx], cl
		mov [si], ch

		inc si
		dec bx

		dec ax
		jnz .loop

	.end:
	pop cx
	pop bx
	pop ax
	pop si
	ret

printint:
	push si
	push eax
	push ecx
	push edx

	mov si, .conversion_buf

	.loop:
		cmp eax, 10
		jl .end

		xor edx, edx
		mov ecx, 10
		div ecx

		add dl, '0'
		mov [si], dl
		inc si

		jmp .loop
	.end:

	add al, '0'
	mov [si], al
	inc si

	mov byte [si], 0

	mov si, .conversion_buf
	call revstr

	call printstr

	pop edx
	pop ecx
	pop eax
	pop si
	ret

	.conversion_buf: times 32 db 0

printhex:
	push si
	push eax
	push ecx
	push edx

	mov si, .conversion_buf

	.loop:
		cmp eax, 16
		jl .end

		xor edx, edx
		mov ecx, 16
		div ecx

		cmp dl, 10
		jge .add_A
		add dl, '0'
		jmp .add_end
		.add_A
		sub dl, 10
		add dl, 'A'
		.add_end

		mov [si], dl
		inc si

		jmp .loop
	.end:

	cmp al, 10
	jge .xtern_add_A
	add al, '0'
	jmp .xtern_add_end
	.xtern_add_A
	sub al, 10
	add al, 'A'
	.xtern_add_end

	mov [si], al
	inc si

	mov byte [si], 0

	mov si, .conversion_buf
	call revstr

	call printstr

	pop edx
	pop ecx
	pop eax
	pop si
	ret

	.conversion_buf: times 32 db 0

printstr:
	push si
	push ax

	.loop:
		cmp byte [si], 0
		je .end

		mov al, [si]
		call putchar

		inc si
		jmp .loop
	.end:

	pop ax
	pop si
	ret
