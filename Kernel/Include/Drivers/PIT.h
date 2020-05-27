#pragma once

#include <ASM.h>

namespace Kernel {
namespace PIT {

enum class Channel {
	C0 = 0,
	C1 = 1,
	C2 = 2
};

void on_tick();
void set_frequency(Channel channel, u32 freq_hz);

u64 time();

inline void sleep(u64 ticks) {
	u64 sleep_until = PIT::time() + ticks;
	
	while (PIT::time() < sleep_until)
		ASM::hlt();
}

}
}
