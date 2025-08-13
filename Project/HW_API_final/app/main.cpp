/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.cpp
 * @brief          : Main program body for HW_API
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2025 STMicroelectronics.
 * All rights reserved.
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
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{
  // Create hardware interface using factory pattern
  HardwareInterface *hw = HardwareFactory::create();

  // Initialize system (HAL, clocks, etc.)
  hw->init_sys();

  // Initialize all pins defined in project_config.hpp
  hw->initAllPins();

  // Initialize debounce state
  bool lastButtonState = boardPins.button.isDebouncePinOn();

  /* Infinite loop */
  while (1)
  {
    // boardPins.led.writePin(1); // Turn on LED
    // hw->delay(1000);           // Delay for 1 second
    // boardPins.led.writePin(0); // Turn off LED
    // hw->delay(1000);           // Delay for 1 second
    // Read current button state with debouncing
    bool currentButtonState = boardPins.button.isDebouncePinOn();

    // Toggle LED on button press (rising edge detection)
    if (!lastButtonState && currentButtonState)
    {
      boardPins.led.togglePin();
    }

    // Update button state
    lastButtonState = currentButtonState;
  }
}
