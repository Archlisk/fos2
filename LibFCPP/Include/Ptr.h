#pragma once

namespace FCPP {

template<typename T>
class Ptr {
public:

	Ptr() {}
	Ptr(const Ptr&) = delete;
	
	Ptr(T* data) : m_data(data) {}

	~Ptr() { dealloc(); }
	
	Ptr<T>& operator=(T* data) {
		if (m_data)
			free(m_data);
		m_data = data;
		return *this;
	}
	
	T* operator->() const { return m_data; }
	T* operator&() const { return m_data; }
	T& operator*() { return *m_data; }
	
	T* get() const { return m_data; }
	void reset() { m_data = nullptr; }
	
	void dealloc() {
		if (m_data)
			free<T>(m_data);
		m_data = nullptr;
	}
	
private:
	T* m_data = nullptr;
};

}
