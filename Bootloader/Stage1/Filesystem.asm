%include "BIOS_Drive.asm"


struc FS_VolumeDescriptor
	fsvd_signature		resb 8
	fsvd_version_major	resb 1
	fsvd_version_minor	resb 1

	fsvd_vol_name		resb 24
	fsvd_os_name		resb 16

	fsvd_block_size		resb 4

	fsvd_vol_start_lba	resb 8
	fsvd_vol_end_lba	resb 8

	fsvd_root_dir_block	resb 8

	FSVD_SIZE equ $
endstruc


struc FS_DirectoryDescriptor
	fsdd_entries		resb 4
	fsdd_start_block	resb 8
	fsdd_next_block		resb 8

	FSDD_SIZE equ $
endstruc


struc FS_DirectoryEntryDescriptor
	fsded_type	resb 1
	fsded_block	resb 8
	fsded_name	resb 24

	FSDED_SIZE equ $

	FSDED_TYPE_FILE			equ 0
	FSDED_TYPE_DIR			equ 1
endstruc


struc FS_FileDescriptor
	fsfd_blocks			resb 8
	fsfd_start_block	resb 8
	fsfd_next_block		resb 8

	FSFD_SIZE equ $
endstruc


fsvd_ptr: dw 0
fs_drive: db 0


fs_load_fsvd:
	mov [fsvd_ptr], ax
	mov [fs_drive], dl
	ret


cmp_filename:
	push si
	push bx

	.loop:
		mov al, [bx]
		cmp [si], al
		je .skip

		cmp byte [si], '/'
		jne .is_neq
		cmp al, 0
		jne .is_neq

	.skip:
		cmp byte [si], 0
		je .is_eq
		cmp byte [si], '/'
		je .is_eq

		inc bx
		inc si
		jmp .loop

	.is_eq:
		mov ax, 1
		jmp .end

	.is_neq:
		mov ax, 0
		jmp .end

	.end:

	pop bx
	pop si
	ret


len_filename:
	push si
	xor ax, ax

	.loop:
		cmp byte [si], 0
		je .end
		cmp byte [si], '/'
		je .end
		inc si
		inc ax
		jmp .loop

	.end:

	pop si
	ret


file_not_found_error:
	mov si, .error_str
	call printstr
	cli
	hlt
	.error_str: db "File not found", 0x00


fs_load_file:
	push ebx
	push cx
	push si
	push bp

	mov bx, [fsvd_ptr]
	mov ebx, [bx + fsvd_root_dir_block]
	call read_sector

	.loop:
		xor ebx, ebx
		mov bx, ax
		mov cx, [bx + fsdd_entries]
		mov ebx, [bx + fsdd_start_block]
		call read_sector

		mov bx, ax
		.cmp_loop:
			cmp cx, 0
			jle file_not_found_error
			dec cx

			push ax
			add bx, fsded_name
			call cmp_filename
			sub bx, fsded_name
			cmp ax, 0
			pop ax
			jne .cmp_end

			add bx, FSDED_SIZE
			jmp .cmp_loop
		.cmp_end:

	push ax
	call len_filename
	add si, ax
	pop ax

	cmp byte [si], 0
	je .end

	mov cl, [bx + fsded_type]
	cmp cl, FSDED_TYPE_DIR
	jne file_not_found_error

	mov ebx, [bx + fsded_block]
	call read_sector

	inc si
	jmp .loop

	.end:


	mov cl, [bx + fsded_type]
	cmp cl, FSDED_TYPE_FILE
	jne file_not_found_error

	mov ebx, [bx + fsded_block]
	call read_sector

	xor ebx, ebx
	mov bx, ax
	mov cx, [bx + fsfd_blocks]
	mov ebx, [bx + fsfd_start_block]
	call read_sectors

	mov ax, cx

	pop bp
	pop si
	pop cx
	pop ebx
	ret
