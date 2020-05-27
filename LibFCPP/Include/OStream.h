#pragma once

#include <String.h>
#include <CString.h>

namespace FCPP {

class OStream {
public:
	virtual void write(const char*, u32) {}
	virtual void write(char) {}
};

inline OStream& operator<<(OStream& stream, const char* data) {
	stream.write(data, strlen(data));
	return stream;
}

inline OStream& operator<<(OStream& stream, char data) {
	stream.write(data);
	return stream;
}

inline OStream& operator<<(OStream& stream, const String& data) {
	stream.write(data.data(), data.size());
	return stream;
}

}
