#pragma once

#include <Memory.h>

#define PAGE_ENTRIES 1024
#define PAGE_SIZE 4194304

#define PAGE_ALIGN(num) ((u64)num >> 11)

namespace Kernel {
namespace Paging {

struct __attribute__((packed)) PageDir {

	struct __attribute__((packed)) Entry {
		u8 present : 1;
		u8 writable : 1;
		u8 user_access : 1;
		u8 write_through : 1;
		u8 cache_disabled : 1;
		u8 accessed : 1;
		u8 : 1; // IGNORED
		u8 huge : 1;
		u8 : 3; // AVAILABLE
		u32 addr : 21;
	};
	
	void identity_map();
	void unmap_all();
	
	Entry entries[PAGE_ENTRIES];
	
	void* map(void* phys_addr, void* virt_addr);
	void unmap(void* phys_addr);
	
	void* alloc(u64 bytes);
	void free(void* phys_addr);
};

void enable(PageDir& pd);

}
}
