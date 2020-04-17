
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

SECTION .text
	global _start
	_start:
		mov esp, stack_top
	
		extern kernel_enter
		call kernel_enter
		
		cli
	.hang:
		hlt
		jmp .hang
	.end:
