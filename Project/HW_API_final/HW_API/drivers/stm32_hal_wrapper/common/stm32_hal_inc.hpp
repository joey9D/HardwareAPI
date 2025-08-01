#pragma once

// Central STM32 HAL include file for C++ projects
#ifdef STM32_PLATFORM

// Step 1: Include standard C types BEFORE any HAL headers
#ifdef __cplusplus
#include <cstdint>
#include <cstddef>
extern "C"
{
#else
#include <stdint.h>
#include <stddef.h>
#endif

// Step 2: Family-specific includes based on compile-time definitions
#if defined(STM32C0xx) || defined(STM32C031xx)
    // STM32C0xx family - proper include order
    #include <stm32c0xx_hal.h>      // Main HAL header includes config and all modules
#elif defined(STM32G0xx) || defined(STM32G071xx) || defined(STM32G0B1xx)
    // STM32G0xx family - proper include order  
    #include <stm32g0xx_hal.h>      // Main HAL header includes config and all modules
#else
    #error "Unsupported STM32 family. Please define STM32C0xx, STM32G0xx, or add support for your family."
#endif

#ifdef __cplusplus
}
#endif

#endif // STM32_PLATFORM
