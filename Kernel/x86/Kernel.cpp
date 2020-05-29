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

#include <String.h>
#include <Memory.h>
#include <Vector.h>

#define HEAP_ADDR ((void*)(PAGE_SIZE * 4))

using namespace Kernel;
using namespace FC;

extern "C" Paging::PageDir kernel_page_dir;

Terminal KernelData::tty(nullptr, 0, 0);
Heap KernelData::heap(nullptr, 0);

void kernel_main() {
//	for (u16 bus = 0; bus < PCI_MAX_BUS; bus++)
//		for (u8 device = 0; device < PCI_MAX_DEVICE; device++)
//			for (u8 func = 0; func < PCI_MAX_FUNC; func++) {
//				u16 res = PCI::read_w(bus, device, func, 0x00);
//				if (res != 0xFFFF) {
//					res = PCI::read_w(bus, device, func, 0x0A);
//					out << "PCI " << bus << ":" << device << ":" << func << " 0x" << (void*)res << " '"
//						<< PCI::class_str(res) << "'\n";
//				}
//			}
	
	Vector<String> vec;
	vec.push(String("Fuck"));
	vec.push(String(" Bit"));
	vec.push(String("ch\n"));
	vec.insert(1, String(" You"));
	
	for (String& str : vec)
		out << str;
	
	KernelData::tty.set_color(VGA::FGColor4B::LightGreen);
	out << "Initialization complete!\n";
	KernelData::tty.set_color(VGA::FGColor4B::BrightWhite);
}

extern "C"
void enter() {
	KernelData::heap = Heap(HEAP_ADDR, PAGE_SIZE);
	KernelData::tty = Terminal((u16*)0xB8000, 80, 25);
	
	KernelData::tty.set_color(VGA::FGColor4B::BrightWhite);

	kernel_page_dir.unmap_all();	// Zero all entries to remove any garbage
	kernel_page_dir.identity_map_all();
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
	
	out << "CPU\t: " << CPU::brand_str() << '\n';
	
	ACPI acpi;
	
	kernel_main();
	KernelData::heap.print_headers();
}
