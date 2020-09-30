#pragma once

#include <Int.h>

namespace ELF {

enum class SegmentType : u32 {
	Null	= 0x00,
	Load	= 0x01,
	Dynamic	= 0x02,
	Interp	= 0x03,
	Note	= 0x04,
	SHLib	= 0x05,
	PHDR	= 0x06,
	TLS		= 0x07,
	LOOS	= 0x60000000,
	HIOS	= 0x6FFFFFFF,
	LOPROC	= 0x70000000,
	HIPROC	= 0x7FFFFFFF
};

struct ProgramHeader32 {
	u32 type = (u32)SegmentType::Null;
	u32 offset = 0x00;
	u32 virt_addr = 0x00;
	u32 phys_addr = 0x00;
	u32	file_size = 0x00;
	u32 mem_size = 0x00;
	u32 flags = 0x00;
	u32 align = 0x00;
};

struct ProgramHeader64 {
	u32 type = (u32)SegmentType::Null;
	u32 flags = 0x00;
	u64 offset = 0x00;
	u64 virt_addr = 0x00;
	u64 phys_addr = 0x00;
	u64	file_size = 0x00;
	u64 mem_size = 0x00;
	u64 align = 0x00;
};

enum class SectionType : u32 {
	Null = 0x00,
	ProgBits = 0x01,
	SymTab,
	StrTab,
	RELA,
	Hash,
	Dynamic,
	Note,
	NoBits,
	REL,
	SHLib,
	DynSym,
	InitArray,
	FiniArray,
	PreinitArray,
	Group,
	SymTab_SecIndex,
	Num,
	LOOS
};

enum class SectionFlags : u32 {
	Write				= 0x01,
	Alloc				= 0x02,
	ExecInstr			= 0x04,
	Merge				= 0x10,
	Strings				= 0x20,
	InfoLink			= 0x40,
	LinkOrder			= 0x80,
	OS_Nonconforming	= 0x100,
	Group				= 0x200,
	TLS					= 0x400,
	MaskOS				= 0x0FF00000,
	MaskProc			= 0xF0000000,
	Ordered				= 0x40000000,
	Exclude				= 0x80000000,
};

struct SectionHeader32 {
	u32 name_offs = 0x00;
	u32 type = 0x00;
	u32 flags = 0x00;
	u32 addr = 0x00;
	u32 offset = 0x00;
	u32 size = 0x00;
	u32 link = 0x00;
	u32 info = 0x00;
	u32 addr_align = 0x00;
	u32 entry_size = sizeof(SectionHeader32);
};

struct SectionHeader64 {
	u32 name_offs = 0x00;
	u32 type = 0x00;
	u64 flags = 0x00;
	u64 addr = 0x00;
	u64 offset = 0x00;
	u64 size = 0x00;
	u32 link = 0x00;
	u32 info = 0x00;
	u64 addr_align = 0x00;
	u64 entry_size = sizeof(SectionHeader64);
};

enum class Format : u8 {
	x32 = 0x01,
	x64 = 0x02
};

enum class Endian : u8 {
	Little = 0x01,
	Big = 0x02
};

enum class OSABI : u8 {
	SystemV = 0x00,
	HP_UX	= 0x01,
	NetBSD	= 0x02,
	Linux	= 0x03,
	GNUHurd = 0x04,
	Solaris = 0x06,
	AIX		= 0x07,
	IRIX	= 0x08,
	FreeBSD = 0x09,
	Tru64	= 0x0A,
	OpenBSD	= 0x0C,
	OpenVMS = 0x0D
};

enum class ObjectType : u16 {
	None	= 0x00,
	Rel		= 0x01,
	Exec	= 0x02,
	Dyn		= 0x03,
	Core	= 0x04,
	LOOS	= 0xFE00,
	HIOS	= 0xFEFF,
	LOPROC	= 0xFF00,
	HIPROC	= 0xFFFF
};

enum class Arch : u16 {
	None			= 0x00,
	SPARC			= 0x02,
	x86				= 0x03,
	MIPS			= 0x08,
	PowerPC			= 0x14,
	PowerPC_64		= 0x15,
	S390			= 0x16,
	ARM				= 0x28,
	SuperH			= 0x2A,
	IA_64			= 0x32,
	AMD64			= 0x3E,
	TMS320C6000		= 0x8C,
	AArch64			= 0xB7,
	RISC_V			= 0xF3,
};

const u8 CURRENT_VERSION = 0x01;

struct FileHeader32 {
	u8 magic[4] = { 0x7F, 'E', 'L', 'F' };
	
	u8 format = (u8)Format::x32;
	u8 endian = (u8)Endian::Little;
	u8 version = CURRENT_VERSION;
	
	u8 osabi = (u8)OSABI::SystemV;
	u8 osabi_version = 0x00;
	
	u8 pad[7] = {0, 0, 0, 0, 0, 0, 0};
	
	u16 type = (u16)ObjectType::Exec;
	u16 arch = (u16)Arch::x86;
	
	u32 elf_version = CURRENT_VERSION;
	
	u32 entry_point = 0x00;
	u32 ph_offs = 0x00;
	u32 sh_offs = 0x00;
	
	u32 flags = 0x00;
	u16 size = sizeof(FileHeader32);
	
	u16 ph_entry_size = sizeof(ProgramHeader32);
	u16 ph_entries = 0x00;
	
	u16 sh_entry_size = sizeof(SectionHeader32);
	u16 sh_entries = 0x00;
	u16 sh_str_index = 0x00;
};

struct FileHeader64 {
	u8 magic[4] = { 0x7F, 'E', 'L', 'F' };
	
	u8 format = (u8)Format::x64;
	u8 endian = (u8)Endian::Little;
	u8 version = CURRENT_VERSION;
	
	u8 osabi = (u8)OSABI::Linux;
	u8 osabi_version = 0x00;
	
	u8 pad[7] = {0, 0, 0, 0, 0, 0, 0};
	
	u16 type = (u16)ObjectType::Exec;
	u16 arch = (u16)Arch::AMD64;
	
	u32 elf_version = CURRENT_VERSION;
	
	u64 entry_point = 0x00;
	u64 ph_offs = 0x00;
	u64 sh_offs = 0x00;
	
	u32 flags = 0x00;
	u16 size = sizeof(FileHeader64);
	
	u16 ph_entry_size = sizeof(ProgramHeader64);
	u16 ph_entries = 0x00;
	
	u16 sh_entry_size = sizeof(SectionHeader64);
	u16 sh_entries = 0x00;
	u16 sh_str_index = 0x00;
};

}

