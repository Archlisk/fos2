#include <ArgumentHandler.h>

#include <iostream>

std::vector<std::string> ArgumentHandler::Args(int argc, char** argv) {
    std::vector<std::string> args;
    
    for (int i = 1; i < argc; i++) {
        const std::string arg_str = argv[i];
        
        auto it = m_switches.find(arg_str);
        
        if (it != m_switches.end()) {
            
            switch (it->second.type) {
				case Switch::Type::String:
					if (i + 1 < argc)
						*(std::string*)it->second.data = argv[++i];
					else
						std::cout << "ERROR! '" << arg_str << "' Requires a valid argument" << std::endl;
					break;
				
				case Switch::Type::Bool:
					*(bool*)it->second.data = true;
					break;
					
				default:
					std::cout << "WARNING! Unknown error while parsing arguments" << std::endl;
					break;
            }
        }
        else 
            args.push_back(arg_str);
    }
    
    return args;
}
