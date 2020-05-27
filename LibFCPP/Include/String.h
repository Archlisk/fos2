#pragma once

#include <Memory.h>

namespace FCPP {

class String {
public:
	String() {}
    String(const char* str);
    String(u64 val);
    String(i64 val);
	String(u32 val);
    String(i32 val);
    String(char c);
    
    
    inline char* data() const { return m_data.get(); }
    inline u32 size() const { return m_size; }
    
private:
    Ptr<char> m_data = nullptr;
	u32 m_size = 0;
};

}
