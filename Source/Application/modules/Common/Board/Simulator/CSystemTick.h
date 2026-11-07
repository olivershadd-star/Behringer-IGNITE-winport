#pragma once
#include <stdint.h>
#include <chrono>
namespace Ignite {
class CSystemTick {
public:
    static uint32_t getTick(void)
    {
        static std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>( std::chrono::high_resolution_clock::now() - start); 
        return (uint32_t)duration.count();
    }
private:
};
} 
