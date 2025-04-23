#pragma once

#include "periph/timer_stm32c0.hpp"
#include "rcc.hpp"
#include "stm32c0xx.h"

namespace periph::timer_hw_mapping
{
    constexpr TIM_TypeDef *const timer[timer_stm32c0::timers] =
    {
        TIM1,
#if defined(STM32C051xx) || defined(STM32C071xx) || defined(STM32C091xx) || defined(STM32C092xx)
        TIM2,
#else
        nullptr,
#endif
        TIM3,
        // TIM4 - TIM13 are not available in STM32C0xx
        nullptr, nullptr, nullptr, nullptr, nullptr,
        nullptr, nullptr, nullptr, nullptr, nullptr,
        TIM14,
        #if defined(STM32C091xx) || defined(STM32C092xx)
        TIM15,
#else
        nullptr,
#endif
        TIM16,
        TIM17
    };

    constexpr uint32_t rcc_en[timer_stm32c0::timers] =
    {
        RCC_APBENR2_TIM1EN,
#if defined(STM32C051xx) || defined(STM32C071xx) || defined(STM32C091xx) || defined(STM32C092xx)
        RCC_APBENR1_TIM2EN,
#else
        0,
#endif
        RCC_APBENR1_TIM3EN,
        0, // TIM4
        0, // TIM5
        0, // TIM6
        0, // TIM7
        0, // TIM8
        0, // TIM9
        0, // TIM10
        0, // TIM11
        0, // TIM12
        0, // TIM13
        RCC_APBENR2_TIM14EN,
#if defined(STM32C091xx) || defined(STM32C092xx)
        RCC_APBENR2_TIM15EN,
#else
        0,
#endif
        RCC_APBENR2_TIM16EN,
        RCC_APBENR2_TIM17EN
    };

    constexpr volatile uint32_t *rcc_en_reg[timer_stm32c0::timers] =
    {
        &RCC->APBENR2,
        &RCC->APBENR1,
        &RCC->APBENR1,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        &RCC->APBENR2,
        &RCC->APBENR2,
        &RCC->APBENR2,
        &RCC->APBENR2
    };

    constexpr rcc::clk_source rcc_src[timer_stm32c0::timers] =
    {
        rcc::clk_source::apb2,           // [0]  TIM1
        rcc::clk_source::apb1,           // [1]  TIM2
        rcc::clk_source::apb1,           // [2]  TIM3
        static_cast<rcc::clk_source>(0), // [3]  TIM4
        static_cast<rcc::clk_source>(0), // [4]  TIM5
        static_cast<rcc::clk_source>(0), // [5]  TIM6
        static_cast<rcc::clk_source>(0), // [6]  TIM7
        static_cast<rcc::clk_source>(0), // [7]  TIM8
        static_cast<rcc::clk_source>(0), // [8]  TIM9
        static_cast<rcc::clk_source>(0), // [9]  TIM10
        static_cast<rcc::clk_source>(0), // [10] TIM11
        static_cast<rcc::clk_source>(0), // [11] TIM12
        static_cast<rcc::clk_source>(0), // [12] TIM13
        rcc::clk_source::apb2,           // [13] TIM14
        rcc::clk_source::apb2,           // [14] TIM15
        rcc::clk_source::apb2,           // [15] TIM16
        rcc::clk_source::apb2            // [16] TIM17
    };

    constexpr IRQn_Type irqn[timer_stm32c0::timers] =
    {
        TIM1_CC_IRQn,
#if defined(STM32C051xx) || defined(STM32C071xx) || defined(STM32C091xx) || defined(STM32C092xx)
        TIM2_IRQn,
#else
        static_cast<IRQn_Type>(0),
#endif
        TIM3_IRQn,
        static_cast<IRQn_Type>(0), // TIM4_IRQn
        static_cast<IRQn_Type>(0), // TIM5_IRQn
        static_cast<IRQn_Type>(0), // TIM6_IRQn
        static_cast<IRQn_Type>(0), // TIM7_IRQn
        static_cast<IRQn_Type>(0), // TIM8_IRQn
        static_cast<IRQn_Type>(0), // TIM9_IRQn
        static_cast<IRQn_Type>(0), // TIM10_IRQn
        static_cast<IRQn_Type>(0), // TIM11_IRQn
        static_cast<IRQn_Type>(0), // TIM12_IRQn
        static_cast<IRQn_Type>(0), // TIM13_IRQn
        TIM14_IRQn,
        #if defined(STM32C091xx) || defined(STM32C092xx)
        TIM15_IRQn,
#else
        static_cast<IRQn_Type>(0),
#endif
        TIM16_IRQn,
        TIM17_IRQn
    };
} // namespace periph::timer_hw_mapping
