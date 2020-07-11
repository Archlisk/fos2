#pragma once

namespace Kernel {

class Heap {
public:

	struct PACKED Header {
		Header* next;
		u8 free : 1;
		u8 first : 1;
		u8 last : 1;
		u8 : 5; // IGNORED
		Header* prev;
	};

	Heap(void* start_addr, u64 size);

	void* alloc(u32 bytes);
	void* realloc(void* addr, u32 bytes);
	void free(void* addr);
	
	bool check_corruption();
	void print_headers();

private:
	void erase_header(Header* header) {
		header->prev->next = header->next;
		header->next->prev = header->prev;
	}

	void* m_start_addr;
	u64 m_size;
};

}
