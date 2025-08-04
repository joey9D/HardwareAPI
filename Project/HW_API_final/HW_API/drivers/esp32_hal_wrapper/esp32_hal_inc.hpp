#pragma once

// ESP32-IDF include file for C++ projects
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

// Step 2: Essential ESP32 headers only (avoiding complex FreeRTOS components)
#include "esp_system.h"  // Main ESP32 system header
#include "driver/gpio.h" // GPIO driver functions
#include "esp_timer.h"   // Timer functions - needed for esp_timer_get_time()
#include "esp_log.h"     // Logging functions - needed for ESP_LOGI

#ifdef __cplusplus
}
#endif

#endif // ESP32_PLATFORM
