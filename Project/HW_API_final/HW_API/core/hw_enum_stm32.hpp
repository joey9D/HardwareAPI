#pragma once

// Platform-specific GPIO enums for STM32
#ifdef STM32_PLATFORM

// Use our central HAL include that handles family detection
#include "../drivers/stm32_hal_wrapper/common/stm32_hal_inc.hpp"

namespace HW_API {
namespace STM32 {

enum class Mode : uint32_t
{
    Input = GPIO_MODE_INPUT,
    Output_Push_Pull = GPIO_MODE_OUTPUT_PP,
    Output_Open_Drain = GPIO_MODE_OUTPUT_OD,
    Alternate_Push_Pull = GPIO_MODE_AF_PP,
    Alternate_Open_Drain = GPIO_MODE_AF_OD,
    Analog = GPIO_MODE_ANALOG,
    Interrupt_Rising = GPIO_MODE_IT_RISING,
    Interrupt_Falling = GPIO_MODE_IT_FALLING,
    Interrupt_RisingFalling = GPIO_MODE_IT_RISING_FALLING,
    Event_Rising = GPIO_MODE_EVT_RISING,
    Event_Falling = GPIO_MODE_EVT_FALLING,
    Event_RisingFalling = GPIO_MODE_EVT_RISING_FALLING,
};

enum class Pull : uint32_t
{
    None = GPIO_NOPULL,
    Up = GPIO_PULLUP,
    Down = GPIO_PULLDOWN,
};

enum class Speed : uint32_t
{
    Low = GPIO_SPEED_FREQ_LOW,
    Medium = GPIO_SPEED_FREQ_MEDIUM,
    High = GPIO_SPEED_FREQ_HIGH,
    Very_High = GPIO_SPEED_FREQ_VERY_HIGH,
};

enum class Port : uint8_t
{
    A = 0,
    B = 1,
    C = 2,
    D = 3,
    E = 4,
    F = 5,
    G = 6,
    H = 7,
    I = 8,
};

enum class ExtiTrigger : uint32_t
{
    None = 0,
    Rising = GPIO_MODE_IT_RISING,
    Falling = GPIO_MODE_IT_FALLING,
    RisingFalling = GPIO_MODE_IT_RISING_FALLING,
};

} // namespace STM32
} // namespace HW_API

#endif // STM32_PLATFORM
