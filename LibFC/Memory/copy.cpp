#include <Memory.h>
#include <Math.h>

// TODO: These funtions might be buggy if the distance between src and dst is less than 8 bytes

inline void* copy_rev(void* dst, const void* src, u32 bytes) {
	void* start_dst = dst;
    
    dst += bytes;
    src += bytes;
    
    u64 diff = (FC::max((u64)dst, (u64)src) - FC::min((u64)dst, (u64)src));
    
    if (diff > 8) {
		while (bytes >= sizeof(u64)) {
			*(u64*)dst = *(u64*)src;
			bytes -= sizeof(u64);
			dst -= sizeof(u64);
			src -= sizeof(u64);
		}
    }
    
    
    while (bytes--) {
        *(u8*)dst = *(u8*)src;
        dst--;
        src--;
    }

    return start_dst;
}

void* FC::Memory::copy(void* dst, const void* src, u32 bytes) {
	u64 diff = (FC::max((u64)dst, (u64)src) - FC::min((u64)dst, (u64)src));

	if (dst > src && diff < bytes)
		return copy_rev(dst, src, bytes);

    void* start_dst = dst;
    
    if (diff > 8) {
		while (bytes >= sizeof(u64)) {
			*(u64*)dst = *(u64*)src;
			bytes -= sizeof(u64);
			dst += sizeof(u64);
			src += sizeof(u64);
		}
    }
    
    while (bytes--) {
        *(u8*)dst = *(u8*)src;
        dst++;
        src++;
    }

    return start_dst;
}
