/*
 * esp32c6_hw.cpp
 *
 *  Created on: Aug 1, 2025
 *      Author: jan.kristel
 */

#include "esp32c6_devkitc1_hw.hpp"

// ESP32-IDF includes
#include "../../drivers/esp32_hal_wrapper/esp32_hal_inc.hpp"
#include "driver/gpio.h" // GPIO driver
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "spi_flash_mmap.h"
#include "esp_clk_tree.h"

// HW_API includes for pin configuration
#include "../../../core/pin_config.hpp"

// Logging tag for this module
static const char *TAG = "ESP32C6_HW";

//===============================================================================
// System Initialization
//===============================================================================

void Esp32c6_hw::init_sys()
{
    ESP_LOGI(TAG, "ESP32-C6 system already initialized by ESP-IDF");

    // ESP-IDF handles all low-level system initialization automatically:
    // - Bootloader initializes flash, memory, basic peripherals
    // - FreeRTOS kernel is started
    // - Hardware abstraction layer is ready
    // - Clock system is configured via sdkconfig

    // Log system information for verification
    esp_chip_info_t chip_info;
    esp_chip_info(&chip_info);

    ESP_LOGI(TAG, "ESP32-C6 chip with %d CPU core(s), WiFi%s%s",
             chip_info.cores,
             (chip_info.features & CHIP_FEATURE_BT) ? "/BT" : "",
             (chip_info.features & CHIP_FEATURE_BLE) ? "/BLE" : "");

    ESP_LOGI(TAG, "Silicon revision %d", chip_info.revision);
    ESP_LOGI(TAG, "%dMB %s flash",
             (int)(spi_flash_get_chip_size() / (1024 * 1024)),
             (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");
}

//===============================================================================
// Clock Initialization
//===============================================================================

void Esp32c6_hw::init_clock()
{
    ESP_LOGI(TAG, "ESP32-C6 clock system configured by ESP-IDF");

    // ESP-IDF automatically configures the clock system based on:
    // 1. sdkconfig settings (CONFIG_ESP32C6_DEFAULT_CPU_FREQ_MHZ)
    // 2. Automatic crystal detection
    // 3. PLL configuration for optimal performance

    // No manual clock configuration needed - just verify current settings
    uint32_t cpu_freq = esp_clk_cpu_freq();
    uint32_t apb_freq = esp_clk_apb_freq();
    uint32_t xtal_freq = esp_clk_xtal_freq();

    ESP_LOGI(TAG, "Current clock configuration:");
    ESP_LOGI(TAG, "  CPU frequency: %d MHz", cpu_freq / 1000000);
    ESP_LOGI(TAG, "  APB frequency: %d MHz", apb_freq / 1000000);
    ESP_LOGI(TAG, "  XTAL frequency: %d MHz", xtal_freq / 1000000);
}

//===============================================================================
// Delay Function
//===============================================================================

void Esp32c6_hw::delay(uint32_t ms)
{
    // Use FreeRTOS delay for accurate timing
    vTaskDelay(pdMS_TO_TICKS(ms));
}

//===============================================================================
// Pin Initialization
//===============================================================================

/**
 * @brief Initialize all Pins defined in BoardPins from pin_config.hpp
 */
void Esp32c6_hw::initAllPins()
{
    for (auto pin : boardPins.allPins)
    {
        pin->gpio_init();
    }
}

//===============================================================================
// ESP32-specific Member Functions
//===============================================================================

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
    ESP_LOGI(TAG, "Restarting ESP32...");
    esp_restart();
}
