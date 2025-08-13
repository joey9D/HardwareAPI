/*
 * esp32c6_hw.cpp
 *
 *  Created on: Aug 1, 2025
 *      Author: jan.kristel
 */

#include "esp32c6_devkitc1_hw.hpp"

// ESP32-IDF includes
#include "../../drivers/esp32_hal_wrapper/esp32_hal_inc.hpp"
// #include "driver/gpio.h" // Already included in esp32_hal_inc.hpp
// #include "esp_chip_info.h"  // Not needed anymore
// #include "esp_flash.h"      // Not needed anymore
// #include "spi_flash_mmap.h" // Not needed anymore
// #include "esp_clk_tree.h"   // Not needed anymore

// HW_API includes for pin configuration
#include "../../../core/project_config.hpp"

// Logging tag for this module (currently unused)
// static const char *TAG = "ESP32C6_HW";

//================================================================================
// System Initialization
//================================================================================

void Esp32c6_hw::init_sys()
{
    // Empty implementation - ESP-IDF handles all system initialization automatically:
    // - Bootloader initializes flash, memory, basic peripherals
    // - FreeRTOS kernel is started
    // - Hardware abstraction layer is ready
    // - Clock system is configured via sdkconfig
}

//================================================================================
// Clock Initialization
//================================================================================

void Esp32c6_hw::init_clock()
{
    // Empty implementation - ESP-IDF handles clock configuration automatically:
    // 1. sdkconfig settings (CONFIG_ESP32C6_DEFAULT_CPU_FREQ_MHZ)
    // 2. Automatic crystal detection
    // 3. PLL configuration for optimal performance
}

//================================================================================
// Delay Function
//================================================================================

void Esp32c6_hw::delay(uint32_t ms)
{
    // Use simple esp_timer delay instead of FreeRTOS to avoid dependency issues
    // vTaskDelay(pdMS_TO_TICKS(ms));  // Commented out to avoid FreeRTOS dependency

    // Use ESP-IDF's high-resolution timer for delay
    int64_t start_time = esp_timer_get_time();          // Keep as int64_t to match function return type
    int64_t delay_us = static_cast<int64_t>(ms * 1000); // Convert ms to microseconds
    while ((esp_timer_get_time() - start_time) < delay_us)
    {
        // Busy wait - not ideal but works without FreeRTOS
    }
}

//================================================================================
// Pin Initialization
//================================================================================

/**
 * @brief Initialize all Pins defined in BoardPins from project_config.hpp
 */
void Esp32c6_hw::initAllPins()
{
    for (auto pin : boardPins.allPins)
    {
        pin->gpio_init();
    }
}

//================================================================================
// ESP32-specific Member Functions
//================================================================================

uint32_t Esp32c6_hw::getFreeHeapSize() const
{
    return esp_get_free_heap_size();
}

uint32_t Esp32c6_hw::getMinimumFreeHeapSize() const
{
    return esp_get_minimum_free_heap_size();
}

void Esp32c6_hw::restart() const
{
    // ESP_LOGI(TAG, "Restarting ESP32...");  // Commented out to avoid ESP_LOGI dependency
    esp_restart();
}
