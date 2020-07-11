//	MIT License
//	Copyright (c) 2020 Archlisk
//	Read "(Project Root)/LICENSE" for license information

#include <Drivers/VGA.h>
#include <Drivers/GDT.h>
#include <Drivers/IDT.h>
#include <Drivers/PIC.h>
#include <Drivers/PIT.h>
#include <Drivers/PCSpeaker.h>
#include <Drivers/ACPI.h>
#include <Drivers/PCI.h>

#include <Paging.h>
#include <Interrupts.h>
#include <CPUID.h>
#include <TTY.h>

#define HEAP_ADDR ((void*)(PAGE_SIZE * 4))

using namespace Kernel;
using namespace FC;

extern "C" Paging::PageDir kernel_page_dir;

Terminal KernelData::tty(nullptr, 0, 0);
Heap KernelData::heap(nullptr, 0);

extern "C"
void enter() {
	// Heap
	KernelData::heap = Heap(HEAP_ADDR, PAGE_SIZE);
	
	// TTY
	KernelData::tty = Terminal((u16*)0xB8000, 80, 25);
	KernelData::tty.set_color(VGA::FGColor4B::BrightWhite);

	// SSE
	CPU::CPUInfo* cpu_info = CPU::info();
	if (!(cpu_info->sse || cpu_info->sse2 || cpu_info->sse3 || cpu_info->sse4_1 || cpu_info->sse4_2)) {
		KernelData::tty.set_color(VGA::FGColor4B::LightRed);
		out << "This CPU does not support SSE. FOS2 cannot run without this feature.\n";
		while (true)
			ASM::hlt();
	}
	CPU::enable_sse();


	// Paging
	kernel_page_dir.unmap_all();		// Zero all entries to remove any garbage
	kernel_page_dir.identity_map_all();
	Paging::enable(kernel_page_dir);
	
	// GDT
	GDT::Entry gdt[3] = {
		GDT::Entry(0, 0, GDT::Entry::AccessByte(1)),
		GDT::Entry(0, 0xFFFFFFFF, GDT::Entry::AccessByte(0b10011010)),
		GDT::Entry(0, 0xFFFFFFFF, GDT::Entry::AccessByte(0b10010010))
	};
	
	GDT::load(gdt, sizeof(gdt));
	
	// Interrupts
	PIC::remap(0x20, 0x28);
	IDT idt;
	IDT::load(&idt);
	Interrupts::register_all(idt, 0x8);
	ASM::sti();
	
	// PIT
	PIT::set_frequency(PIT::CH0, 1000);
	out << "CPU\t: " << CPU::brand_str() << '\n';
	
	// ACPI
	ACPI& acpi = ACPI::get();
	
	// PCI
	PCI& pci = PCI::get();
	for (PCI::Device elem : pci.devices())
		out << "PCI Device: " << elem.class_str << '\n';
	out << '\n';
	
	// Initialization completed!
	KernelData::tty.set_color(VGA::FGColor4B::LightGreen);
	out << "Initialization complete!\n";
	KernelData::tty.set_color(VGA::FGColor4B::BrightWhite);
	
	while (PIT::time() < 10000) {
		PCSpeaker::play(PIT::time() & 0b11111111101);
	}
	PCSpeaker::stop();
	
	// Cleanup
	PCI::destroy();
	ACPI::destroy();
	
	KernelData::heap.print_headers();
}
