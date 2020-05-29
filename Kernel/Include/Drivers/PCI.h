#pragma once

#include <ASM.h>

#define PCI_MAX_BUS 0xFF
#define PCI_MAX_DEVICE 0x10
#define PCI_MAX_FUNC 0x04

#define PCI_CONFIG_ADDRESS 0x0CF8
#define PCI_CONFIG_DATA 0x0CFC

namespace Kernel {
namespace PCI {

inline u16 read_w(u8 bus, u8 device, u8 func, u8 offset) {
	volatile u32 address = ((u32)0b1 << 31) | ((u32)bus << 16) | (((u32)device & 0xF) << 11) | (((u32)func & 0xF) << 8) | (offset & 0xFC);
	
	IO::write_d(PCI_CONFIG_ADDRESS, address);
	
	return (u32)IO::read_d(PCI_CONFIG_DATA) >> ((offset & 2) * 8);
}

const char* class_str(u16 class_info);

}
}
