#include <Interrupts.h>
#include <TTY.h>

extern "C" void divide_by_zero_isr() {
	out << VGA::FGColor4B::LightRed << "ERROR: DIVIDE BY ZERO\n" << VGA::FGColor4B::BrightWhite;
}

extern "C" void debug_isr() {
	out << VGA::FGColor4B::LightRed << "ERROR: DEBUG\n" << VGA::FGColor4B::BrightWhite;
}

extern "C" void non_maskable_interrupt_isr() {
	out << VGA::FGColor4B::LightRed << "ERROR: NON MASKABLE INTERRUPT\n" << VGA::FGColor4B::BrightWhite;
}

extern "C" void breakpoint_isr() {
	out << VGA::FGColor4B::LightRed << "ERROR: BREAKPOINT\n" << VGA::FGColor4B::BrightWhite;
}

extern "C" void overflow_isr() {
	out << VGA::FGColor4B::LightRed << "ERROR: OVERFLOW\n" << VGA::FGColor4B::BrightWhite;
}

extern "C" void bound_range_exceeded_isr() {
	out << VGA::FGColor4B::LightRed << "ERROR: BOUND RANGE EXCEEDED\n" << VGA::FGColor4B::BrightWhite;
}

extern "C" void invalid_opcode_isr() {
	out << VGA::FGColor4B::LightRed << "ERROR: INVALID OPCODE\n" << VGA::FGColor4B::BrightWhite;
}

extern "C" void device_not_available_isr() {
	out << VGA::FGColor4B::LightRed << "ERROR: DEVICE NOT AVAILABLE\n" << VGA::FGColor4B::BrightWhite;
}

extern "C" void double_fault_isr() {
	out << VGA::FGColor4B::LightRed << "ERROR: DOUBLE FAULT\n" << VGA::FGColor4B::BrightWhite;
}

extern "C" void coprocessor_segment_overrun_isr() {
	out << VGA::FGColor4B::LightRed << "ERROR: COPROCESSOR SEGMENT OVERRUN\n" << VGA::FGColor4B::BrightWhite;
}

extern "C" void invalid_tss_isr() {
	out << VGA::FGColor4B::LightRed << "ERROR: INVALID TSS\n" << VGA::FGColor4B::BrightWhite;
}

extern "C" void segment_not_present_isr() {
	out << VGA::FGColor4B::LightRed << "ERROR: SEGMENT NOT PRESENT\n" << VGA::FGColor4B::BrightWhite;
}

extern "C" void stack_segment_fault_isr() {
	out << VGA::FGColor4B::LightRed << "ERROR: SEGMENT FAULT\n" << VGA::FGColor4B::BrightWhite;
}

extern "C" void general_protection_fault_isr() {
	out << VGA::FGColor4B::LightRed << "ERROR: GENERAL PROTECTION FAULT\n" << VGA::FGColor4B::BrightWhite;
}

extern "C" void page_fault_isr() {
	out << VGA::FGColor4B::LightRed << "ERROR: PAGE FAULT\n" << VGA::FGColor4B::BrightWhite;
}

extern "C" void x87_float_exception_isr() {
	out << VGA::FGColor4B::LightRed << "ERROR: X87 FLOAT EXCEPTION\n" << VGA::FGColor4B::BrightWhite;
}

extern "C" void alignment_check_isr() {
	out << VGA::FGColor4B::LightRed << "ERROR: ALIGNMENT CHECK\n" << VGA::FGColor4B::BrightWhite;
}

extern "C" void machine_check_isr() {
	out << VGA::FGColor4B::LightRed << "ERROR: MACHINE CHECK\n" << VGA::FGColor4B::BrightWhite;
}

extern "C" void simd_float_exception_isr() {
	out << VGA::FGColor4B::LightRed << "ERROR: SIMD FLOAT EXCEPTION\n" << VGA::FGColor4B::BrightWhite;
}

extern "C" void virtualization_exception_isr() {
	out << VGA::FGColor4B::LightRed << "ERROR: VIRTUALIZATION EXCEPTION\n" << VGA::FGColor4B::BrightWhite;
}

extern "C" void security_exception_isr() {
	out << VGA::FGColor4B::LightRed << "ERROR: SECURITY EXCEPTION\n" << VGA::FGColor4B::BrightWhite;
}

