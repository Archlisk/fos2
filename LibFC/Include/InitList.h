#pragma once

namespace std {

template<class T>
class initializer_list {
public:
	initializer_list() {}
	
	u32 size() const { return m_len; }
	
	const T* begin() const { return m_array; }
	const T* end() const { return begin() + size(); }

private:
	const T* m_array = nullptr;
	size_t	m_len = 0;

	initializer_list(const T* array, size_t size)
		: m_array(array), m_len(size) {}
};

}

namespace FC {
	template<typename T>
	using InitList = std::initializer_list<T>;
}
