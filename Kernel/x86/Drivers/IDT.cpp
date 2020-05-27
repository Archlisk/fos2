#include <Drivers/IDT.h>

using namespace Kernel;

extern "C" void load_idt_asm(void* idt, u16 size);

void IDT::load(IDT* idt) {
	load_idt_asm(idt, sizeof(IDT));
}
