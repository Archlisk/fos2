#include <Drivers/GDT.h>

using namespace Kernel;

extern "C" void load_gdt_asm(void* gdt, u16 size);

void GDT::load(Entry* gdt, u16 size) {
	load_gdt_asm(gdt, size);
}
