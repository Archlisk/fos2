#include <Memory.h>

void* FCPP::Memory::set(void* dst, u64 val, u32 bytes) {
    while (bytes >= sizeof(u64)) {
        *(u64*)dst = val;
        bytes -= sizeof(u64);
        dst += sizeof(u64);
    }
    
    while (bytes--) {
        *(u8*)dst = val;
        dst++;
    }
    
    return dst;
}
