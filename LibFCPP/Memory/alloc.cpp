#include <Memory.h>

#ifdef KERNEL
#include <KernelData.h>

void* FCPP::Memory::alloc(u32 size) {
	return Kernel::KernelData::heap.alloc(size);
}

#else

void* FCPP::Memory::alloc(u32 size) {
	return nullptr;
}

#endif


