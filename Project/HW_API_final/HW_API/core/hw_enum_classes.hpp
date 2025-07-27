#pragma once

// Platform-specific enum includes
#ifdef STM32_PLATFORM
    #include "hw_enum_stm32.hpp"
    namespace HW_API {
        // Use STM32 enums as default
        using Mode = STM32::Mode;
        using Pull = STM32::Pull;
        using Speed = STM32::Speed;
        using Port = STM32::Port;
        using ExtiTrigger = STM32::ExtiTrigger;
    }
// ESP32 PLATFORM DISABLED FOR STM32-ONLY BUILD
// #elif ESP32_PLATFORM
//     #include "hw_enum_esp32.hpp"
//     namespace HW_API {
//         // Use ESP32 enums as default
//         using Mode = ESP32::Mode;
//         using Pull = ESP32::Pull;
//         using Speed = ESP32::Speed;
//         using Interrupt = ESP32::Interrupt;
//         
//         // ESP32 doesn't have Port concept, provide dummy
//         enum class Port : uint8_t { None = 0 };
//         enum class ExtiTrigger : uint32_t { None = 0 };
//     }
#endif

// Import into global namespace for backward compatibility
using namespace HW_API;

// Common enums for all platforms
enum class HAL_State
{
    OK = 0x00U,
    Error = 0x01U,
    Busy = 0x02U,
    Timeout = 0x03U
};


