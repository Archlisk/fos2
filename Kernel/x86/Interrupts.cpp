#include <Interrupts.h>
#include <ASM.h>

#include <TTY.h>

using namespace Kernel;

#include <Drivers/PIT.h>

extern "C" 
void pit_isr() {
	PIT::on_tick();
	PIC::eoi(0);
}

extern "C" 
void ps2_keyboard_isr() {
	IO::read_b(0x60);
	PIC::eoi(1);
}

extern "C" 
void cascade_isr() {
	PIC::eoi(2);
}

extern "C" 
void com2_isr() {
	PIC::eoi(3);
}

extern "C" 
void com1_isr() {
	PIC::eoi(4);
}

extern "C" 
void lpt2_isr() {
	PIC::eoi(5);
}

extern "C" 
void floppy_isr() {
	PIC::eoi(6);
}

extern "C" 
void lpt1_isr() {
	PIC::eoi(7);
}

extern "C" 
void cmos_clock_isr() {
	PIC::eoi(8);
}

extern "C" 
void legacy_scsi_isr() {
	PIC::eoi(9);
}

extern "C" 
void scsi2_isr() {
	PIC::eoi(10);
}

extern "C" 
void scsi1_isr() {
	PIC::eoi(11);
}

extern "C" 
void ps2_mouse_isr() {
	PIC::eoi(12);
}

extern "C" 
void fpu_isr() {
	PIC::eoi(13);
}

extern "C" 
void primary_ata_isr() {
	PIC::eoi(14);
}

extern "C" 
void secondary_ata_isr() {
	PIC::eoi(15);
}
