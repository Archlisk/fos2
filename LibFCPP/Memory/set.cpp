#include <Memory.h>

void* FCPP::Memory::set(void* dst, const u8 val, u32 bytes) {
    void* start_dst = dst;
    
     u64 val64 = (u64)val << 56 | (u64)val << 48 | (u64)val << 40 | (u64)val << 32 | (u64)val << 24 | (u64)val << 16 | (u64)val << 8 | val;
    
    while (bytes >= sizeof(u64)) {
        *(u64*)dst = val64;
        bytes -= sizeof(u64);
        dst += sizeof(u64);
    }
    
    while (bytes--) {
        *(u8*)dst = val;
        dst++;
    }
    
    return start_dst;
}
