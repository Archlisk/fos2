LIB = LibFC.a

SOURCES_CPP += \
	      Memory/copy.cpp \
	      Heap/Heap.cpp

INCLUDE_DIRS += \
	       LibFC/Include

AUTO_INCLUDE += \
		   LibFC/Include/FCTypes.h

ASM_FLAGS += -felf32
CPP_FLAGS += -ffreestanding -fno-exceptions -fno-rtti -Wall -Wextra -Wno-pointer-arith -m32 -std=c++20
LNK_FLAGS += -nostdlib -m elf_i386

include ../Makefile.common
