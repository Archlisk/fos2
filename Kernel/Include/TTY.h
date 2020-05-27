#pragma once

#include <Drivers/VGA.h>

#include <KernelData.h>

#include <OStream.h>
#include <String.h>

using FCPP::OStream;

class TTY : public OStream {
public:
	enum class TextMode {
		Text,
		Hex
	};

	void write(const char* data, u32 size) override {
		Kernel::KernelData::tty.write_str(data, size);
	}
	
	void write(char data) override {
		Kernel::KernelData::tty.write_char(data);
	}
	
	TextMode text_mode() { return m_text_mode; }
	void set_text_mode(TextMode mode) { m_text_mode = mode; }
	
private:
	TextMode m_text_mode = TextMode::Text;
};

inline char m_convertion_buffer[32];

inline TTY& operator<<(TTY& stream, VGA::FGColor4B fg) {
	Kernel::KernelData::tty.set_color(fg);
	return stream;
}

inline TTY& operator<<(TTY& stream, VGA::BGColor4B bg) {
	Kernel::KernelData::tty.set_color(bg);
	return stream;
}

inline TTY& operator<<(TTY& stream, const char* data) {
	stream.write(data, strlen(data));
	return stream;
}

inline TTY& operator<<(TTY& stream, char data) {
	stream.write(data);
	return stream;
}

inline TTY& operator<<(TTY& stream, int data) {
	m_convertion_buffer[0] = 0;

	if (stream.text_mode() == TTY::TextMode::Text)
		itoa(data, m_convertion_buffer);
	else if (stream.text_mode() == TTY::TextMode::Hex)
		htoa(data, m_convertion_buffer);
		
	stream.set_text_mode(TTY::TextMode::Text);
	stream.write(m_convertion_buffer, strlen(m_convertion_buffer));
	return stream;
}

inline TTY& operator<<(TTY& stream, const FCPP::String& data) {
	stream.write(data.data(), data.size());
	return stream;
}

inline TTY& operator<<(TTY& stream, const TTY::TextMode mode) {
	stream.set_text_mode(mode);
	return stream;
}

inline TTY out;
