#include <String.h>

#include <CString.h>

using namespace FCPP;

String::String(const char* str) {
	u32 m_size = strlen(str);

	m_data = (char*)Memory::alloc(m_size);
	Memory::copy(m_data.get(), str, m_size);
}

String::String(u64 val) {
	m_data = (char*)Memory::alloc(32);
	utoa(val, m_data.get());
	
	m_size = strlen(m_data.get());
}

String::String(i64 val) {
	m_data = (char*)Memory::alloc(32);
	itoa(val, m_data.get());
	
	m_size = strlen(m_data.get());
}

String::String(u32 val) {
	m_data = (char*)Memory::alloc(12);
	utoa(val, m_data.get());
	
	m_size = strlen(m_data.get());
}

String::String(i32 val) {
	m_data = (char*)Memory::alloc(12);
	itoa(val, m_data.get());
	
	m_size = strlen(m_data.get());
}

String::String(char c) {
	m_data = New<char>(c);
	m_size = 1;
}
