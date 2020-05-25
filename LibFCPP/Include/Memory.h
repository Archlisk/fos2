#pragma once

#include <FCPPTypes.h>

namespace FCPP {
namespace Memory {

    void* copy(void* dst, const void* src, u32 bytes);
    void* set(void* dst, u64 val, u32 bytes);
}
}
