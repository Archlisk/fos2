; Exceptions
extern divide_by_zero_isr
extern debug_isr
extern non_maskable_interrupt_isr
extern breakpoint_isr
extern overflow_isr
extern bound_range_exceeded_isr
extern invalid_opcode_isr
extern device_not_available_isr
extern double_fault_isr
extern coprocessor_segment_overrun_isr
extern invalid_tss_isr
extern segment_not_present_isr
extern stack_segment_fault_isr
extern general_protection_fault_isr
extern page_fault_isr

extern x87_float_exception_isr
extern alignment_check_isr
extern machine_check_isr
extern simd_float_exception_isr
extern virtualization_exception_isr

extern security_exception_isr


; Hardware IRQs (PIC1)
extern pit_isr
extern ps2_keyboard_isr
extern cascade_isr
extern com2_isr
extern com1_isr
extern lpt2_isr
extern floppy_isr
extern lpt1_isr

; Hardware IRQs (PIC2)
extern cmos_clock_isr
extern legacy_scsi_isr
extern scsi2_isr
extern scsi1_isr
extern ps2_mouse_isr
extern fpu_isr
extern primary_ata_isr
extern secondary_ata_isr



; Exceptions
global divide_by_zero_isr_asm
global debug_isr_asm
global non_maskable_interrupt_isr_asm
global breakpoint_isr_asm
global overflow_isr_asm
global bound_range_exceeded_isr_asm
global invalid_opcode_isr_asm
global device_not_available_isr_asm
global double_fault_isr_asm
global coprocessor_segment_overrun_isr_asm
global invalid_tss_isr_asm
global segment_not_present_isr_asm
global stack_segment_fault_isr_asm
global general_protection_fault_isr_asm
global page_fault_isr_asm

global x87_float_exception_isr_asm
global alignment_check_isr_asm
global machine_check_isr_asm
global simd_float_exception_isr_asm
global virtualization_exception_isr_asm

global security_exception_isr_asm


; Hardware IRQs (PIC1)
global pit_isr_asm
global ps2_keyboard_isr_asm
global cascade_isr_asm
global com2_isr_asm
global com1_isr_asm
global lpt2_isr_asm
global floppy_isr_asm
global lpt1_isr_asm

; Hardware IRQs (PIC2)
global cmos_clock_isr_asm
global legacy_scsi_isr_asm
global scsi2_isr_asm
global scsi1_isr_asm
global ps2_mouse_isr_asm
global fpu_isr_asm
global primary_ata_isr_asm
global secondary_ata_isr_asm



; Exceptions
divide_by_zero_isr_asm:
	pusha
	call divide_by_zero_isr
	popa
	iret

debug_isr_asm:
	pusha
	call debug_isr
	popa
	iret

non_maskable_interrupt_isr_asm:
	pusha
	call non_maskable_interrupt_isr
	popa
	iret

breakpoint_isr_asm:
	pusha
	call breakpoint_isr
	popa
	iret

overflow_isr_asm:
	pusha
	call overflow_isr
	popa
	iret

bound_range_exceeded_isr_asm:
	pusha
	call bound_range_exceeded_isr
	popa
	iret

invalid_opcode_isr_asm:
	pusha
	call invalid_opcode_isr
	popa
	iret

device_not_available_isr_asm:
	pusha
	call device_not_available_isr
	popa
	iret

double_fault_isr_asm:
	pusha
	call double_fault_isr
	popa
	iret

coprocessor_segment_overrun_isr_asm:
	pusha
	call coprocessor_segment_overrun_isr
	popa
	iret

invalid_tss_isr_asm:
	pusha
	call invalid_tss_isr
	popa
	iret

segment_not_present_isr_asm:
	pusha
	call segment_not_present_isr
	popa
	iret

stack_segment_fault_isr_asm:
	pusha
	call stack_segment_fault_isr
	popa
	iret

general_protection_fault_isr_asm:
	pusha
	call general_protection_fault_isr
	popa
	iret

page_fault_isr_asm:
	pusha
	call page_fault_isr
	popa
	iret



x87_float_exception_isr_asm:
	pusha
	call x87_float_exception_isr
	popa
	iret

alignment_check_isr_asm:
	pusha
	call alignment_check_isr
	popa
	iret

machine_check_isr_asm:
	pusha
	call machine_check_isr
	popa
	iret

simd_float_exception_isr_asm:
	pusha
	call simd_float_exception_isr
	popa
	iret

virtualization_exception_isr_asm:
	pusha
	call virtualization_exception_isr
	popa
	iret



security_exception_isr_asm:
	pusha
	call security_exception_isr
	popa
	iret





; Hardware IRQs (PIC1)
pit_isr_asm:
	pusha
	call pit_isr
	popa
	iret

ps2_keyboard_isr_asm:
	pusha
	call ps2_keyboard_isr
	popa
	iret

cascade_isr_asm:
	pusha
	call cascade_isr
	popa
	iret

com2_isr_asm:
	pusha
	call com2_isr
	popa
	iret

com1_isr_asm:
	pusha
	call com1_isr
	popa
	iret

lpt2_isr_asm:
	pusha
	call lpt2_isr
	popa
	iret

floppy_isr_asm:
	pusha
	call floppy_isr
	popa
	iret

lpt1_isr_asm:
	pusha
	call lpt1_isr
	popa
	iret


; Hardware IRQs (PIC2)
cmos_clock_isr_asm:
	pusha
	call cmos_clock_isr
	popa
	iret

legacy_scsi_isr_asm:
	pusha
	call legacy_scsi_isr
	popa
	iret

scsi2_isr_asm:
	pusha
	call scsi2_isr
	popa
	iret

scsi1_isr_asm:
	pusha
	call scsi1_isr
	popa
	iret

ps2_mouse_isr_asm:
	pusha
	call ps2_mouse_isr
	popa
	iret

fpu_isr_asm:
	pusha
	call fpu_isr
	popa
	iret

primary_ata_isr_asm:
	pusha
	call primary_ata_isr
	popa
	iret

secondary_ata_isr_asm:
	pusha
	call secondary_ata_isr
	popa
	iret

