#pragma once

#include <ASM.h>

#define PCI_MAX_BUS 0xFF
#define PCI_MAX_DEVICE 0x10
#define PCI_MAX_FUNC 0x04

#define PCI_CONFIG_ADDR 0x0CF8
#define PCI_CONFIG_DATA 0x0CFC

#include <String.h>
#include <Vector.h>

namespace Kernel {
class PCI {
	singleton(PCI, { enumerate(); });
	
public:
	struct Device {
		u8 bus;
		u8 device;
		u8 func;
		FC::String class_str;
	};
	
	static u32 make_addr(u8 bus, u8 device, u8 func, u8 offset) {
		return ((u32)0b1 << 31) | ((u32)bus << 16) | (((u32)device & 0xF) << 11) | (((u32)func & 0xF) << 8) | (offset & 0xFC);
	}

	static u32 read_d(u8 bus, u8 device, u8 func, u8 offset) {
		IO::write_d(PCI_CONFIG_ADDR, make_addr(bus, device, func, offset));
		return (u32)IO::read_d(PCI_CONFIG_DATA) >> ((offset & 2) * 8);
	}
	
	FC::Vector<Device>& enumerate();
	
	const FC::Vector<Device>& devices() { return m_devices; }
	
	static const char* class_str(u16 class_info);

private:
	FC::Vector<Device> m_devices;
};

}
