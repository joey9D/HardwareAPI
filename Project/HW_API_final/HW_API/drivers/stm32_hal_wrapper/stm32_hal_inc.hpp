#pragma once

// Central STM32 HAL include file
#ifdef STM32_PLATFORM

#ifdef __cplusplus
extern "C" {
#endif

// Include the generated HAL configuration first - this is crucial
#include "stm32c0xx_hal_conf.h"

// Include main HAL header - this must come after hal_conf.h and provides HAL_Init
#include "stm32c0xx_hal.h"

#ifdef __cplusplus
}
#endif

#endif // STM32_PLATFORM
