#pragma once

namespace Kernel {

class Heap {
public:
	Heap(void* start_addr, u64 size);

	void* alloc(u32 bytes);
	void* realloc(void* addr, u32 bytes);
	void free(void* addr);
	
	void print_headers();
	
	struct PACKED Header {
		Header* next;
		u8 free : 1;
		u8 first : 1;
		u8 last : 1;
		u8 : 5; // IGNORED
		Header* prev;
	};

private:
	void* m_start_addr;
	u64 m_size;
};

}
