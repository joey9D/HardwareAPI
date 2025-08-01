/*
 * esp32c6_hw.cpp
 *
 *  Created on: Aug 1, 2025
 *      Author: jan.kristel
 */

#include "esp32c6devkitc.hpp"

// ESP32 Specific Includes
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_system.h"
#include "esp_log.h"
#include "esp_err.h"

// Logging tag for this module
static const char *TAG = "ESP32C6_HW";

//===============================================================================
// System Initialization
//===============================================================================

void Esp32c6_hw::init_sys()
{
    ESP_LOGI(TAG, "Initializing ESP32-C6 DevKitC-1 system...");

    // Initialize ESP32 system
    // Note: ESP-IDF handles most low-level initialization automatically

    // Log system information
    esp_chip_info_t chip_info;
    esp_chip_info(&chip_info);

    ESP_LOGI(TAG, "ESP32-C6 chip with %d CPU core(s), WiFi%s%s, ",
             chip_info.cores,
             (chip_info.features & CHIP_FEATURE_BT) ? "/BT" : "",
             (chip_info.features & CHIP_FEATURE_BLE) ? "/BLE" : "");

    ESP_LOGI(TAG, "Silicon revision %d, ", chip_info.revision);
    ESP_LOGI(TAG, "%dMB %s flash",
             (int)(spi_flash_get_chip_size() / (1024 * 1024)),
             (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");

    ESP_LOGI(TAG, "System initialization completed");
}

//===============================================================================
// Clock Initialization
//===============================================================================

void Esp32c6_hw::init_clock()
{
    ESP_LOGI(TAG, "Initializing ESP32-C6 clock system...");

    // ESP-IDF automatically configures the clock system
    // CPU frequency is set via menuconfig or sdkconfig
    // Default configuration should be suitable for most applications

    // Get current CPU frequency
    uint32_t cpu_freq = esp_clk_cpu_freq();
    ESP_LOGI(TAG, "CPU frequency: %d MHz", cpu_freq / 1000000);

    // Get APB frequency
    uint32_t apb_freq = esp_clk_apb_freq();
    ESP_LOGI(TAG, "APB frequency: %d MHz", apb_freq / 1000000);

    ESP_LOGI(TAG, "Clock system initialization completed");
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

void Esp32c6_hw::initAllPins()
{
    ESP_LOGI(TAG, "Initializing ESP32-C6 DevKitC-1 pins...");

    // Pin initialization is handled by the GPIO classes in pin_config.hpp
    // Each GPIO object handles its own initialization when gpio_init() is called

    ESP_LOGI(TAG, "Pin initialization completed");
}

//===============================================================================
// Additional ESP32-specific Helper Functions
//===============================================================================

// Get free heap size (useful for memory monitoring)
uint32_t get_free_heap_size()
{
    return esp_get_free_heap_size();
}

// Get minimum free heap size since boot
uint32_t get_minimum_free_heap_size()
{
    return esp_get_minimum_free_heap_size();
}

// Reset the ESP32
void esp32_restart()
{
    ESP_LOGI(TAG, "Restarting ESP32...");
    esp_restart();
}
