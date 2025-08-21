#pragma once

#ifdef STM32_PLATFORM

#include "../../../drivers/stm32_hal_wrapper/common/stm32_hal_inc.hpp"

#ifdef __cplusplus
extern "C"
{
#endif

    /**
     * @brief  This function is executed in case of error occurrence.
     * @retval None
     */
    void Error_Handler(void);

#ifdef __cplusplus
}
#endif

#endif // STM32_PLATFORM