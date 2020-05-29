#pragma once

#include <Memory.h>

namespace FC {

template<typename T>
class Vector {
public:
	Vector() {}
	~Vector() { clear(); }
	
	template<typename... Targs>
	void push(const Targs&... args) {
		m_elems += 1;

		if (m_alloc_bytes < m_elems	* sizeof(T)) {
			m_alloc_bytes = m_elems * 2 * sizeof(T);
			m_data = (T*)realloc(m_data, m_alloc_bytes);
		}
		
		m_data[m_elems - 1] = T(args...);
	}
	
	void insert(u32 index, const T& val) {
		m_elems += 1;

		if (m_alloc_bytes < m_elems	* sizeof(T)) {
			m_alloc_bytes = m_elems * 2 * sizeof(T);
			m_data = (T*)realloc(m_data, m_alloc_bytes);
		}
		
		Memory::copy(&m_data[index + 1], &m_data[index], (m_elems - index) * sizeof(T));
		m_data[index] = val;
	}
	
	void pop() {
		m_elems--;
		m_data[m_elems].~T();
		
		if (m_elems < m_alloc_bytes / sizeof(T))
			resize();
	}
	
	void erase(u32 index) {
		m_data[index].~T();
		Memory::copy(&m_data[index], &m_data[index + 1], (m_elems-- - index) * sizeof(T));
		
		if (m_elems < m_alloc_bytes / sizeof(T))
			resize();
	}
	
	void clear() {
		for (u32 i = 0; i < m_elems; i++)
			m_data[i].~T();
		
		free(m_data);
		m_data = nullptr;
		m_elems = 0;
		m_alloc_bytes = 0;
	}
	
	void resize() {
		m_alloc_bytes = m_elems * sizeof(T);
		m_data = (T*)realloc(m_data, m_alloc_bytes);
	}
	
	u32 size() { return m_elems; }
	
	T* begin() { return m_data; }
	T* end() { return (T*)((u8*)m_data + m_elems * sizeof(T)); }
	
	FORCE_INLINE T& operator[](u32 index) { return m_data[index]; }

private:
	u64 a, b, c, d, e, f, g;
	T* m_data = nullptr;
	u32 m_elems = 0;
	u32 m_alloc_bytes = 0;
	u64 a1, b2, c3, d5, e6, f7, g8;
};

}
