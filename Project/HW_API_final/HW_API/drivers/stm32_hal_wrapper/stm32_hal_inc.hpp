#pragma once

// Central STM32 HAL include file for C++ projects
#ifdef STM32_PLATFORM

// Step 1: Include standard C types BEFORE any HAL headers
#ifdef __cplusplus
#include <cstdint>
#include <cstddef>
extern "C" {
#else
#include <stdint.h>
#include <stddef.h>
#endif

// Step 2: Include CMSIS device header FIRST (provides register definitions)
#include "stm32c0xx.h"

// Step 3: Include HAL configuration (this now finds all types correctly)
#include "stm32c0xx_hal_conf.h"

// Step 4: Include main HAL header (this pulls in all enabled modules)
#include "stm32c0xx_hal.h"

#ifdef __cplusplus
}
#endif

#endif // STM32_PLATFORM
