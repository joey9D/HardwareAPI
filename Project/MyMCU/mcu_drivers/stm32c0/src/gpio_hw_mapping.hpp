#pragma once

#include "periph/gpio_stm32c0.hpp"
#include "stm32c0xx.h"

namespace periph::gpio_hw_mapping
{
    constexpr auto ports = 5; // GPIOA, B, C, D, F - no E Port for C0xx. GPIOD only available in C03 models.
    constexpr auto pins = 16; // The total number of pins in port

    constexpr GPIO_TypeDef *const gpio[ports] =
        {
            GPIOA, GPIOB, GPIOC,
#if defined(STM32C031xx) || defined(STM32C051xx) || defined(STM32C071xx) || \
    defined(STM32C091xx) || defined(STM32C092xx)
            GPIOD,
#else
            nullptr,
#endif
            GPIOF};

    constexpr uint32_t rcc_en[ports] =
        {
            RCC_IOPENR_GPIOAEN,
            RCC_IOPENR_GPIOBEN,
            RCC_IOPENR_GPIOCEN,
#if defined(STM32C031xx) || defined(STM32C051xx) || defined(STM32C071xx) || \
    defined(STM32C091xx) || defined(STM32C092xx)
            RCC_IOPENR_GPIODEN,
#else
            0,
#endif
            RCC_IOPENR_GPIOFEN};
} // namespace periph::gpio_hw_mapping
