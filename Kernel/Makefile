ARCH = x86

OUT = Kernel.bin

SOURCES_CPP += \
	       ../LibFCPP/Memory/copy.cpp \
	       ../LibFCPP/Memory/set.cpp \
	       $(ARCH)/Kernel.cpp \
	       $(ARCH)/Paging.cpp \
	       Drivers/Terminal.cpp \
	       Heap.cpp

SOURCES_ASM += \
	       $(ARCH)/Boot.asm

INCLUDE_DIRS += \
		Kernel/Include \
		LibFCPP/Include

ASM_FLAGS += -felf32
CPP_FLAGS += -ffreestanding -fno-exceptions -fno-rtti -Wall -Wextra -Wno-pointer-arith -m32
LNK_FLAGS += -T linker.ld -nostdlib -m32 -lgcc

include ../Makefile.common	
