#pragma once

namespace FCPP {

class String {
public:
    String(const char* str);
    
private:
    char* m_data;
};

}
