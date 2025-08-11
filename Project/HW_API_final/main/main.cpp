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
    // printf("Hello from ESP32 app_main!\n");
    // Create hardware interface using factory pattern
    HardwareInterface *hw = HardwareFactory::create();

    // Initialize system (HAL, clocks, etc.)
    // hw->init_sys();

    // Initialize all pins defined in pin_config.hpp

    hw->initAllPins();

    // Initialize debounce state
    bool lastButtonState = boardPins.button.isDebouncePinOn();
    bool led_state = false;

    /* Infinite loop */
    while (1)
    {
        // boardPins.led.writePin(true);  // Turn on LED
        // hw->delay(1000);               // Delay for 1 second
        // boardPins.led.writePin(false); // Turn off LED
        // hw->delay(1000);               // Delay for 1 second

        // Read current button state with debouncing
        bool currentButtonState = boardPins.button.isDebouncePinOn();

        // Toggle LED on button press (rising edge detection)
        if (!lastButtonState && currentButtonState)
        {
            boardPins.led.togglePin();
            led_state = !led_state; // Toggle LED state
            // gpio_set_level(static_cast<gpio_num_t>(boardPins.led.getPin()),
            // led_state); // Set LED pin state
            boardPins.led.writePin(led_state); // Set LED pin state
        }

        // Update button state
        lastButtonState = currentButtonState;

        // Small delay to prevent busy waiting (ESP32 specific)
        // vTaskDelay(pdMS_TO_TICKS(10)); // 10ms delay
    }
}
