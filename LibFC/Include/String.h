#pragma once

#include <Memory.h>
#include <CString.h>
#include <OStream.h>

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
		return self;
    }
    
    String& operator+=(const String& other) {
		u32 new_size = m_size + other.size();
		m_data = (char*)realloc(m_data, new_size);
		Memory::copy(m_data + m_size, other.data(), other.size());
		m_size = new_size;
		return self;
    }
    
	String& operator+=(const char* other) {
		u32 other_size = strlen(other);
		u32 new_size = m_size + other_size;
		m_data = (char*)realloc(m_data, new_size);
		Memory::copy(m_data + m_size, other, other_size);
		m_size = new_size;
		return self;
    }
    
	String& operator+=(char other) {
		m_data = (char*)realloc(m_data, m_size + 1);
		m_data[m_size] = other;
		m_size++;
		return self;
    }
    
	String operator+(const String& other) {
		FC::String new_str(self);
		new_str += other;
		return new_str;
    }
    
	String operator+(const char* other) {
		FC::String new_str(self);
		new_str += other;
		return new_str;
    }
    
	String operator+(char other) {
		FC::String new_str(self);
		new_str += other;
		return new_str;
    }
    
    u8 operator==(const String& other) {
		return streq(m_data, other.data());
    }
    
	u8 operator==(const char* other) {
		return streq(m_data, other);
    }
    
    char* data() const { return m_data; }
    u32 size() const { return m_size; }
    
    void clear() { 
		free(m_data); 
		m_data = nullptr;
		m_size = 0;
	}
	
	const char* begin() const { return m_data; }
	const char* end() const { return m_data + m_size; }
private:
    char* m_data = nullptr;
	u32 m_size = 0;
};

inline OStream& operator<<(OStream& stream, const String& str) {
	stream.write(str.data(), str.size());
	return stream;
}


}
