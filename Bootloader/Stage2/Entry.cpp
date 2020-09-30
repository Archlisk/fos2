#include <stdint.h>

#define PACKED __attribute__((packed))
#define FORCE_INLINE __attribute__((always_inline))

#define self (*this)

typedef uint64_t u64;
typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8;

typedef int64_t i64;
typedef int32_t i32;
typedef int16_t i16;
typedef int8_t i8;

typedef double f64;
typedef float f32;


#define KERNEL_ADDR (void*)0x100000

extern "C"
void* entry(void* kernel_data_addr, u32 kernel_bytes) {
	return copy(KERNEL_ADDR, kernel_data_addr, kernel_bytes);
}

