#pragma once

// Central ESP32-IDF include file for C++ projects (equivalent to stm32_hal_inc.hpp)
#ifdef ESP32_PLATFORM

// Step 1: Include standard C types BEFORE any ESP-IDF headers
#ifdef __cplusplus
#include <cstdint>
#include <cstddef>
extern "C"
{
#else
#include <stdint.h>
#include <stddef.h>
#endif

// Step 2: ESP32-IDF main headers (equivalent to stm32xxx_hal.h)
#include "esp_system.h"        // Main ESP32 system header
#include "freertos/FreeRTOS.h" // FreeRTOS main header
#include "esp_timer.h"         // Timer functions

#ifdef __cplusplus
}
#endif

#endif // ESP32_PLATFORM
