ARCH = x86

OUT = Kernel.bin

SOURCES_CPP += \
	       ../LibFCPP/Memory/copy.cpp \
	       ../LibFCPP/Memory/set.cpp \
	       ../LibFCPP/Memory/alloc.cpp \
	       ../LibFCPP/Memory/free.cpp \
	       ../LibFCPP/Array.cpp \
	       ../LibFCPP/Console.cpp \
	       ../LibFCPP/String.cpp \
	       $(ARCH)/Kernel.cpp \
	       $(ARCH)/Paging.cpp \
	       $(ARCH)/Drivers/GDT.cpp \
	       $(ARCH)/Drivers/IDT.cpp \
	       $(ARCH)/Interrupts.cpp \
	       $(ARCH)/Exceptions.cpp \
	       Drivers/PIT.cpp \
	       Drivers/PIC.cpp \
	       Drivers/Terminal.cpp \
	       Heap.cpp

SOURCES_ASM += \
	       $(ARCH)/Boot.asm \
	       $(ARCH)/Interrupts_asm.asm

INCLUDE_DIRS += \
		Kernel/Include \
		Kernel/$(ARCH)/Include \
		LibFCPP/Include
		
AUTO_INCLUDE += \
		LibFCPP/Include/FCPPTypes.h

ASM_FLAGS += -felf32
CPP_FLAGS += -ffreestanding -fno-exceptions -fno-rtti -Wall -Wextra -Wno-pointer-arith -m32 -std=c++20 -D KERNEL
LNK_FLAGS += -T linker.ld -nostdlib -m32 -lgcc

include ../Makefile.common	
