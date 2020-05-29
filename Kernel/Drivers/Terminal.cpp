#include <Drivers/Terminal.h>

#include <Memory.h>

#define TERMINAL_TAB_SIZE 8

using namespace Kernel;

#include <Drivers/PIT.h>

u32 Terminal::write_str(const char* str, u32 len) {
	for (u32 i = 0; i < len; i++)
		write_char(str[i]);
	
	return len;
}

u32 Terminal::write_str(const char* str) {
	u32 i = 0;
	while (str[i] != 0)
		write_char(str[i++]);
	
	return i;
}

char Terminal::write_char(char symbol) {
	
	switch (symbol) {
	case '\n':
        m_position += m_width - (m_position % m_width);
        break;
        
    case '\t':
        m_position += TERMINAL_TAB_SIZE - (m_position % TERMINAL_TAB_SIZE);
        break;
        
    case '\b':
        m_data[--m_position] = (u16)0x00 | ((u16)m_color << 8);
        break;
        
    default:
        m_data[m_position++] = (u16)symbol | ((u16)m_color << 8);
        break;
	}
	
	if (m_position >= m_width * m_height) {
        FC::Memory::copy(m_data, (char*)m_data + m_width * 2, m_width * (m_height - 1) * 2);
        FC::Memory::set((char*)m_data + m_width * (m_height - 1) * 2, 0, m_width * 2);
        m_position -= m_width + m_position % m_width;
    }
	
	return symbol;
}
