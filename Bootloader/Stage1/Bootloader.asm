[ORG 0x7C00]
[BITS 16]

FSVD_LBA equ 1
FSVD_LOAD_ADDR equ 0x8000

STAGE2_LOAD_ADDR equ 0x8200

start:
	mov [boot_drive], dl

	; Set video mode to 3 to clear the screen
	mov ah, 0x00
	mov al, 0x03
	int 0x10

	; Zero the segments
	xor ax, ax
	mov ds, ax
	mov es, ax
	mov ss, ax

	mov sp, [FSVD_LOAD_ADDR]

	; Load the FSVD
	mov ax, FSVD_LOAD_ADDR
	mov ebx, FSVD_LBA
	call read_sector
	call fs_load_fsvd

	; Load the second stage
	mov ax, STAGE2_LOAD_ADDR
	mov si, stage2_path
	call fs_load_file

	mov bx, STAGE2_LOAD_ADDR
	mov cx, FSVD_LOAD_ADDR
	mov dl, [boot_drive]

	jmp STAGE2_LOAD_ADDR

	cli
	hlt


%include "BIOS_String.asm"
%include "Filesystem.asm"

boot_drive: db 0

stage2_path: db "System/Stage2.bin", 0x00

; Padding
times 510 - ($ - $$) db 0
db 0x55, 0xAA
