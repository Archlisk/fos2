#pragma once

namespace FC {

class IStream {
public:

	virtual void read(u8*, u32) {}

	inline IStream& operator>>(u8*) {
		//read(data);
		return *this;
	}

};

}
