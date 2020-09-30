[BITS 16]

SECTION .text
	gdt:
		dq 0x00
	.code:
		dw 0xFFFF
		dw 0x00
		db 0x00
		db 0b10011010
		db 0b11001111
		db 0x00
	.data:
		dw 0xFFFF
		dw 0x00
		db 0x00
		db 0b10010010
		db 0b11001111
		db 0x00
	.end:

	.desc:
		dw .end - gdt
		dd gdt

	GDT_CODE_SEG equ .code - gdt
	GDT_DATA_SEG equ .data - gdt

gdt_load_tmp:
	lgdt [gdt.desc]
	ret
