#include <Memory.h>

void* FCPP::Memory::copy(void* dst, const void* src, u32 bytes) {
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
