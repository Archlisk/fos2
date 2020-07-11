#pragma once

#include <ASM.h>

namespace Kernel {
namespace PIT {

enum Channel {
	CH0 = 0,
	CH1 = 1,
	CH2 = 2
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
