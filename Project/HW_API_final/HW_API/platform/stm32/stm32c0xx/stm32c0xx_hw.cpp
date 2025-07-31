/*
 * stm32c0xx_hw.cpp
 *
 *  Created on: Jul 10, 2025
 *      Author: jan.kristel
 */
#include <assert.h>
#include <type_traits>
#include "../../../drivers/stm32_hal_wrapper/stm32_hal_inc.hpp"
#include "stm32c0xx_hw.hpp"
#include "stm32x0_gpio_mapping.hpp"
//#include "timer.hpp"
#include "gpio_stm32.hpp"
#include "pin_config.hpp"

// Forward declaration of Error_Handler
extern "C" void Error_Handler(void);

void Stm32c0xx_hw::init_sys()
	{
		HAL_Init();
		init_clock();
	}

	// clock
void Stm32c0xx_hw::init_clock()
{
	RCC_OscInitTypeDef OscInitStruct{}; // Klammern leer nach C++ 11 Standard
	RCC_ClkInitTypeDef ClkInitStruct{};

	// Configure flash latency
	__HAL_FLASH_SET_LATENCY(FLASH_LATENCY_1);

	// NUCLEO-C031C6 uses internal HSI, not external HSE crystal
	OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	OscInitStruct.HSIState = RCC_HSI_ON;
	OscInitStruct.HSIDiv = RCC_HSI_DIV1;
	OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;

	if (HAL_RCC_OscConfig(&OscInitStruct) != HAL_OK)
	{
		// Clock configuration failed - call error handler
		Error_Handler();
	}

	// Configure system clock
	ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1;
	ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
	ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
	ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV1;
	ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV1;

	if (HAL_RCC_ClockConfig(&ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
	{
		// Clock configuration failed - call error handler
		Error_Handler();
	}

	// Enable GPIO clocks for the pins we'll use
	__HAL_RCC_GPIOA_CLK_ENABLE();  // Both LED (PA15) and Button (PA9) are on GPIOA
}

void Stm32c0xx_hw::delay(uint32_t ms)
{
	HAL_Delay(ms);
}

/**
 * @brief Initialize all Pins defined in BoardPins from pin_config.hpp
 */
void Stm32c0xx_hw::initAllPins()
{
	for( auto pin : boardPins.allPins )
	{
		pin->gpio_init();
	}
}



















