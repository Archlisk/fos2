OUT = Stage2.bin

SOURCES_CPP = \
	      Entry.cpp

SOURCES_ASM = \
	      Stage2.asm

LNK = ld

LNK_LIBS = -lgcc

CPP_FLAGS = -m32 -fno-pie -ffreestanding -nostdlib
ASM_FLAGS = -felf32
LNK_FLAGS = -ffreestanding -fno-pie -nostdlib -T linker.ld -m32

include ../../Makefile.common

