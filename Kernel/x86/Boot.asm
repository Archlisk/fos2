
MBALIGN		equ 	1 << 0
MEMINFO 	equ 	1 << 1
FLAGS 		equ	MBALIGN | MEMINFO
MAGIC 		equ	0x1BADB002
CHECKSUM	equ	-(MAGIC + FLAGS)

ALIGN 4
SECTION .multiboot
	dd MAGIC
	dd FLAGS
	dd CHECKSUM


ALIGN 16
SECTION .bss
	stack_bottom:
		resb 16384 ; 16 KiB
	stack_top:
	
ALIGN 4096
	global kernel_page_dir
	kernel_page_dir:
		resb 4096

SECTION .text
	global _start
	_start:
		mov esp, stack_top
	
		extern enter
		call enter
		
		cli
	.hang:
		hlt
		jmp .hang
	.end:
	
	global enable_paging_asm
	enable_paging_asm:
		mov eax, [esp + 4]
		mov cr3, eax
		
		mov eax, cr4
		or eax, 0x00000010
		mov cr4, eax
		
		mov eax, cr0
		or eax, 0x80000001
		mov cr0, eax
		ret
