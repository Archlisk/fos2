#include <Heap.h>

#include <Memory.h>

using namespace Kernel;

Heap::Heap(void* start_addr, u64 size)
	: m_start_addr(start_addr), m_size(size)
{
	Header* first_header = (Header*)start_addr;
	Header* last_header = (Header*)((u64)start_addr + size - sizeof(Header));
	
	first_header->prev = nullptr;
	first_header->free = true;
	first_header->first = true;
	first_header->last = false;
	first_header->next = last_header;
	
	last_header->prev = first_header;
	last_header->free = false;
	last_header->first = false;
	last_header->last = true;
	last_header->next = nullptr;
}

#include <TTY.h>

void* Heap::alloc(u32 bytes) {
	if (!bytes)
		return nullptr;
	
	Header* c_header = (Header*)m_start_addr;
	
	while (!c_header->last) {
		if (c_header->free) {
			u32 c_size = ((u64)c_header->next - (u64)c_header) - sizeof(Header);
		
			if (c_size >= bytes && c_size <= bytes + sizeof(Header)) {
				c_header->free = false;
				return (void*)((u64)c_header + sizeof(Header));
			}
			
			if (c_size >= bytes + sizeof(Header)) {
				Header* new_header = (Header*)((u64)c_header + bytes + sizeof(Header));
				
				new_header->free = true;
				new_header->last = false;
				new_header->first = false;
				
				new_header->prev = c_header;
				new_header->next = c_header->next;
				
				c_header->next = new_header;
				c_header->free = false;
				
				new_header->next->prev = new_header;
				
				return (void*)((u64)c_header + sizeof(Header));
			}
		}
		
		c_header = c_header->next;
	}
	
	out << "Heap is out of memory!\n";
	return nullptr;
}

void* Heap::realloc(void* addr, u32 bytes) {
	if (!bytes) {
		free(addr);
		return nullptr;
	}

	if (!addr)
		return alloc(bytes);
	
	Header* header = (Header*)((u64)addr - sizeof(Header));
	u32 alloc_size = (u64)header->next - (u64)header - sizeof(Header);
	
	// TODO: When the current allocated size is smaller it should create a new header instead of free()-ing and alloc()-ing.
	
	if (bytes > alloc_size) {
		void* new_addr = alloc(bytes);
		FC::Memory::copy(new_addr, addr, alloc_size);
		free(addr);
		return new_addr;
	}
	
	if (bytes < alloc_size) {
		void* new_addr = alloc(bytes);
		FC::Memory::copy(new_addr, addr, bytes);
		free(addr);
		return new_addr;
	}
	
	return addr;
}

void Heap::free(void* addr) {
	if (!addr)
		return;
	
	Header* header = (Header*)((u64)addr - sizeof(Header));
	
	header->free = true;
	
	if (!header->first && header->prev->free)
		erase_header(header);
	
	if (!header->next->last && header->next->free)
		erase_header(header->next);
	
//	if (check_corruption()) {
//		out << "HEAP CORRUPTED!\n";
//		print_headers();
//		while (true) {}
//	}
}

bool Heap::check_corruption() {
	Header* c_header = (Header*)m_start_addr;
	
	Header* next_header_ptr = nullptr;
	Header* prev_header_ptr = nullptr;
	
	while (!c_header->last) {
		if (next_header_ptr != c_header && next_header_ptr)
			return true;
		if (prev_header_ptr != c_header->prev && prev_header_ptr)
			return true;
	
		next_header_ptr = c_header->next;
		prev_header_ptr = c_header;
		c_header = c_header->next;
	}
	
	return false;
}

void Heap::print_headers() {
	Header* c_header = (Header*)m_start_addr;
	
	Header* next_header_ptr = nullptr;
	Header* prev_header_ptr = nullptr;
	
	while (!c_header->last) {
		if (next_header_ptr != c_header && next_header_ptr)
			out << "HEAP CORRUPTION DETECTED!\n";
		if (prev_header_ptr != c_header->prev && prev_header_ptr)
			out << "HEAP CORRUPTION DETECTED!\n";
	
		u32 c_size = (u64)c_header->next - (u64)c_header - sizeof(Header);
		
		if (c_header->free)
			out << "FREE:\t 0x" << c_header << " size=" << (u64)c_size << "B next=" << c_header->next << " prev=" << c_header->prev << "\n";
		else
			out << "USED:\t 0x" << c_header << " size=" << (u64)c_size << "B next=" << c_header->next << " prev=" << c_header->prev << "\n";
		
		next_header_ptr = c_header->next;
		prev_header_ptr = c_header;
		c_header = c_header->next;
	}
}
