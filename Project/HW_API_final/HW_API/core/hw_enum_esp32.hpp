#pragma once

// Platform-specific GPIO enums for ESP32
#ifdef ESP_PLATFORM

#include "../drivers/esp32_hal_wrapper/esp32_hal_inc.hpp"

namespace HW_API
{
    namespace ESP32
    {
        // ============================================================================
        // GPIO Enums
        // ============================================================================

        enum class Mode
        {
            Disabled = GPIO_MODE_DEF_DISABLE,
            Input = GPIO_MODE_DEF_INPUT,
            Output = GPIO_MODE_DEF_OUTPUT,
            Output_Open_Drain = ((GPIO_MODE_DEF_OUTPUT) | (GPIO_MODE_DEF_OD)),
            Input_Output_Open_Drain = ((GPIO_MODE_DEF_INPUT) | (GPIO_MODE_DEF_OUTPUT) | (GPIO_MODE_DEF_OD)),
            Input_Output = ((GPIO_MODE_DEF_INPUT) | (GPIO_MODE_DEF_OUTPUT)),
        };

        enum class Pull
        {
            None = GPIO_FLOATING,
            Up = GPIO_PULLUP_ONLY,
            Down = GPIO_PULLDOWN_ONLY,
            UpDown = GPIO_PULLUP_PULLDOWN,
        };

        enum class Speed
        {
            Low = GPIO_DRIVE_CAP_0,
            Medium = GPIO_DRIVE_CAP_1,
            High = ((GPIO_DRIVE_CAP_2) | (GPIO_DRIVE_CAP_DEFAULT)),
            Very_High = GPIO_DRIVE_CAP_3,
            Max = GPIO_DRIVE_CAP_MAX,
        };

        enum class Alternate
        {
            None = 0 // ESP32 does not use Alternate
        };

        enum class Interrupt
        {
            Disabled = GPIO_INTR_DISABLE,
            Rising = GPIO_INTR_POSEDGE,
            Falling = GPIO_INTR_NEGEDGE,
            RisingFalling = GPIO_INTR_ANYEDGE,
            Low_Level = GPIO_INTR_LOW_LEVEL,
            High_Level = GPIO_INTR_HIGH_LEVEL,
            Max = GPIO_INTR_MAX,
        };

        // ============================================================================
        // SPI Enums
        // ============================================================================

        } // namespace ESP32
} // namespace HW_API

#endif // ESP_PLATFORM
