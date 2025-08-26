#pragma once

/**
 * ESP32 Standard includes
 */
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

/**
 * include HW_API headers - updated for ESP32 structure
 */
#include "hw_factory.hpp"
// hw_interface.hpp is included via hw_factory.hpp - no need to include directly
#include "project_config.hpp"

// Platform-specific includes for ESP32
#ifdef ESP_PLATFORM
#include "esp32_hal_inc.hpp" // ESP32 HAL wrapper
#endif

// ESP32 logging tag
// static const char *TAG = "HW_API_ESP32";
