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

	__HAL_FLASH_SET_LATENCY(FLASH_LATENCY_1);

	OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	OscInitStruct.HSEState = RCC_HSE_ON;

	HAL_RCC_OscConfig(&OscInitStruct);

	ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1;
	ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSE;
	ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
	ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV1;
	ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV1;

	HAL_RCC_ClockConfig(&ClkInitStruct, FLASH_LATENCY_1);
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



















