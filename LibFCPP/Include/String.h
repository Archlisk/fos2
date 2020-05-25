#pragma once

#include <FCPPTypes.h>

static inline u32 strlen(const char* str) {
	u32 len = 0; 

	while (str[len] != 0)
		len++;

	return len;
}

static inline char* strrev(char* str) {
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


static inline char* itoa(u64 num) {
	static char str[21] = {0};
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

static inline char* htoa(u64 val) {
	static char str[17] = {0};
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


namespace FCPP {

class String {
public:
    String(const char* str) {}
    
    inline const char* data() const { return m_data; }
    inline u32 size() const { return m_size; }
    
private:
    char* m_data;
	u32 m_size;
};

}
