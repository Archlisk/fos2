
read_sector:
	mov [dap.pointer], ax
	mov [dap.lba], ebx

	push ax
	push si

	mov ax, 1
	mov [dap.sectors], ax

	mov ah, 0x42
	mov si, dap
	int 0x13

	pop si
	pop ax
	ret




read_sectors:
	mov [dap.pointer], ax
	mov [dap.lba], ebx
	mov [dap.sectors], cx

	push ax
	push si

	mov ah, 0x42
	mov si, dap
	int 0x13

	pop si
	pop ax
	ret



dap:
	.size:		db 0x10
	db 0
	.sectors:	dw 0x00
	.pointer:	dd 0x00
	.lba:		dq 0x00
