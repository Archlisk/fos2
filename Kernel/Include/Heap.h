#pragma once

#include <FCPPTypes.h>

class Terminal;

namespace Kernel {

class Heap {
public:
	Heap(void* start_addr, u64 size);

	void* alloc(u32 size);
	void free(void* addr);
	
	void print_headers(Terminal& tty);
	
	struct __attribute__((packed)) Header {
		Header* next;
		u8 free : 1;
		u8 is_first : 1;
		u8 is_last : 1;
		u8 : 5; // IGNORED
		Header* prev;
	};

private:
	void* m_start_addr;
	u64 m_size;
};

}
