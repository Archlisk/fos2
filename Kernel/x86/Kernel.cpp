//	MIT License
//	Copyright (c) 2020 Archlisk
//	Read "(Project Root)/LICENSE" for license information

#include <Drivers/Terminal.h>
#include <Drivers/VGA.h>

#include <Paging.h>
#include <Heap.h>

#include <String.h>

#define HEAP_ADDR ((void*)(PAGE_SIZE))

namespace Kernel {

extern "C" Paging::PageDir kernel_page_dir;

Terminal tty(nullptr, 0, 0);	// There is currently no way to call global constructors, 
Heap heap(nullptr, 0);			// these are only here to keep the compiler sane.

void main() {
	tty.set_color(VGA::FGColor4B::LightGreen, VGA::BGColor4B::Black);
	tty.write_str("Kernel entered\n");
	tty.set_color(VGA::FGColor4B::BrightWhite, VGA::BGColor4B::Black);
	
	tty.write_str("lol\n");
	
	tty.set_color(VGA::FGColor4B::LightRed, VGA::BGColor4B::Black);
	tty.write_str("Kernel exiting...");
}

extern "C"
void enter() {
	kernel_page_dir.unmap_all();	// Zero all entries to remove any garbage
	kernel_page_dir.map(nullptr, nullptr);
	Paging::enable(kernel_page_dir);

	kernel_page_dir.map(HEAP_ADDR, HEAP_ADDR);
	heap = Heap(HEAP_ADDR, PAGE_SIZE);
	tty = Terminal((u16*)0xB8000, 80, 25);
	
	Kernel::main();
}

}
