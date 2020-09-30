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
#include <Drivers/IDE.h>

#include <Paging.h>
#include <Interrupts.h>
#include <CPUID.h>
#include <TTY.h>
#include <Map.h>
#include <String.h>

#define HEAP_ADDR ((void*)(PAGE_SIZE * 4))

using namespace Kernel;

extern "C" Paging::PageDir kernel_page_dir;

Terminal KernelData::tty(nullptr, 0, 0);
Heap KernelData::heap(nullptr, 0);

void panic(const FC::String& error_msg) {
		KernelData::tty.clear();
		KernelData::tty.set_color(VGA::FGColor4B::LightRed);
		out << error_msg;
		while (true)
			ASM::hlt();
}

extern "C"
void enter() {
	// Heap
	KernelData::heap = Heap(HEAP_ADDR, PAGE_SIZE);

	// TTY
	KernelData::tty = Terminal((u16*)0xB8000, 80, 25);
	KernelData::tty.set_color(VGA::FGColor4B::BrightWhite);

	// SSE
	CPU::CPUInfo* cpu_info = CPU::info();
	if (!(cpu_info->sse3 || cpu_info->sse4_1 || cpu_info->sse4_2))
		panic("This CPU does not support SSE3. FOS2 cannot run without this feature.");
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
	out << "CPU: " << CPU::brand_str() << '\n';
	
	// ACPI
	ACPI& acpi = ACPI::get();
	if (acpi.pcie_supported())
		out << "PCIe support detected\n";
	else
		out << "No PCIe support detected\n";
	
	// PCI
	PCI& pci = PCI::get();
	for (PCI::Device elem : pci.devices()) {
		out << "PCI Device: '" << elem.class_str << "'\n";
		
		// IDE
		if (elem.reg_data[PCI_HC_HEADER_TYPE] == PCI_HEADER_TYPE_0
			&& elem.reg_data[PCI_HC_CLASS]	  == 0x01
			&& elem.reg_data[PCI_HC_SUBCLASS] == 0x01)
		{
			IDE& ide = IDE::get();
			ide.initialize(
				elem.reg_data32(PCI_H0_BAR0), 
				elem.reg_data32(PCI_H0_BAR1), 
				elem.reg_data32(PCI_H0_BAR2), 
				elem.reg_data32(PCI_H0_BAR3),
				elem.reg_data32(PCI_H0_BAR4)
			);
		}
	}
	out << '\n';
	
	// Initialization completed!
	KernelData::tty.set_color(VGA::FGColor4B::LightGreen);
	out << "Initialization complete!\n";
	KernelData::tty.set_color(VGA::FGColor4B::BrightWhite);
	
    u8 data[512];

    out << "Reading from disk 0\n";
    IDE::get()[0].read_disk(data, ATA_MASTER, 0, 1);
    out << "Done reading!\n";

    for (u32 i = 0; i < 512; i++) {
        out << (void*)data[i];
    }

    FC::Memory::set(data, 0, 512);

    out << "Writing to disk 0\n";
    IDE::get()[0].write_disk(data, ATA_MASTER, 0, 1);
    out << "Done writing\n";

    out << "Reading from disk 0\n";
    IDE::get()[0].read_disk(data, ATA_MASTER, 0, 1);
    out << "Done reading!\n";

    for (u32 i = 0; i < 512; i++) {
        out << (void*)data[i];
    }

    // Cleanup
	IDE::destroy();
	PCI::destroy();
	ACPI::destroy();
	
	KernelData::heap.print_headers();
}
