ARCH = x86

OUT = Kernel.bin

SOURCES_CPP += \
	       ../LibFC/Memory/copy.cpp \
	       ../LibFC/Memory/set.cpp \
	       ../LibFC/Memory/compare.cpp \
	       $(ARCH)/Kernel.cpp \
	       $(ARCH)/Paging.cpp \
	       $(ARCH)/Drivers/GDT.cpp \
	       $(ARCH)/Drivers/IDT.cpp \
	       $(ARCH)/Interrupts.cpp \
	       $(ARCH)/Exceptions.cpp \
	       Drivers/PIT.cpp \
	       Drivers/PIC.cpp \
	       Drivers/Terminal.cpp \
	       Drivers/ACPI.cpp \
	       Drivers/PCI.cpp \
	       Drivers/PCIList.cpp \
	       Drivers/IDE.cpp \
	       Heap.cpp

SOURCES_ASM += \
	       $(ARCH)/Boot.asm \
	       $(ARCH)/Interrupts_asm.asm

INCLUDE_DIRS += \
		Kernel/Include \
		Kernel/$(ARCH)/Include \
		LibFC/Include
		
AUTO_INCLUDE += \
		LibFC/Include/FC.h

ASM_FLAGS += -felf32
CPP_FLAGS += -ffreestanding -fno-exceptions -fno-rtti -Wall -Wextra -Wno-pointer-arith -m32 -std=c++20 -D KERNEL
LNK_FLAGS += -T linker.ld -nostdlib -m32 -lgcc

include ../Makefile.common	
