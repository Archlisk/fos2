#pragma once

#include <FCPPTypes.h>

namespace FCPP {
namespace Memory {

    void* copy(void* dst, const void* src, u32 bytes);
    void* set(void* dst, const u8 val, u32 bytes);

}
}
