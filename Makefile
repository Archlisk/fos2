BIN = ./bin

DIRS += \
	Bootloader \
	Kernel \
	Tools

all:
	@if grub-file --is-x86-multiboot Bin/Kernel.bin; then \
		echo Multiboot confirmed!; \
	else \
		echo No multiboot header found; \
	fi
	
	-@mkdir Bin
	-@mkdir Bin/fsdir
	@cp Bin/Kernel.bin Bin/fsdir/System/Kernel.bin
	@cp Bin/Stage2.bin Bin/fsdir/System/Stage2.bin
	
	-@rm fos2.img
	-@touch fos2.img
	Bin/mkfsimg -o fos2.img -b Bin/Bootloader.bin Bin/fsdir/*

run: all
	@qemu-system-i386 -drive format=raw,file=fos2.img -soundhw pcspk
	
clean:
	-rm -rf Bin/isodir Bin/Kernel.bin

include Makefile.dirs
