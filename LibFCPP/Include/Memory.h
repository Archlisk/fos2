#pragma once

namespace FCPP {

namespace Memory {
    void* copy(void* dst, const void* src, u32 bytes);
    void* set(void* dst, u64 val, u32 bytes);
    
    void* alloc(u32 bytes);
    void free(void* addr);
}

template<typename T>
class Ptr {
public:

	Ptr() {}
	inline Ptr(T* data) : m_data(data) {}

	inline ~Ptr() {
		if (m_data)
			Memory::free(m_data); 
	}
	
	inline Ptr<T>& operator=(T* data) {
		if (m_data)
			Memory::free(m_data);
		m_data = data;
		return *this;
	}
	
	inline T* operator->() { return m_data; }
	inline T* operator&() { return m_data; }
	inline T& operator*() { return *m_data; }
	
	inline T* get() const { return m_data; }
	
private:
	T* m_data = nullptr;
};

template<typename T, typename ... Arguments>
inline T* New(const Arguments&... args) {
	T* new_t = (T*)FCPP::Memory::alloc(sizeof(T));
	*new_t = T(args...);
	return new_t;
}


}
