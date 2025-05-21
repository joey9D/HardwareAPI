#pragma once

#include <cstdint>
#include <chrono>

namespace periph
{
class systick
{
public:
    static void init();

    static std::chrono::microseconds get();

    static std::chrono::microseconds get_past(std::chrono::microseconds timestamp);

    static void delay(uint32_t delay_ms);

private:
    systick() {}
};
} // namespace periph
