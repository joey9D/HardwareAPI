

#include "main.h"

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

	HardwareInterface *hw = HardwareFactory::create();

	hw->init_sys();

	PinConfig_t led_cfg;
	led_cfg.pin = 15;
	led_cfg.port = Port::A;
	led_cfg.mode = Mode::Output_Push_Pull;
	led_cfg.pull = Pull::None;
	led_cfg.speed = Speed::Low;
	led_cfg.invertedPin = false;
	led_cfg.debounceTime = 0;
	led_cfg.debounceState = 0;


	PinConfig_t button_cfg;
	button_cfg.pin = 9;
	button_cfg.port = Port::A;
	button_cfg.mode = Mode::Input;
	button_cfg.pull = Pull::Up;
	button_cfg.speed = Speed::Low;
	button_cfg.invertedPin = false;
	button_cfg.debounceTime = 50;
	button_cfg.debounceState = 0;


	Gpio led(led_cfg);
	Gpio button(button_cfg);

	led.gpio_init();
	button.gpio_init();

	bool lastButtonState = button.isDebouncePinOn();

  /* Infinite loop */

  while (1)
  {
//	  hw->togglePin();
//	  hw->delay(500);
	  bool currentButtonState = button.isDebouncePinOn();

	  if( !lastButtonState && currentButtonState )
	  {
		  led.togglePin();
	  }
	  lastButtonState = currentButtonState;

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

#ifdef  USE_FULL_ASSERT
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
