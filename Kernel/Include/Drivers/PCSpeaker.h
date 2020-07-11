#pragma once

#include <Drivers/PIT.h>

namespace Kernel {
namespace PCSpeaker {

inline void play(u32 freq_hz) {
	PIT::set_frequency(PIT::CH2, freq_hz);
	
	u8 flags = IO::read_b(0x61);
	if (!(flags & 0x3))
		IO::write_b(0x61, flags | 0b11);
}

inline void stop() {
	u8 flags = IO::read_b(0x61) & ~(0b11);
	IO::write_b(0x61, flags); 
}

}
}
