#pragma once

#include <Drivers/VGA.h>

class Terminal {
public:
	Terminal(u16* data, u16 width, u16 height)
		: m_data(data), m_width(width), m_height(height) {}

	u32 write_str(const char* str, u32 len);
	u32 write_str(const char* str);
	char write_char(char symbol);

	inline void set_color(VGA::FGColor4B fg, VGA::BGColor4B bg) { m_color = fg | bg; }
	inline void set_color(VGA::FGColor4B fg) { m_color &= 0xF0; m_color |= (u8)fg; }
	inline void set_color(VGA::BGColor4B bg) { m_color &= 0x0F; m_color |= (u8)bg; }
	
	inline u8 get_color() const { return m_color; }

private:
	u16* m_data;
	u16 m_position = 0;

	u16 m_width, m_height;

	u8 m_color = 0x0F;
};
