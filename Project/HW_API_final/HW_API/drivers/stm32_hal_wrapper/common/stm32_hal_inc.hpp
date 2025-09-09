#pragma once

// Central STM32 HAL include file for C++ projects
#ifdef STM32_PLATFORM

#ifdef __cplusplus
#include <cstddef>
#include <cstdint>
extern "C"
{
#else
#include <stddef.h>
#include <stdint.h>
#endif

// stm32c0xx
#if defined(STM32C0xx) || defined(STM32C031xx)
#include "stm32c0xx_hal_conf.h"
#include <stm32c0xx_hal.h>
#include <stm32c0xx_hal_rcc_ex.h>
// stm32g0xx
#elif defined(STM32G0xx) || defined(STM32G071xx) || defined(STM32G0B1xx)
#include <stm32g0xx_hal.h>
#else
#error "Unsupported STM32 family. Please define STM32C0xx, STM32G0xx, or add support for your family."
#endif

#ifdef __cplusplus
}
#endif

#endif // STM32_PLATFORM
