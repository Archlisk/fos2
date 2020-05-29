#pragma once

#include <OStream.h>
#include <String.h>

namespace FC {

class Console : public OStream {
public:
	void write(const char* data, u32 size) override;
	void write(char data) override;
};

inline OStream& operator<<(Console& stream, const String& data) {
	stream.write(data.data(), data.size());
	return stream;
}

inline Console out;

}
