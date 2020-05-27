#pragma once

inline u32 strlen(const char* str) {
	u32 len = 0;

	while (str[len] != 0)
		len++;

	return len;
}

inline char* strrev(char* str) {
	i16 i, j;
	u8 a;
	u32 len = strlen(str);
	
	for (i = 0, j = len - 1; i < j; i++, j--) {
		a = str[i];
		str[i] = str[j];
		str[j] = a;
	}
	
	return str;
}


inline char* utoa(u64 num, char* str) {
	u16 c = 0;

	while (num >= 10) {
		str[c++] = num % 10 + '0';
		num /= 10;
	}
	str[c++] = num + '0';
	str[c] = 0;

	strrev(str);

	return str;
}

inline char* itoa(i64 num, char* str) {
	u16 c = 0;
	
	u8 negative = 0;
	
	if (num < 0) {
		negative = true;
		num = -num;
	}

	while (num >= 10) {
		str[c++] = num % 10 + '0';
		num /= 10;
	}
	str[c++] = num + '0';
	if (negative)
		str[c++] = '-';
	str[c] = 0;

	strrev(str);

	return str;
}

inline char* htoa(u64 val, char* str) {
	u32 c = 0;

	while (val > 15) {
		u32 val_mod = val % 16;
		if (val_mod > 9)
			str[c++] = val_mod - 10 + 'A';
		else
			str[c++] = val_mod + '0';

		val /= 16;
	}

	u32 val_mod = val % 16;
	if (val_mod > 9)
		str[c++] = val_mod - 10 + 'A';
	else
		str[c++] = val_mod + '0';

	str[c] = 0;

	strrev(str);

	return str;
}
