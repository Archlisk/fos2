#pragma once

#include <KernelData.h>

#include <OStream.h>

using FC::OStream;

class TTY : public OStream {
public:
	void write(const char* data, u32 size) override {
		Kernel::KernelData::tty.write_str(data, size);
	}
	
	void write(char data) override {
		Kernel::KernelData::tty.write_char(data);
	}
};

inline TTY out;
