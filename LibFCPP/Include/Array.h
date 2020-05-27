#pragma once

namespace FCPP {

template<typename T, u32 elements>
class Array {
public:
	u32 size() const { return elements; }
	
	inline T& operator[](u32 index) { return m_data[index]; }

private:
	T m_data[elements];
};

}
