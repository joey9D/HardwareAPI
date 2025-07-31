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

  // Initialize all pins defined in pin_config.hpp
  hw->initAllPins();

  // // Initialize debounce state
  // bool lastButtonState = boardPins.button.isDebouncePinOn();

  /* Infinite loop */
  while (1)
  {
    boardPins.led.writePin(1); // Turn on LED
    hw->delay(1000);           // Delay for 1 second
    boardPins.led.writePin(0); // Turn off LED
    hw->delay(1000);           // Delay for 1 second
    // // Read current button state with debouncing
    // bool currentButtonState = boardPins.button.isDebouncePinOn();

    // // Toggle LED on button press (rising edge detection)
    // if (!lastButtonState && currentButtonState)
    // {
    //   boardPins.led.togglePin();
    // }

    // // Update button state
    // lastButtonState = currentButtonState;

    // Small delay to prevent CPU hogging
    // hw->delay(1);
  }
}

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
