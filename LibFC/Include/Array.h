#pragma once

namespace FC {

template<typename T, u32 elements>
class Array {
public:
	u32 size() const { return elements; }
	
	T& operator[](u32 index) const { return m_data[index]; }

private:
	T m_data[elements];
};

}
