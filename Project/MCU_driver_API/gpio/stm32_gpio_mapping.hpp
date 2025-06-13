#pragma once

namespace stm32x0_gpio_mapping
{
/**
 * Include all hw familz header files
 */
#include "stm32c0xx.h"

constexpr auto port_count = 6; /* A, B, C, D, E, F */
constexpr auto pin_count = 16; /* 0 - 15 */


/**
 * @brief SMT32C0
 *
 */

#ifdef STM32C0
constexpr GPIO_TypeDef *const gpio_port[port_count] =
{
    GPIOA, GPIOB, GPIOC
#if defined(STM32C031x4) || defined(STM32C031x6)
    GPIOD,
#else
    nullptr,
#endif
    nullptr, // port E is not listed in rm0490 stm32c0x1
#endif
    GPIOF
}
#endif /* end stm32c0 */

/**
 * @brief SMT32F0
 *
 */
#ifdef STM32F0
constexpr GPIO_TypeDef *const gpio[port_count] =
{
    GPIOA, GPIOB, GPIOC,
#if defined(STM32F030x6) || defined(STM32F030x8) || defined(STM32F030xC) || \
    defined(STM32F051x8) || defined(STM32F058xx) || defined(STM32F070x6) || \
    defined(STM32F070xB) || defined(STM32F071xB) || defined(STM32F072xB) || \
    defined(STM32F078xx) || defined(STM32F091xC) || defined(STM32F098xx)
    GPIOD,
#else
    nullptr,
#endif
#if defined(STM32F071xB) || defined(STM32F072xB) || defined(STM32F078xx) || \
    defined(STM32F091xC) || defined(STM32F098xx)
    GPIOE,
#else
    nullptr,
#endif
    GPIOF
}
#endif /* end stm32f0 */


/**
 * @brief SMT32G0
 *
 */
#ifdef STM32G0
constexpr GPIO_TypeDef *const gpio[ports] =
{
    GPIOA, GPIOB, GPIOC,
#if defined(STM32G070xx) || defined(STM32G071xx) || defined(STM32G081xx) || \
    defined(STM32G0B1xx) || defined(STM32G0B0xx) || defined(STM32G0C1xx)
    GPIOD,
#else
    nullptr,
#endif
#if defined(STM32G081xx) || defined(STM32G0B1xx) || defined(STM32G0B0xx) || defined(STM32G0C1xx)
    GPIOE,
#else
    nullptr,
#endif
    GPIOF
}
#endif /* end stm32g0 */

} /* end namespace */
