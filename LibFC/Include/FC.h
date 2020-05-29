#pragma once

#include <stdint.h>
#include <stddef.h>

#define PACKED __attribute__((packed))
#define FORCE_INLINE __attribute__((always_inline))

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

#ifdef KERNEL
	#include <KernelData.h>
	
	inline void* alloc(u32 bytes) { return Kernel::KernelData::heap.alloc(bytes); }
	inline void free(void* addr) { Kernel::KernelData::heap.free(addr); }
	inline void* realloc(void* addr, u32 bytes) { return Kernel::KernelData::heap.realloc(addr, bytes); }
#else
	inline void* alloc(u32 bytes);
	inline void free(void* addr);
	inline void* realloc(void* addr, u32 bytes);
#endif

#include <Ptr.h>

template<typename T, typename... Targs>
T* create(const Targs&... args) {
	T* new_t = (T*)alloc(sizeof(T));
	*new_t = T(args...);
	return new_t;
}

template<typename T>
void destroy(T& target) {
	target.~T();
	free(&target);
}
