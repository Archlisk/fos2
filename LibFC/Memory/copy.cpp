#include <Memory.h>
#include <Math.h>

// TODO: These funtions will be buggy if the distance between src and dst is less than 8 bytes

FORCE_INLINE void* copy_rev(void* dst, const void* src, u32 bytes) {
	void* start_dst = dst;
    
    dst += bytes - 1;
    src += bytes - 1;
    
    u64 diff = (FC::max(dst, src) - FC::min(dst, src));
    
    while (bytes >= sizeof(u64)) {
        *(u64*)dst = *(u64*)src;
        bytes -= sizeof(u64);
        dst -= sizeof(u64);
        src -= sizeof(u64);
    }
    
    while (bytes--) {
        *(u8*)dst = *(u8*)src;
        dst--;
        src--;
    }

    return start_dst;
}

void* FC::Memory::copy(void* dst, const void* src, u32 bytes) {
	if (dst > src && src < dst + bytes)
		return copy_rev(dst, src, bytes);

    void* start_dst = dst;
    
    while (bytes >= sizeof(u64)) {
        *(u64*)dst = *(u64*)src;
        bytes -= sizeof(u64);
        dst += sizeof(u64);
        src += sizeof(u64);
    }
    
    while (bytes--) {
        *(u8*)dst = *(u8*)src;
        dst++;
        src++;
    }

    return start_dst;
}
