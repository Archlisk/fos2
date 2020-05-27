#include <Memory.h>

#ifdef KERNEL

#include <KernelData.h>

void FCPP::Memory::free(void* addr) {
	Kernel::KernelData::heap.free(addr);
}

#else

void FCPP::Memory::free(void* addr) {

}

#endif
