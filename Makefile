BIN = ./bin

DIRS += \
	Kernel \
	Tools

all:
	@if grub-file --is-x86-multiboot Bin/Kernel.bin; then \
		echo Multiboot confirmed!; \
	else \
		echo No multiboot header found; \
	fi
	
	@mkdir -p Bin/isodir/boot/grub
	@cp Bin/Kernel.bin Bin/isodir/boot/
	@cp Bin/grub.cfg Bin/isodir/boot/grub
	@grub-mkrescue -o fos2.iso Bin/isodir

run: all
	@qemu-system-x86_64 -cdrom fos2.iso	

include Makefile.dirs
