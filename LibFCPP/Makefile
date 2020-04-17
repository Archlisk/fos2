LIB = LibFCPP.a

SOURCES_CPP = \
	      Memory/copy.cpp

INCLUDE_DIRS = \
	       LibFCPP/Include

ASM_FLAGS += -felf32
CPP_FLAGS += -ffreestanding -fno-exceptions -fno-rtti -Wall -Wextra -Wno-pointer-arith -m32
LNK_FLAGS += -nostdlib -m elf_i386

include ../Makefile.common
