#pragma once

// Platform-specific GPIO enums for STM32
#ifdef STM32_PLATFORM

// Only include the minimal HAL headers needed for GPIO definitions
#include "stm32c0xx_hal_conf.h"
#include "stm32c0xx_hal_gpio.h"

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
    Input_IT_Rising = GPIO_MODE_IT_RISING,
    Input_IT_Falling = GPIO_MODE_IT_FALLING,
    Input_IT_RisingFalling = GPIO_MODE_IT_RISING_FALLING,
    Input_EVT_Rising = GPIO_MODE_EVT_RISING,
    Input_EVT_Falling = GPIO_MODE_EVT_FALLING,
    Input_EVT_RisingFalling = GPIO_MODE_EVT_RISING_FALLING,
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
