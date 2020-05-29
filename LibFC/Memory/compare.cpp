#include <Memory.h>

u8 FC::Memory::compare(const void* area1, const void* area2, u32 bytes) {
    while (bytes >= sizeof(u64)) {
        if (*(u64*)area1 != *(u64*)area2)
			return false;
        bytes -= sizeof(u64);
        area1 += sizeof(u64);
        area2 += sizeof(u64);
    }
    
    while (bytes--) {
        if (*(u8*)area1 != *(u8*)area2)
			return false;
        area1++;
        area2++;
    }

    return true;
}
