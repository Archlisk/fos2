#pragma once

#include <Memory.h>
#include <InitList.h>

#include <TTY.h>

namespace FC {

template<typename T>
class Vector {
public:
	Vector() {}
	Vector(const InitList<T>& list) {
		for (const T& elem : list)
			push(elem);
	}
	
	Vector(const Vector<T>& other) {
		m_elems = other.size();
		m_alloc_bytes = m_elems * sizeof(T);
		m_data = alloc(m_alloc_bytes);
		
		for (u32 i = 0; i < m_elems; i++)
			new (&m_data[i]) T(other.data()[i]);
	}
	
	~Vector() { clear(); }
	
	void push(const T& other) {
		m_elems += 1;

		if (m_alloc_bytes < m_elems	* sizeof(T)) {
			m_alloc_bytes = m_elems * 2 * sizeof(T);
			m_data = (T*)realloc(m_data, m_alloc_bytes);
		}
		
		m_data[m_elems - 1] = other;
	}
	
	template<typename... Targs>
	void emplace(const Targs&... args) {
		m_elems += 1;

		if (m_alloc_bytes < m_elems	* sizeof(T)) {
			m_alloc_bytes = m_elems * 2 * sizeof(T);
			m_data = (T*)realloc(m_data, m_alloc_bytes);
		}
		
		new (&m_data[m_elems - 1]) T(args...);
	}
	
	void insert(u32 index, const T& val) {
		m_elems += 1;

		if (m_alloc_bytes < m_elems	* sizeof(T)) {
			m_alloc_bytes = m_elems * 2 * sizeof(T);
			m_data = (T*)realloc(m_data, m_alloc_bytes);
		}
		
		Memory::copy(&m_data[index + 1], &m_data[index], (m_elems - index) * sizeof(T));
		Memory::set(&m_data[index], 0, sizeof(T));
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
		for (T& elem : self)
			elem.~T();
		
		free(m_data);
		m_data = nullptr;
		m_elems = 0;
		m_alloc_bytes = 0;
	}
	
	void resize() {
		m_alloc_bytes = m_elems * sizeof(T);
		m_data = (T*)realloc(m_data, m_alloc_bytes);
	}
	
	T& top() { return m_data[m_elems - 1]; }
	
	u32 size() { return m_elems; }
	T* data() { return m_data; }
	
	T* begin() { return m_data; }
	T* end() { return (T*)((u8*)m_data + m_elems * sizeof(T)); }
	
	FORCE_INLINE T& operator[](u32 index) { return m_data[index]; }
	
	
	const T& top() const { return m_data[m_elems - 1]; }
	
	const T* begin() const { return m_data; }
	const T* end() const { return (T*)((u8*)m_data + m_elems * sizeof(T)); }
	
	FORCE_INLINE const T& operator[](u32 index) const { return m_data[index]; }

private:
	T* m_data = nullptr;
	u32 m_elems = 0;
	u32 m_alloc_bytes = 0;
};

}
