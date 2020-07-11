#pragma once

namespace Kernel {

class ACPI {
	singleton(ACPI, ;);
	
public:

	struct PACKED GenericAddress {
		u8 address_space;
		u8 bit_width;
		u8 bit_offset;
		u8 access_size;
		u64 address;
	};
	
	struct PACKED RSDP {
		char Signature[8];
		u8 checksum;
		char oem_id[6];
		u8 revision;
		u32 rsdt_addr;
	};
	
	struct PACKED RSDP_2 {
		RSDP first;
		
		u32 length;
		u64 xsdt_addr;
		u8 ext_checksum;
		u8 reserved[3];
	};
	
	struct PACKED SDTHeader {
		char signature[4];
		u32 length;
		u8 revision;
		u8 checksum;
		char oem_id[6];
		char oem_table_id[8];
		u32 oem_revision;
		u32 creator_id;
		u32 creator_revision;
	};
	
	struct PACKED RSDT {
		SDTHeader header;
		u32 sdts[];
	};
	
	struct PACKED XSDT {
		SDTHeader header;
		u64 sdts[];
	};
	
	struct PACKED FADT {
		SDTHeader header;
		u32 firmware_ctrl;
		u32 dsdt;
		
		u8 reserved;
		
		u8 preferred_pm_profile;
		u16 sci_interrupt;
		u32 smi_cmd_port;
		u8 acpi_enable;
		u8 acpi_disable;
		u8 s4bios_req;
		u8 pstate_control;
		u32 pm1a_event_block;
		u32 pm1b_event_block;
		u32 pm1a_control_block;
		u32 pm1b_control_block;
		u32 pm2_control_block;
		u32 pm_timer_block;
		u32 gpe0_block;
		u32 gpe1_block;
		u8  pm1_event_Length;
		u8  pm1_control_Length;
		u8  pm2_control_Length;
		u8  pm_timer_length;
		u8  gpe0_length;
		u8  gpe1_length;
		u8  gpe1_base;
		u8  state_control;
		u16 worst_c2_Latency;
		u16 worst_c3_Latency;
		u16 flush_size;
		u16 flush_stride;
		u8  duty_offset;
		u8  duty_width;
		u8  day_alarm;
		u8  month_alarm;
		u8  century;
		
		u16 boot_arch_flags;
		
		u8 reserved2;
		
		u32 flags;
		
		GenericAddress reset_reg;
		
		u8 reset_val;
		
		u8 reserved3[3];
	};
	
	struct PACKED FADT_2 {
		FADT first;
		
		u64 x64_firmware_ctrl;
		u64 x64_dsdt;
		
		GenericAddress x64_pm1a_event_block;
		GenericAddress x64_pm1b_event_block;
		GenericAddress x64_pm1a_control_block;
		GenericAddress x64_pm1b_control_block;
		GenericAddress x64_pm2_control_block;
		GenericAddress x64_pm_timer_block;
		GenericAddress x64_gpe0_block;
		GenericAddress x64_gpe1_block;
	};
	
	struct PACKED MCFGDevice {
		u64 address;
		u16 segment_group;
		u8 start_bus;
		u8 end_bus;
		u32 reserved;
	};
	
	struct PACKED MCFG {
		SDTHeader header;
		
		u64 reserved;
		
		MCFGDevice devices[];
	};

	inline u8 pcie_supported() { return m_mcfg != 0; }

private:
	RSDP* find_rsdp();
	void* find_sdt_table(const char* table_name);
	
	u8 m_revision = 0;
	
	RSDP* m_rsdp = nullptr;
	RSDT* m_rsdt = nullptr;
	XSDT* m_xsdt = nullptr;
	FADT* m_fadt = nullptr;
	MCFG* m_mcfg = nullptr;
};

}
