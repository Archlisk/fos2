#pragma once

#include <ASM.h>

#include <Vector.h>

#define PCI_MAX_BUS 0xFF
#define PCI_MAX_DEVICE 0x10
#define PCI_MAX_FUNC 0x04

#define PCI_CONFIG_ADDR 0x0CF8
#define PCI_CONFIG_DATA 0x0CFC


#define PCI_HEADER_MAX_SIZE 0x44

#define PCI_HEADER_TYPE_0 0x00
#define PCI_HEADER_TYPE_1 0x01
#define PCI_HEADER_TYPE_2 0x02

// Common header registers
#define PCI_HC_VENDOR_ID	0x00
#define PCI_HC_DEVICE_ID	0x02

#define PCI_HC_COMMAND	0x04
#define PCI_HC_STATUS	0x06

#define PCI_HC_REV_ID	0x08
#define PCI_HC_PROG_IF	0x09
#define PCI_HC_SUBCLASS	0x0A
#define PCI_HC_CLASS	0x0B

#define PCI_HC_CACHE_LINE_SIZE	0x0C
#define PCI_HC_LATENCY_TIMER	0x0D
#define PCI_HC_HEADER_TYPE		0x0E
#define PCI_HC_BIST				0x0F


// Header 0 registers
#define PCI_H0_BAR0	0x10
#define PCI_H0_BAR1	0x14
#define PCI_H0_BAR2	0x18
#define PCI_H0_BAR3	0x1C
#define PCI_H0_BAR4	0x20
#define PCI_H0_BAR5	0x24

#define PCI_H0_CCS_PTR	0x28

#define PCI_H0_SUBSYS_VENDOR_ID	0x2C
#define PCI_H0_SUBSYS_ID		0x2E

#define PCI_H0_EXPANSION_ROM_BASE_ADDR	0x30

#define PCI_H0_CAPABILITIES_PTR	0x34

#define PCI_H0_INTERRUPT_LINE	0x3C
#define PCI_H0_INTERRUPT_PIN	0x3D
#define PCI_H0_MIN_GRANT		0x3E
#define PCI_H0_MAX_LATENCY		0x3E

namespace Kernel {
class PCI {
	singleton(PCI, { enumerate(); });
	
public:
	struct Device {
		Device(u8 bus, u8 device, u8 func)
				: bus(bus), device(device), func(func)
		{
			// Load common header
			for (u32 i = 0; i < 0x04; i++)
				((u32*)reg_data)[i] = read_reg(bus, device, func, i << 2);
			
			// Load header-specific data
			if (reg_data[PCI_HC_HEADER_TYPE] == 2) {
				for (u32 i = 4; i < 0x12; i++)
					((u32*)reg_data)[i] = read_reg(bus, device, func, i << 2);
			}
			else {
				for (u32 i = 4; i < 0x10; i++)
					((u32*)reg_data)[i] = read_reg(bus, device, func, i << 2);
			}
			
			class_str = PCI::class_str(reg_data[PCI_HC_CLASS], reg_data[PCI_HC_SUBCLASS], reg_data[PCI_HC_PROG_IF]);
		}
		
		u32 reg_data32(u8 offset) { return ((u32*)reg_data)[offset / sizeof(u32)]; }
		u32 reg_data16(u8 offset) { return ((u16*)reg_data)[offset / sizeof(u16)]; }
		
		u8 bus, device, func;
		
		const char* class_str;
		
		u8 reg_data[PCI_HEADER_MAX_SIZE];
		
	};
	
	static u32 make_addr(u8 bus, u8 device, u8 func, u8 offset) {
		return ((u32)0b1 << 31) | ((u32)bus << 16) | (((u32)device & 0xF) << 11) | (((u32)func & 0xF) << 8) | (offset & 0xFC);
	}

	static u32 read_reg(u8 bus, u8 device, u8 func, u8 offset) {
		IO::write_d(PCI_CONFIG_ADDR, make_addr(bus, device, func, offset));
		return IO::read_d(PCI_CONFIG_DATA) >> ((offset & 2) * 8);
	}
	
	FC::Vector<Device>& enumerate();
	
	const FC::Vector<Device>& devices() { return m_devices; }
	
	static const char* class_str(u8 class_code, u8 subclass, u8 prog_if);

private:
	FC::Vector<Device> m_devices;
};

}
