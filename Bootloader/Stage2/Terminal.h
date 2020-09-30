#pragma once

#define CONSOLE_WIDTH 80
#define CONSOLE_HEIGHT 25

void putchar(char c) {
	static u8 cursor_row = 0;
	static u8 cursor_col = 0;

	switch (c) {
		case '\n':
			cursor_row++;
			cursor_col = 0;
			break;

		default:
			*(((u16*)0xB8000) + cursor_col++ + (cursor_row * CONSOLE_WIDTH)) = c | (0x0F << 8);
			if (cursor_col == CONSOLE_WIDTH) {
				cursor_col = 0;
				cursor_row++;
			}
			break;
	}
}

void printstr(const char* str) {
	while (*str != '\0')
		putchar(*(str++));
}
