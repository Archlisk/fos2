#include <Paging.h>

using namespace Kernel;
using namespace Kernel::Paging;

extern "C" void enable_paging_asm(Paging::PageDir& pd);

void Paging::enable(Paging::PageDir& pd) {
	enable_paging_asm(pd);
}

void PageDir::identity_map() {
	u32 current_addr = 0;

	for (int i = 0; i < PAGE_ENTRIES; i++) {
		*(u32*)&entries[i] = current_addr;
		entries[i].present = 1;
		entries[i].writable = 1;
		entries[i].huge = 1;
		
		current_addr += PAGE_SIZE;
	}
}

void PageDir::unmap_all() {
	for (int i = 0; i < PAGE_ENTRIES; i++)
		*(u32*)&entries[i] = 0;
}

void* PageDir::map(void* phys_addr, void* virt_addr) {
	u16 page_index = (u64)phys_addr / PAGE_SIZE;
	
	entries[page_index].addr = PAGE_ALIGN(virt_addr);
	entries[page_index].present = 1;
	entries[page_index].writable = 1;
	entries[page_index].huge = 1;
	
	return virt_addr;
}

void PageDir::unmap(void* phys_addr) {
	*(u32*)&entries[(u64)phys_addr / PAGE_SIZE] = 0;
}
