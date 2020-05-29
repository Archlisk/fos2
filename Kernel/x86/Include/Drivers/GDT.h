#pragma once

#include <Array.h>

namespace Kernel {
namespace GDT {

	struct PACKED Entry {
	
		struct PACKED AccessByte {
			AccessByte() {}
			AccessByte(u8 data) { *(u8*)this = data; }
		
			u8 present				: 1;
			u8 privilege			: 2;
			u8 descriptor_type		: 1;
			u8 executable			: 1;
			u8 direction			: 1;
			u8 readable_writable	: 1;
			u8 accessed				: 1;
		};
	
		Entry() {}
		Entry(u32 base, u32 limit, AccessByte arg_access_byte) {
			base_low = base & 0xFFFF;
			base_high_low = (base >> 16) & 0xFF;
			base_high_high = (base >> 24) & 0xFF;
			
			limit_low = limit & 0xFFFF;
			limit_high = (limit & 0xFFFF0000) >> 16;
			
			access_byte = arg_access_byte;
		}
		
		u16 limit_low;
		u16 base_low;
		u8 base_high_low;
		
		AccessByte access_byte;
		
		u8 limit_high : 4;
		
		// Flags
		u8 granularity	: 1 = 1;
		u8 size			: 1 = 1;
		u8 ignored		: 2 = 0b11;
		
		u8 base_high_high;
	};
	
	void load(Entry* gdt, u16 size);

}
}
