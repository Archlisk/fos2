[BITS 16]

SECTION .data
	drive_read_error_str: db "Unknown drive read error", 0x00

	dap:
		.size:		db 0x10
		db 0
		.sectors:	dw 0x00
		.pointer:	dd 0x00
		.lba:		dq 0x00


SECTION .text

drive_read_error:
	mov si, drive_read_error_str
	call printstr
	cli
	hlt

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

	jc drive_read_error

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

	jc drive_read_error

	pop si
	pop ax
	ret

