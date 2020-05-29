#pragma once

#include <Memory.h>
#include <CString.h>

#include <TTY.h>

namespace FC {

class String {
public:
	String() {}

	String(const char* str) {
		m_size = strlen(str);
		m_data = (char*)alloc(m_size);
		Memory::copy(m_data, str, m_size);
	}
	
	String(const String& other) {
		m_size = other.size();
		m_data = (char*)alloc(m_size);
		Memory::copy(m_data, other.data(), m_size);
	}
    
    ~String() { free(m_data); }
    
    String& operator=(const String& other) {
		m_size = other.size();
		m_data = (char*)realloc(m_data, m_size);
		Memory::copy(m_data, other.data(), m_size);
		return *this;
    }
    
    char* data() const { return m_data; }
    u32 size() const { return m_size; }
    
    void clear() { 
		free(m_data); 
		m_data = nullptr;
		m_size = 0;
	}
        
private:
    char* m_data = nullptr;
	u32 m_size = 0;
};

OStream& operator<<(OStream& stream, const String& str) {
	stream.write(str.data(), str.size());
	return stream;
}


}
