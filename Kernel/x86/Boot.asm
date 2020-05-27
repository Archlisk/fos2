
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
		
	global load_idt_asm
	load_idt_asm:
		mov eax, [esp + 4]
		mov [.idtr + 2], eax
		mov ax, [esp + 8]
		mov [.idtr], ax
		lidt [.idtr]
		
		ret
		
		.idtr:
			dw 0
			dd 0
	
	global load_gdt_asm
	load_gdt_asm:
		mov eax, [esp + 4]
		mov [.gdtr + 2], eax
		mov ax, [esp + 8]
		mov [.gdtr], ax
		lgdt [.gdtr]
		
		jmp 0x08:.reload_segments
		.reload_segments:
			mov ax, 0x10
			mov ds, ax
			mov es, ax
			mov fs, ax
			mov gs, ax
			mov ss, ax
		
		ret

		.gdtr:
			dw 0
			dd 0
