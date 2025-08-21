#ifdef STM32_PLATFORM

#include "error_handler.hpp"

#ifdef __cplusplus
extern "C"
{
#endif

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
            // Optional: LED blinken oder Debug-Output
            // HAL_Delay(500);  // Nur wenn SysTick noch funktioniert
        }
        /* USER CODE END Error_Handler_Debug */
    }

#ifdef __cplusplus
}
#endif

#endif // STM32_PLATFORM