/*
 * stm32g0xx_hal_msp.c
 *
 *  Created on: Aug 1, 2025
 *      Author: jan.kristel
 */

#include "stm32g0xx_hal.h"

/**
 * @brief Initializes the Global MSP.
 */
void HAL_MspInit(void)
{
    /* Enable HSI Clock */
    __HAL_RCC_HSI_ENABLE();

    /* Enable GPIO Clocks for typical NUCLEO-G0xx usage */
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();

    /* Configure the system Power */
    __HAL_RCC_PWR_CLK_ENABLE();
}

/**
 * @brief DeInitializes the Global MSP.
 */
void HAL_MspDeInit(void)
{
    /* Reset all peripherals */
    __HAL_RCC_APB1_FORCE_RESET();
    __HAL_RCC_APB1_RELEASE_RESET();

    __HAL_RCC_APB2_FORCE_RESET();
    __HAL_RCC_APB2_RELEASE_RESET();

    __HAL_RCC_AHB_FORCE_RESET();
    __HAL_RCC_AHB_RELEASE_RESET();
}

// Force symbol to be included in final binary
uint32_t MSP_ForceInclude(void)
{
    return 0x12345678;
}

/******************************************************************************/
/*                      SPI MSP Functions - LEER für Custom Wrapper         */
/******************************************************************************/

/**
 * @brief SPI MSP Initialization - wird von HAL_SPI_Init() aufgerufen
 * @param hspi: SPI handle pointer
 * @retval None
 *
 * HINWEIS: Komplett LEER, da die SPI-Wrapper-Klasse alles selbst macht:
 * - Clock Enable bereits in spi_stm32.cpp
 * - GPIO-Init bereits über HW_API/gpio
 * - Keine zusätzliche MSP-Initialisierung nötig
 */
void HAL_SPI_MspInit(SPI_HandleTypeDef *hspi)
{
    /* Absichtlich leer - alles wird von SPI-Wrapper-Klasse gemacht */
    (void)hspi; /* Unused parameter */
}

/**
 * @brief SPI MSP De-Initialization - wird von HAL_SPI_DeInit() aufgerufen
 * @param hspi: SPI handle pointer
 * @retval None
 *
 * HINWEIS: Komplett LEER, da die SPI-Wrapper-Klasse alles selbst macht
 */
void HAL_SPI_MspDeInit(SPI_HandleTypeDef *hspi)
{
    /* Absichtlich leer - alles wird von SPI-Wrapper-Klasse gemacht */
    (void)hspi; /* Unused parameter */
}
