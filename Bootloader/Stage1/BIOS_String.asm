

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
