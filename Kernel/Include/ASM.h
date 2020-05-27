#pragma once

namespace Kernel {
namespace ASM {
	inline void sti() {
		asm volatile ("sti");
	}
	
	inline void cli() {
		asm volatile ("cli");
	}
	
	template<int irq>
	inline void interrupt() {
		asm volatile ("int %0" : : "N"(irq));
	}
	
	inline void hlt() {
		asm volatile ("hlt");
	}
}

namespace IO {
	inline void write_b(u16 port, u8 val) {
		asm volatile ( "out %0, %1" : : "Nd"(port), "a"(val) );
	}
	
	inline void write_w(u16 port, u16 val) {
		asm volatile ( "out %0, %1" : : "Nd"(port), "a"(val) );
	}
	
	inline void write_d(u16 port, u32 val) {
		asm volatile ( "out %0, %1" : : "Nd"(port), "a"(val) );
	}
	
	
	
	inline u8 read_b(u16 port) {
		u8 val;
		asm volatile ( "in %0, %1" : "=a"(val) : "Nd"(port) );
		return val;
	}
	
	inline u16 read_w(u16 port) {
		u16 val;
		asm volatile ( "in %0, %1" : "=a"(val) : "Nd"(port) );
		return val;
	}
	
	inline u32 read_d(u16 port) {
		u32 val;
		asm volatile ( "in %0, %1" : "=a"(val) : "Nd"(port) );
		return val;
	}
	
	
	
	inline void wait() {
		asm volatile ( "outb 0x80, %%al" : : "a"(0) );
	}
}
}
