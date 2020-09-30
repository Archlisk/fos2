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
	
	void write_num(u64 num) {
		utoa((u64)num, convertion_buffer);
		write(convertion_buffer, strlen(convertion_buffer));
	}
	
	void write_signed_num(i64 num) {
		itoa((i64)num, convertion_buffer);
		write(convertion_buffer, strlen(convertion_buffer));
	}
	
	OStream& operator<<(const char* data) {
		write(data, strlen(data));
		return self;
	}

	OStream& operator<<(char data) {
		write(data);
		return self;
	}
	
	OStream& operator<<(void* data) {
		htoa((u64)data, convertion_buffer);
		write(convertion_buffer, strlen(convertion_buffer));
		return self;
	}
	
	OStream& operator<<(u64 data) { write_num(data); return self; }
	OStream& operator<<(u32 data) { write_num(data); return self; }
	OStream& operator<<(u16 data) { write_num(data); return self; }
	OStream& operator<<(u8 data)  { write_num(data); return self; }
	
	OStream& operator<<(i64 data) { write_signed_num(data); return self; }
	OStream& operator<<(i32 data) { write_signed_num(data); return self; }
	OStream& operator<<(i16 data) { write_signed_num(data); return self; }
	OStream& operator<<(i8 data)  { write_signed_num(data); return self; }
	
private:
	inline static char convertion_buffer[32];
};

}
