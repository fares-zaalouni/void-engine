#pragma once
#include <iostream>
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

#ifdef _DEBUG
    

// Helper macro to print variadic arguments

#define ASSERT_RENDERER(condition, message, ...) \
if(!(condition)){\
std::cout << "Error: " << message << std::endl; \
std::cout << "Variadic args: "; \
PRINT_VARIADIC(__VA_ARGS__)\
std::exit(EXIT_FAILURE);\
}

#define PRINT_VARIADIC(...) \
        const char* args[] = {__VA_ARGS__}; \
        for (const auto& arg : args) { \
            std::cout << arg << " "; \
        } \
        std::cout << std::endl; 
    
#endif // _DEBUG

