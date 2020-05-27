#pragma once

#define IDT_ENTRIES 256

#define IDT_TASK_GATE		0x5
#define IDT_INTERRUPT_GATE	0xE
#define IDT_TRAP_GATE		0xF

namespace Kernel {

struct IDT {

	struct __attribute__((packed)) Entry {
		
		struct __attribute__((packed)) Attributes {
			Attributes() {}
			
			Attributes(u8 gate_type, u8 privilege) 
				: gate_type(gate_type), privilege(privilege), present(1)
			{
				if (gate_type == IDT_TASK_GATE)
					storage_segment = 1;
			}
			
			Attributes(u8 data) { *(u8*)this = data; }
			
			u8 gate_type		: 4 = IDT_INTERRUPT_GATE;
			u8 storage_segment	: 1 = 0;
			u8 privilege		: 2 = 0;
			u8 present			: 1 = 1;
		};
	
		Entry() {}
		Entry(u32 offset, u16 selector, Attributes attribs) 
			: offset_low(offset), selector(selector), attribs(attribs), offset_high(offset >> 16) {}
		
		Entry(u64 data) { *(u64*)this = data; }
		
		u16 offset_low;
		u16 selector;
		u8 zero = 0;
		Attributes attribs;
		u16 offset_high;
	};
	
	static void load(IDT* idt);
	static void init();
	
	Entry entries[IDT_ENTRIES];
};

}
