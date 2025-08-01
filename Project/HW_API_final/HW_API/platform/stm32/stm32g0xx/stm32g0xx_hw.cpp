/*
 * stm32g0xx_hw.cpp
 *
 *  Created on: Jul 10, 2025
 *      Author: jan.kristel
 */
#include <assert.h>
#include <type_traits>
#include "../../../drivers/stm32_hal_wrapper/common/stm32_hal_inc.hpp"
#include "stm32g0xx_hw.hpp"
#include "stm32x0_gpio_mapping.hpp"
// #include "timer.hpp"
#include "gpio_stm32.hpp"
#include "pin_config.hpp"

// Error handler implementation for hardware abstraction layer
extern "C" void Error_Handler(void)
{
    // Disable interrupts and halt
    __disable_irq();
    while (1)
    {
        // Stay here in case of error
    }
}

// Forward declaration of the forcing function from MSP file
extern "C" uint32_t MSP_ForceInclude(void);

void Stm32g0xx_hw::init_sys()
{
    // Force inclusion of MSP object file to ensure HAL_MspInit override works
    volatile uint32_t msp_check = MSP_ForceInclude();
    (void)msp_check; // Avoid unused variable warning

    HAL_Init();
    init_clock();
}

// clock
void Stm32g0xx_hw::init_clock()
{
    // C++17 aggregate initialization - clean and elegant
    RCC_OscInitTypeDef RCC_OscInitStruct{};
    RCC_ClkInitTypeDef RCC_ClkInitStruct{};

    // Configure the main internal regulator output voltage (STM32G0xx specific)
    HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);

    // STM32G0xx HSI configuration (based on STM32CubeIDE for G071RB/G0B1RE)
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV1; // G0xx does have HSIDiv!
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;

    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        // Clock configuration failed - call error handler
        Error_Handler();
    }

    // Configure system clock for STM32G0xx (based on STM32CubeIDE)
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1; // Note: Different naming for G0xx
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
    {
        // Clock configuration failed - call error handler
        Error_Handler();
    }
}

void Stm32g0xx_hw::delay(uint32_t ms)
{
    HAL_Delay(ms);
}

/**
 * @brief Initialize all Pins defined in BoardPins from pin_config.hpp
 */
void Stm32g0xx_hw::initAllPins()
{
    for (auto pin : boardPins.allPins)
    {
        pin->gpio_init();
    }
}
