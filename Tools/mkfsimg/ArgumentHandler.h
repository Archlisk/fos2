#pragma once

#include <map>
#include <vector>
#include <string>

struct Switch {

    enum class Type {
        None,
        String,
        Bool
    };
    
    Switch() : type(Type::None), data(nullptr) {}
    Switch(std::string* data) : type(Type::String), data(data) {}
    Switch(bool* data) : type(Type::Bool), data(data) {}
    
    Type type;
    void* data;
};

class ArgumentHandler {
public:
	inline void AddSwitch(const std::string& key, std::string* data) { m_switches[key] = Switch(data); }
	inline void AddSwitch(const std::string& key, bool* data) { m_switches[key] = Switch(data); }
	
	std::vector<std::string> Args(int argc, char** argv);
	
private:
	std::map<std::string, Switch> m_switches;
};

