#pragma once

#include <CString.h>

namespace FC {

class OStream {
public:
	virtual void write(const char*, u32) {}
	virtual void write(char) {}
	
	template<typename T>
	void write_binary(const T& data) {
		write((char*)&data, sizeof(T));
	}
	
	OStream& operator<<(const char* data) {
		write(data, strlen(data));
		return *this;
	}

	OStream& operator<<(char data) {
		write(data);
		return *this;
	}
	
	OStream& operator<<(void* data) {
		htoa((u64)data, convertion_buffer);
		write(convertion_buffer, strlen(convertion_buffer));
		return *this;
	}
	
	OStream& operator<<(u64 data) {
		utoa((u64)data, convertion_buffer);
		write(convertion_buffer, strlen(convertion_buffer));
		return *this;
	}
	
	OStream& operator<<(u32 data) {
		utoa((u64)data, convertion_buffer);
		write(convertion_buffer, strlen(convertion_buffer));
		return *this;
	}
	
	OStream& operator<<(u16 data) {
		utoa((u64)data, convertion_buffer);
		write(convertion_buffer, strlen(convertion_buffer));
		return *this;
	}
	
	OStream& operator<<(u8 data) {
		utoa((u64)data, convertion_buffer);
		write(convertion_buffer, strlen(convertion_buffer));
		return *this;
	}
	
private:
	inline static char convertion_buffer[32];
};

}
