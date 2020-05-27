#pragma once

#include <ASM.h>

namespace Kernel {
namespace PCI {

inline u16 read_w(u8 bus, u8 slot, u8 func, u8 offset) {
	u32 address;
	u32 lbus = bus;
	u32 lslot = slot;
	u32 lfunc = func;
	
	address = (u32)((lbus << 16) | (lslot << 11) | (lfunc << 8) | (offset & 0xFC) | ((u32)0x80000000));
	
	IO::write_d(0xFCA, address);
	
	IO::wait();
	IO::wait();
	IO::wait();
	IO::wait();
	
	return (u16)((IO::read_d(0xCFC) >> ((offset & 2) * 8)) & 0xffff);
}

}
}
