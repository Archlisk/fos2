#include <Drivers/PIT.h>

#define PIT_DATA_CHANNEL0 0x40
#define PIT_DATA_CHANNEL1 0x41
#define PIT_DATA_CHANNEL2 0x42
#define PIT_COMMAND 0x43

#define PIT_CMD_CHANNEL0	0b00000000
#define PIT_CMD_CHANNEL1	0b01000000
#define PIT_CMD_CHANNEL2	0b10000000

#define PIT_CMD_SQUARE_WAVE 0b00000110

#define PIT_CMD_ACCESS_LOW	0b00010000
#define PIT_CMD_ACCESS_HIGH	0b00100000
#define PIT_CMD_ACCESS_FULL (PIT_CMD_ACCESS_LOW | PIT_CMD_ACCESS_HIGH)

using namespace Kernel;

u64 pit_current_ticks;

void PIT::on_tick() {
	pit_current_ticks++;
}

void PIT::set_frequency(PIT::Channel channel, u32 freq_hz) {
	if (!freq_hz)
		return;
	
	u32 divisor = 1193180 / freq_hz;
	
	u16 data_port = PIT_DATA_CHANNEL0 + (u8)channel;
	u8 command = ((u8)channel << 6) | PIT_CMD_SQUARE_WAVE | PIT_CMD_ACCESS_FULL;
	
	IO::write_b(PIT_COMMAND, command);
	IO::write_b(data_port, divisor);
	IO::write_b(data_port, divisor >> 8);
}

u64 PIT::time() {
	return pit_current_ticks;
}
