//	MIT License
//	Copyright (c) 2020 Archlisk
//	Read "(Project Root)/LICENSE" for license information

#include <Drivers/VGA.h>
#include <Drivers/GDT.h>
#include <Drivers/IDT.h>
#include <Drivers/PIC.h>
#include <Drivers/PIT.h>
#include <Drivers/PCSpeaker.h>

#include <Paging.h>
#include <Interrupts.h>
#include <TTY.h>

#include <String.h>
#include <Memory.h>

#define HEAP_ADDR ((void*)(PAGE_SIZE))

using namespace Kernel;
using namespace FCPP;

extern "C" Paging::PageDir kernel_page_dir;

Terminal KernelData::tty(nullptr, 0, 0);
Heap KernelData::heap(nullptr, 0);

void kernel_main() {
	out << VGA::FGColor4B::LightGreen << "Kernel entered\n" << VGA::FGColor4B::BrightWhite; 

	while(true) {
		PIT::sleep(985);
		PCSpeaker::play(800);
		PIT::sleep(15);
		PCSpeaker::stop();
	}

	out << VGA::FGColor4B::LightRed << "Kernel exiting...\n";
}

extern "C"
void enter() {
	KernelData::heap = Heap(HEAP_ADDR, PAGE_SIZE);
	KernelData::tty = Terminal((u16*)0xB8000, 80, 25);

	kernel_page_dir.unmap_all();	// Zero all entries to remove any garbage
	kernel_page_dir.map(nullptr, nullptr);
	kernel_page_dir.map(HEAP_ADDR, HEAP_ADDR);
	Paging::enable(kernel_page_dir);
	
	GDT::Entry gdt[3] = {
		GDT::Entry(0, 0, GDT::Entry::AccessByte(1)),
		GDT::Entry(0, 0xFFFFFFFF, GDT::Entry::AccessByte(0b10011010)),
		GDT::Entry(0, 0xFFFFFFFF, GDT::Entry::AccessByte(0b10010010))
	};
	
	GDT::load(gdt, sizeof(gdt));
	
	PIC::remap(0x20, 0x28);
	
	IDT idt;
	IDT::load(&idt);
	
	Interrupts::register_all(idt, 0x8);
	
	ASM::sti();
	
	PIT::set_frequency(PIT::Channel::C0, 1000);
	
	kernel_main();
}
