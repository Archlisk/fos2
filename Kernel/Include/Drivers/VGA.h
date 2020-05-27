#pragma once

namespace VGA {

enum class FGColor4B {
	Black = 0x00,
	Blue = 0x01,
	Green = 0x02,
	Cyan = 0x03,
	Red = 0x04,
	Magenta = 0x05,
	Brown = 0x06,
	White = 0x07,
	Gray = 0x08,
	LightBlue = 0x09,
	LightGreen = 0x0A,
	LightCyan = 0x0B,
	LightRed = 0x0C,
	LightMagenta = 0x0D,
	Yellow = 0x0E,
	BrightWhite = 0x0F
};

enum class BGColor4B {
	Black = 0x00,
	Blue = 0x10,
	Green = 0x20,
	Cyan = 0x30,
	Red = 0x40,
	Magenta = 0x50,
	Brown = 0x60,
	White = 0x70,
	Gray = 0x80,
	LightBlue = 0x90,
	LightGreen = 0xA0,
	LightCyan = 0xB0,
	LightRed = 0xC0,
	LightMagenta = 0xD0,
	Yellow = 0xE0,
	BrightWhite = 0xF0
};

inline u8 operator|(FGColor4B fg, BGColor4B bg) {
	return (u8)fg | (u8)bg;
}

inline u8 operator|(BGColor4B bg, FGColor4B fg) {
	return (u8)fg | (u8)bg;
}

}
