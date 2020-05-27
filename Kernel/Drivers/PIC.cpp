#include <Drivers/PIC.h>

#include <ASM.h>

#define PIC1_COMMAND	0x20
#define PIC1_DATA		0x21
#define PIC2_COMMAND	0xA0
#define PIC2_DATA		0xA1

#define PIC_EOI 0x20

#define ICW1_ICW4	0x01		/* ICW4 (not) needed */
#define ICW1_SINGLE	0x02		/* Single (cascade) mode */
#define ICW1_INTERVAL4	0x04		/* Call address interval 4 (8) */
#define ICW1_LEVEL	0x08		/* Level triggered (edge) mode */
#define ICW1_INIT	0x10		/* Initialization - required! */
 
#define ICW4_8086	0x01		/* 8086/88 (MCS-80/85) mode */
#define ICW4_AUTO	0x02		/* Auto (normal) EOI */
#define ICW4_BUF_SLAVE	0x08		/* Buffered mode/slave */
#define ICW4_BUF_MASTER	0x0C		/* Buffered mode/master */
#define ICW4_SFNM	0x10		/* Special fully nested (not) */

using namespace Kernel;

void PIC::remap(u8 offset1, u8 offset2) {
	u8 mask1 = IO::read_b(PIC1_DATA);
	u8 mask2 = IO::read_b(PIC2_DATA);
	
	IO::write_b(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);
	IO::wait();
	IO::write_b(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
	IO::wait();
	
	IO::write_b(PIC1_DATA, offset1);
	IO::wait();
	IO::write_b(PIC2_DATA, offset2);
	IO::wait();
	
	IO::write_b(PIC1_DATA, 4);
	IO::wait();
	IO::write_b(PIC2_DATA, 2);
	IO::wait();
	
	IO::write_b(PIC1_DATA, ICW4_8086);
	IO::wait();
	IO::write_b(PIC2_DATA, ICW4_8086);
	IO::wait();
	
	IO::write_b(PIC1_DATA, mask1);
	IO::write_b(PIC2_DATA, mask2);
}

void PIC::mask_irq(u8 irq) {
	u16 port;
    u8 value;
 
    if(irq < 8)
        port = PIC1_DATA;
	else {
        port = PIC2_DATA;
        irq -= 8;
    }
    
    value = IO::read_b(port) | (1 << irq);
    IO::write_b(port, value);
}

void PIC::unmask_irq(u8 irq) {
	u16 port;
    u8 value;
 
    if(irq < 8)
        port = PIC1_DATA;
    else {
        port = PIC2_DATA;
        irq -= 8;
    }
    
    value = IO::read_b(port) & ~(1 << irq);
    IO::write_b(port, value);
}

void PIC::eoi(u8 irq) {
	if(irq >= 8)
		IO::write_b(PIC2_COMMAND, PIC_EOI);
 
	IO::write_b(PIC1_COMMAND, PIC_EOI);
}

void PIC::disable() {
	IO::write_b(PIC1_DATA, 0xFF);
	IO::write_b(PIC2_DATA, 0xFF);
}
