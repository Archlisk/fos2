#include <Drivers/PCI.h>

using namespace Kernel;

FC::Vector<PCI::Device>& PCI::enumerate() {
	m_devices.clear();
	
	for (u16 bus = 0; bus < PCI_MAX_BUS; bus++) {
		for (u8 device = 0; device < PCI_MAX_DEVICE; device++) {
			for (u8 func = 0; func < PCI_MAX_FUNC; func++) {
			
				u16 res = PCI::read_reg(bus, device, func, 0x00);
				
				if (res != 0xFFFF)
					m_devices.push(Device(bus, device, func));
			}
		}
	}
	
	return m_devices;
}
