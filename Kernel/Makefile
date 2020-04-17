OUT = Kernel.bin

SOURCES_CPP += \
	       ../LibFCPP/Memory/copy.cpp \
	       ../LibFCPP/Memory/set.cpp \
	       Kernel.cpp \
	       Drivers/Terminal.cpp

SOURCES_ASM += \
	       Boot.asm

INCLUDE_DIRS += \
		Kernel/Include \
		LibFCPP/Include

ASM_FLAGS += -felf32
CPP_FLAGS += -ffreestanding -fno-exceptions -fno-rtti -Wall -Wextra -Wno-pointer-arith -m32
LNK_FLAGS += -T linker.ld -nostdlib -m elf_i386

include ../Makefile.common	
