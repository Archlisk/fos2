#include <Interrupts.h>
#include <TTY.h>

extern "C" void divide_by_zero_isr() {
	out << "ERROR: DIVIDE BY ZERO\n";
}

extern "C" void debug_isr() {
	out << "ERROR: DEBUG\n";
}

extern "C" void non_maskable_interrupt_isr() {
	out << "ERROR: NON MASKABLE INTERRUPT\n";
}

extern "C" void breakpoint_isr() {
	out << "ERROR: BREAKPOINT\n";
}

extern "C" void overflow_isr() {
	out << "ERROR: OVERFLOW\n";
}

extern "C" void bound_range_exceeded_isr() {
	out << "ERROR: BOUND RANGE EXCEEDED\n";
}

extern "C" void invalid_opcode_isr() {
	out << "ERROR: INVALID OPCODE\n";
}

extern "C" void device_not_available_isr() {
	out << "ERROR: DEVICE NOT AVAILABLE\n";
}

extern "C" void double_fault_isr() {
	out << "ERROR: DOUBLE FAULT\n";
}

extern "C" void coprocessor_segment_overrun_isr() {
	out << "ERROR: COPROCESSOR SEGMENT OVERRUN\n";
}

extern "C" void invalid_tss_isr() {
	out << "ERROR: INVALID TSS\n";
}

extern "C" void segment_not_present_isr() {
	out << "ERROR: SEGMENT NOT PRESENT\n";
}

extern "C" void stack_segment_fault_isr() {
	out << "ERROR: SEGMENT FAULT\n";
}

extern "C" void general_protection_fault_isr() {
	out << "ERROR: GENERAL PROTECTION FAULT\n";
	while (true) {}
}

extern "C" void page_fault_isr() {
	out << "ERROR: PAGE FAULT\n";
}

extern "C" void x87_float_exception_isr() {
	out << "ERROR: X87 FLOAT EXCEPTION\n";
}

extern "C" void alignment_check_isr() {
	out << "ERROR: ALIGNMENT CHECK\n";
}

extern "C" void machine_check_isr() {
	out << "ERROR: MACHINE CHECK\n";
}

extern "C" void simd_float_exception_isr() {
	out << "ERROR: SIMD FLOAT EXCEPTION\n";
}

extern "C" void virtualization_exception_isr() {
	out << "ERROR: VIRTUALIZATION EXCEPTION\n";
}

extern "C" void security_exception_isr() {
	out << "ERROR: SECURITY EXCEPTION\n";
}

