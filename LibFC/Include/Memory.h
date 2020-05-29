#pragma once

namespace FC {

namespace Memory {
	u8 compare(const void* area1, const void* area2, u32 bytes);
    void* copy(void* dst, const void* src, u32 bytes);
    void* set(void* dst, u64 val, u32 bytes);
}

}
