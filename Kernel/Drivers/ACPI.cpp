#include <Drivers/ACPI.h>

#include <TTY.h>

#include <Memory.h>

using namespace FC;
using namespace Kernel;


inline u8 verify(void* table, u32 size) {
	u8 sum = 0;
	for (u32 i = 0; i < size; i++)
		sum += ((char*)table)[i];
	
	return sum == 0;
}

template<typename T>
inline u8 verify(T* table) {
	u8 sum = 0;
	for (u32 i = 0; i < sizeof(T); i++)
		sum += ((u8*)table)[i];
	
	return sum == 0;
}

inline u8 verify(ACPI::RSDP_2* table) {
	return verify((char*)table + sizeof(ACPI::RSDP), sizeof(ACPI::RSDP_2) - sizeof(ACPI::RSDP));
}

inline u8 verify(ACPI::SDTHeader* table) {
	return verify((char*)table, table->length);
}

#include <ASM.h>

ACPI::ACPI() {
	m_rsdp = find_rsdp();
	out << "ACPI Revision: " << m_rsdp->revision << '\n';
	out << "RSDP Address: 0x" << m_rsdp << '\n';
	out << "RSDT Address: 0x" << (void*)m_rsdp->rsdt_addr << '\n';
	out << "XSDT Address: 0x" << (void*)((RSDP_2*)m_rsdp)->xsdt_addr << '\n';
	
	if (!m_rsdp)
		out << "RSDP Address not found!\n";
	if (!verify(m_rsdp))
		out << "RSDP Checksum is invalid!\n";
	if (m_rsdp->revision >= 2)
		if (!verify((RSDP_2*)m_rsdp))
			out << "RSDP_2 Checksum is invalid!\n";
	
	m_revision = m_rsdp->revision;
	
	if (m_revision < 2) {
		m_rsdt = (RSDT*)m_rsdp->rsdt_addr;
		if (m_rsdt && !verify(&m_rsdt->header))
			out << "RSDT Checksum is invalid!\n";
	}
	else {	
		m_xsdt = (XSDT*) ((RSDP_2*)m_rsdp)->xsdt_addr;
		if (m_xsdt && !verify(&m_xsdt->header))
			out << "XSDT Checksum is invalid!\n";
	}
	
	m_fadt = (FADT*)find_sdt_table("FACP");
		
	if (m_fadt && !verify(&m_fadt->header))
		out << "FADT Checksum is invalid!\n";
	else
		out << "FADT Address: 0x" << m_fadt << '\n';
		
	m_mcfg = (MCFG*)find_sdt_table("MCFG");
	
	if (m_mcfg && !verify(&m_mcfg->header))
		out << "MCFG Checksum is invalid!\n";
		
	if (pcie_supported()) {
		out << "MCFG Address: 0x" << m_mcfg << '\n';
		u32 entries = (m_mcfg->header.length - sizeof(MCFG)) / sizeof(MCFGDevice);
		for (u32 i = 0; i < entries; i++) {
			MCFGDevice* device = &m_mcfg->devices[i];
			out << "PCI-E Device found at: 0x" << device << "\n";
		}
	}
}

void* ACPI::find_sdt_table(const char* table_name) {
	if (m_revision < 2) {
		u32 entries = (m_rsdt->header.length - sizeof(SDTHeader)) / sizeof(u32);
		for (u32 i = 0; i < entries; i++) {
			const char* signature = ((SDTHeader*)m_rsdt->sdts[i])->signature;
			if (Memory::compare(signature, table_name, 4))
				return (void*)m_rsdt->sdts[i];
		}
	}
	else {
		u32 entries = (m_xsdt->header.length - sizeof(SDTHeader)) / sizeof(u64);
		for (u32 i = 0; i < entries; i++) {
			const char* signature = ((SDTHeader*)m_xsdt->sdts[i])->signature;
			if (Memory::compare(signature, table_name, 4))
				return (void*)m_xsdt->sdts[i];
		}
	}
	return nullptr;
}

ACPI::RSDP* ACPI::find_rsdp() {
	const char* signature = "RSD PTR ";
	const char* ptr = (char*)0xE0000;
	
	const u32 len = 8;
	
	while (ptr < (char*)0xFFFFF) {
		if (FC::Memory::compare(signature, ptr, len))
			return (RSDP*)ptr;
		
		ptr += 16;
	}
	
	return nullptr;
}
