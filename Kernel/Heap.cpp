#include <Heap.h>

using namespace Kernel;

Heap::Heap(void* start_addr, u64 size)
	: m_start_addr(start_addr), m_size(size)
{
	Header* first_header = (Header*)start_addr;
	Header* last_header = (Header*)((u64)start_addr + size - sizeof(Header));
	
	first_header->prev = nullptr;
	first_header->free = true;
	first_header->is_first = true;
	first_header->is_last = false;
	first_header->next = last_header;
	
	last_header->prev = first_header;
	last_header->free = false;
	last_header->is_first = false;
	last_header->is_last = true;
	last_header->next = nullptr;
}

void* Heap::alloc(u32 size) {
	if (!size)
		return nullptr;
		
	Header* c_header = (Header*)m_start_addr;
	
	while (!c_header->is_last) {
		u32 c_size = ((u64)c_header->next - (u64)c_header);
	
		if (c_header->free) {
			if (c_size >= size && c_size <= size + sizeof(Header)) {
				c_header->free = false;
				return (void*)((u64)c_header + sizeof(Header));
			}
			
			if (c_size > size + sizeof(Header)) {
				
				Header* new_header = (Header*)((u64)c_header + size + sizeof(Header));
				
				new_header->prev = c_header;
				new_header->free = true;
				new_header->is_last = false;
				new_header->is_first = false;
				new_header->next = c_header->next;
				
				c_header->next = new_header;
				c_header->free = false;
				
				new_header->next->prev = new_header;
				
				return (void*)((u64)c_header + sizeof(Header));
			}
		}
		
		c_header = c_header->next;
	}
	
	return nullptr;
}

void Heap::free(void* addr) {
	if (!addr)
		return;
	
	Header* header = (Header*)((u64)addr - sizeof(Header));
	
	header->free = true;
	
	if (!header->is_first && header->prev->free) {
		header->prev->next = header->next;
		header->next->prev = header->prev;
		
		header = header->prev;
	}
	
	if (header->next->free) {
		header->next->next->prev = header;
		header->next = header->next->next;
	}
}
