#pragma once

#include <Drivers/IDT.h>
#include <Drivers/PIC.h>
#include <Drivers/IDT.h>

#include <ASM.h>

#define PIC1_IRQ_OFFSET 0x20
#define PIC2_IRQ_OFFSET (PIC1_IRQ_OFFSET + 0x8)

#define IRQ_PIT				(PIC1_IRQ_OFFSET + 0)
#define IRQ_PS2_KEYBOARD	(PIC1_IRQ_OFFSET + 1)
#define IRQ_CASCADE			(PIC1_IRQ_OFFSET + 2)
#define IRQ_COM2			(PIC1_IRQ_OFFSET + 3)
#define IRQ_COM1			(PIC1_IRQ_OFFSET + 4)
#define IRQ_LPT2			(PIC1_IRQ_OFFSET + 5)
#define IRQ_FLOPPY			(PIC1_IRQ_OFFSET + 6)
#define IRQ_LPT1			(PIC1_IRQ_OFFSET + 7)

#define IRQ_CMOS_CLOCK		(PIC2_IRQ_OFFSET + 0)
#define IRQ_LEGACY_SCSI		(PIC2_IRQ_OFFSET + 1)
#define IRQ_SCSI2			(PIC2_IRQ_OFFSET + 2)
#define IRQ_SCSI1			(PIC2_IRQ_OFFSET + 3)
#define IRQ_PS2_MOUSE		(PIC2_IRQ_OFFSET + 4)
#define IRQ_FPU				(PIC2_IRQ_OFFSET + 5)
#define IRQ_PRIMARY_ATA		(PIC2_IRQ_OFFSET + 6)
#define IRQ_SECONDARY_ATA	(PIC2_IRQ_OFFSET + 7)

namespace Kernel {
namespace Interrupts {
// NASM
// Exceptions
extern "C" void divide_by_zero_isr_asm();				// 0
extern "C" void debug_isr_asm();						// 1
extern "C" void non_maskable_interrupt_isr_asm();		// 2
extern "C" void breakpoint_isr_asm();					// 3
extern "C" void overflow_isr_asm();						// 4
extern "C" void bound_range_exceeded_isr_asm();			// 5
extern "C" void invalid_opcode_isr_asm();				// 6
extern "C" void device_not_available_isr_asm();			// 7
extern "C" void double_fault_isr_asm();					// 8
extern "C" void coprocessor_segment_overrun_isr_asm();	// 9
extern "C" void invalid_tss_isr_asm();					// 10
extern "C" void segment_not_present_isr_asm();			// 11
extern "C" void stack_segment_fault_isr_asm();			// 12
extern "C" void general_protection_fault_isr_asm();		// 13
extern "C" void page_fault_isr_asm();					// 14
														// 15 - RESERVED
extern "C" void x87_float_exception_isr_asm();			// 16
extern "C" void alignment_check_isr_asm();				// 17
extern "C" void machine_check_isr_asm();				// 18
extern "C" void simd_float_exception_isr_asm();			// 19
extern "C" void virtualization_exception_isr_asm();		// 20
														// 21 -> 29 - RESERVED
extern "C" void security_exception_isr_asm();			// 30
														// 31 - RESERVED
// Hardware IRQs (PIC1)
extern "C" void pit_isr_asm();			// 32
extern "C" void ps2_keyboard_isr_asm();	// 33
extern "C" void cascade_isr_asm();		// 34
extern "C" void com2_isr_asm();			// 35
extern "C" void com1_isr_asm();			// 36
extern "C" void lpt2_isr_asm();			// 37
extern "C" void floppy_isr_asm();		// 38
extern "C" void lpt1_isr_asm();			// 39

// Hardware IRQs (PIC2)
extern "C" void cmos_clock_isr_asm();	// 40
extern "C" void legacy_scsi_isr_asm();	// 41
extern "C" void scsi2_isr_asm();		// 42
extern "C" void scsi1_isr_asm();		// 43
extern "C" void ps2_mouse_isr_asm();	// 44
extern "C" void fpu_isr_asm();			// 45
extern "C" void primary_ata_isr_asm();	// 46
extern "C" void secondary_ata_isr_asm();// 47


// C++
// Exceptions
extern "C" void divide_by_zero_isr();				// 0
extern "C" void debug_isr();						// 1
extern "C" void non_maskable_interrupt_isr();		// 2
extern "C" void breakpoint_isr();					// 3
extern "C" void overflow_isr();						// 4
extern "C" void bound_range_exceeded_isr();			// 5
extern "C" void invalid_opcode_isr();				// 6
extern "C" void device_not_available_isr();			// 7
extern "C" void double_fault_isr();					// 8
extern "C" void coprocessor_segment_overrun_isr();	// 9
extern "C" void invalid_tss_isr();					// 10
extern "C" void segment_not_present_isr();			// 11
extern "C" void stack_segment_fault_isr();			// 12
extern "C" void general_protection_fault_isr();		// 13
extern "C" void page_fault_isr();					// 14
													// 15 - RESERVED
extern "C" void x87_float_exception_isr();			// 16
extern "C" void alignment_check_isr();				// 17
extern "C" void machine_check_isr();				// 18
extern "C" void simd_float_exception_isr();			// 19
extern "C" void virtualization_exception_isr();		// 20
													// 21 -> 29 - RESERVED
extern "C" void security_exception_isr();			// 30
													// 31 - RESERVED

// Hardware IRQs (PIC1)
extern "C" void pit_isr();			// 32
extern "C" void ps2_keyboard_isr();	// 33
extern "C" void cascade_isr();		// 34
extern "C" void com2_isr();			// 35
extern "C" void com1_isr();			// 36
extern "C" void lpt2_isr();			// 37
extern "C" void floppy_isr();		// 38
extern "C" void lpt1_isr();			// 39

// Hardware IRQs (PIC2)
extern "C" void cmos_clock_isr();	// 40
extern "C" void legacy_scsi_isr();	// 41
extern "C" void scsi2_isr();		// 42
extern "C" void scsi1_isr();		// 43
extern "C" void ps2_mouse_isr();	// 44
extern "C" void fpu_isr();			// 45
extern "C" void primary_ata_isr();	// 46
extern "C" void secondary_ata_isr();// 47


inline void register_all(IDT& idt, u16 selector) {
	idt.entries[0] = IDT::Entry((u64)divide_by_zero_isr_asm, selector, IDT::Entry::Attributes(IDT_INTERRUPT_GATE, 3));
	idt.entries[1] = IDT::Entry((u64)debug_isr_asm, selector, IDT::Entry::Attributes(IDT_INTERRUPT_GATE, 3));
	idt.entries[2] = IDT::Entry((u64)non_maskable_interrupt_isr_asm, selector, IDT::Entry::Attributes(IDT_INTERRUPT_GATE, 3));
	idt.entries[3] = IDT::Entry((u64)breakpoint_isr_asm, selector, IDT::Entry::Attributes(IDT_INTERRUPT_GATE, 3));
	idt.entries[4] = IDT::Entry((u64)overflow_isr_asm, selector, IDT::Entry::Attributes(IDT_INTERRUPT_GATE, 3));
	idt.entries[5] = IDT::Entry((u64)bound_range_exceeded_isr_asm, selector, IDT::Entry::Attributes(IDT_INTERRUPT_GATE, 3));
	idt.entries[6] = IDT::Entry((u64)invalid_opcode_isr_asm, selector, IDT::Entry::Attributes(IDT_INTERRUPT_GATE, 3));
	idt.entries[7] = IDT::Entry((u64)device_not_available_isr_asm, selector, IDT::Entry::Attributes(IDT_INTERRUPT_GATE, 3));
	idt.entries[8] = IDT::Entry((u64)double_fault_isr_asm, selector, IDT::Entry::Attributes(IDT_INTERRUPT_GATE, 3));
	idt.entries[9] = IDT::Entry((u64)coprocessor_segment_overrun_isr_asm, selector, IDT::Entry::Attributes(IDT_INTERRUPT_GATE, 3));
	idt.entries[10] = IDT::Entry((u64)invalid_tss_isr_asm, selector, IDT::Entry::Attributes(IDT_INTERRUPT_GATE, 3));
	idt.entries[11] = IDT::Entry((u64)segment_not_present_isr_asm, selector, IDT::Entry::Attributes(IDT_INTERRUPT_GATE, 3));
	idt.entries[12] = IDT::Entry((u64)stack_segment_fault_isr_asm, selector, IDT::Entry::Attributes(IDT_INTERRUPT_GATE, 3));
	idt.entries[13] = IDT::Entry((u64)general_protection_fault_isr_asm, selector, IDT::Entry::Attributes(IDT_INTERRUPT_GATE, 3));
	idt.entries[14] = IDT::Entry((u64)page_fault_isr_asm, selector, IDT::Entry::Attributes(IDT_INTERRUPT_GATE, 3));
	idt.entries[16] = IDT::Entry((u64)x87_float_exception_isr_asm, selector, IDT::Entry::Attributes(IDT_INTERRUPT_GATE, 3));
	idt.entries[17] = IDT::Entry((u64)alignment_check_isr_asm, selector, IDT::Entry::Attributes(IDT_INTERRUPT_GATE, 3));
	idt.entries[18] = IDT::Entry((u64)machine_check_isr_asm, selector, IDT::Entry::Attributes(IDT_INTERRUPT_GATE, 3));
	idt.entries[19] = IDT::Entry((u64)simd_float_exception_isr_asm, selector, IDT::Entry::Attributes(IDT_INTERRUPT_GATE, 3));
	idt.entries[20] = IDT::Entry((u64)virtualization_exception_isr_asm, selector, IDT::Entry::Attributes(IDT_INTERRUPT_GATE, 3));
	idt.entries[31] = IDT::Entry((u64)security_exception_isr_asm, selector, IDT::Entry::Attributes(IDT_INTERRUPT_GATE, 3));
	
	idt.entries[IRQ_PIT] = IDT::Entry((u64)pit_isr_asm, selector, IDT::Entry::Attributes(IDT_INTERRUPT_GATE, 3));
	idt.entries[IRQ_PS2_KEYBOARD] = IDT::Entry((u64)ps2_keyboard_isr_asm, selector, IDT::Entry::Attributes(IDT_INTERRUPT_GATE, 3));
	idt.entries[IRQ_CASCADE] = IDT::Entry((u64)cascade_isr_asm, selector, IDT::Entry::Attributes(IDT_INTERRUPT_GATE, 3));
	idt.entries[IRQ_COM2] = IDT::Entry((u64)com2_isr_asm, selector, IDT::Entry::Attributes(IDT_INTERRUPT_GATE, 3));
	idt.entries[IRQ_COM1] = IDT::Entry((u64)com1_isr_asm, selector, IDT::Entry::Attributes(IDT_INTERRUPT_GATE, 3));
	idt.entries[IRQ_LPT2] = IDT::Entry((u64)lpt2_isr_asm, selector, IDT::Entry::Attributes(IDT_INTERRUPT_GATE, 3));
	idt.entries[IRQ_FLOPPY] = IDT::Entry((u64)floppy_isr_asm, selector, IDT::Entry::Attributes(IDT_INTERRUPT_GATE, 3));
	idt.entries[IRQ_LPT1] = IDT::Entry((u64)lpt1_isr_asm, selector, IDT::Entry::Attributes(IDT_INTERRUPT_GATE, 3));
	
	idt.entries[IRQ_CMOS_CLOCK] = IDT::Entry((u64)cmos_clock_isr_asm, selector, IDT::Entry::Attributes(IDT_INTERRUPT_GATE, 3));
	idt.entries[IRQ_LEGACY_SCSI] = IDT::Entry((u64)legacy_scsi_isr_asm, selector, IDT::Entry::Attributes(IDT_INTERRUPT_GATE, 3));
	idt.entries[IRQ_SCSI2] = IDT::Entry((u64)scsi2_isr_asm, selector, IDT::Entry::Attributes(IDT_INTERRUPT_GATE, 3));
	idt.entries[IRQ_SCSI1] = IDT::Entry((u64)scsi1_isr_asm, selector, IDT::Entry::Attributes(IDT_INTERRUPT_GATE, 3));
	idt.entries[IRQ_PS2_MOUSE] = IDT::Entry((u64)ps2_mouse_isr_asm, selector, IDT::Entry::Attributes(IDT_INTERRUPT_GATE, 3));
	idt.entries[IRQ_FPU] = IDT::Entry((u64)fpu_isr_asm, selector, IDT::Entry::Attributes(IDT_INTERRUPT_GATE, 3));
	idt.entries[IRQ_PRIMARY_ATA] = IDT::Entry((u64)primary_ata_isr_asm, selector, IDT::Entry::Attributes(IDT_INTERRUPT_GATE, 3));
	idt.entries[IRQ_SECONDARY_ATA] = IDT::Entry((u64)secondary_ata_isr_asm, selector, IDT::Entry::Attributes(IDT_INTERRUPT_GATE, 3));
}

}
}
