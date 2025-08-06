/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.cpp
 * @brief          : Main program body for HW_API ESP32
 ******************************************************************************
 * @attention
 *
 * ESP32 version of the HW_API main application
 * Uses ESP-IDF framework instead of standard main()
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.hpp"

/**
 * @brief  ESP32 application entry point (replaces main() for ESP-IDF)
 * @retval void
 */
extern "C" void app_main(void)
{
    ESP_LOGI(TAG, "Starting HW_API ESP32 Application");
    ESP_LOGI(TAG, "Initializing hardware interface...");

    // Create hardware interface using factory pattern
    HardwareInterface *hw = HardwareFactory::create();

    if (!hw)
    {
        ESP_LOGE(TAG, "Failed to create hardware interface!");
        return;
    }

    ESP_LOGI(TAG, "Hardware interface created successfully");

    // Initialize system (HAL, clocks, etc.)
    // hw->init_sys();

    // Initialize all pins defined in pin_config.hpp
    ESP_LOGI(TAG, "Initializing GPIO pins...");
    hw->initAllPins();
    ESP_LOGI(TAG, "GPIO pins initialized successfully");

    // Initialize debounce state
    bool lastButtonState = boardPins.button.isDebouncePinOn();
    ESP_LOGI(TAG, "Starting main loop...");

    /* Infinite loop */
    while (1)
    {
        // Read current button state with debouncing
        bool currentButtonState = boardPins.button.isDebouncePinOn();

        // Toggle LED on button press (rising edge detection)
        if (!lastButtonState && currentButtonState)
        {
            boardPins.led.togglePin();
            ESP_LOGI(TAG, "Button pressed - LED toggled");
        }

        // Update button state
        lastButtonState = currentButtonState;

        // Small delay to prevent busy waiting (ESP32 specific)
        vTaskDelay(pdMS_TO_TICKS(10)); // 10ms delay
    }
}
