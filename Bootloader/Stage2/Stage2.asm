[BITS 16]

SECTION .entry
	jmp start


%include "BIOS_String.asm"
%include "Filesystem.asm"
%include "A20.asm"
%include "GDT.asm"


SECTION .text

global start
start:
	mov [stage2_blocks], ax
	mov [stage2_addr], bx
	mov [fsvd_addr], cx
	mov [boot_drive], dl

	mov sp, stack_top

	; Load the fsvd from stage 1
	mov ax, [fsvd_addr]
	mov dl, [boot_drive]
	call fs_load_fsvd

	; Multiply the stage2 blocks by 512 to get the size in bytes
	mov ax, [stage2_blocks]
	xor dx, dx
	mov cx, 512
	mul cx
	mov [stage2_bytes], ax

	; Add the address of the 2nd stage to find a free address
	add ax,	[stage2_addr]
	mov [kernel_addr], ax

	; Load the kernel
	mov si, kernel_path
	call fs_load_file
	mov [kernel_blocks], ax

	; Multiply the kernel blocks by 512 to get the size in bytes
	xor dx, dx
	mov cx, 512
	mul cx
	mov [kernel_bytes], ax

	; Enable A20 line
	call a20_enable

	; Load a temporary GDT
	call gdt_load_tmp

	cli

	; Enable protected mode
	mov eax, cr0
	or eax, 1
	mov cr0, eax

	; Jump to 32 bit code
	jmp GDT_CODE_SEG:protected_mode

[BITS 32]
protected_mode:
	mov esp, stack_top

	push dword [kernel_bytes]
	push dword [kernel_addr]
	extern entry
	call entry

	jmp eax

	.halt:
		cli
		hlt
		jmp .halt


SECTION .data
	kernel_path: db "System/Kernel.bin", 0x00

	boot_drive: db 0

	fsvd_addr: dw 0

	stage2_addr:	dd 0
	stage2_blocks:	dd 0
	stage2_bytes:	dd 0

	kernel_addr:	dd 0
	kernel_blocks:	dd 0
	kernel_bytes:	dd 0

	stack_bottom:
		times 256 db 0
	stack_top:
