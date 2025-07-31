/**
 ******************************************************************************
 * @file    stm32c0xx_hal_msp.c
 * @author  MCD Application Team
 * @brief   HAL MSP module.
 *          This file template is copied from the official STM32 HAL driver
 *          and adapted for the HW_API project.
 *
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "stm32c0xx_hal.h"

/** @addtogroup STM32C0xx_HAL_Driver
 * @{
 */

/** @defgroup HAL_MSP HAL MSP module driver
 * @brief HAL MSP module.
 * @{
 */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup HAL_MSP_Private_Functions
 * @{
 */

/**
 * @brief  Initialize the Global MSP.
 * @note   This function is called from HAL_Init() function to perform system
 *         level initialization (GPIOs, clock, DMA, interrupt).
 * @retval None
 */
__attribute__((used)) void HAL_MspInit(void)
{
    /* USER MSP INIT - This is the custom implementation */
    volatile uint32_t msp_marker = 0x12345678; // Debug marker to identify custom MSP
    msp_marker++;                              // Breakpoint-friendly line

    /* Configure the system Power */
    /* Enable Power Clock */
    __HAL_RCC_PWR_CLK_ENABLE();

    /* Enable SYSCFG clock */
    __HAL_RCC_SYSCFG_CLK_ENABLE();

    /* Configure the Debug Module */
    /* Disable the Debug Module during STOP mode */
    HAL_DBGMCU_EnableDBGStopMode();

    /* Disable the Debug Module during STANDBY mode */
    HAL_DBGMCU_EnableDBGStandbyMode();
}

/**
 * @brief  Force inclusion of this object file by providing a function
 *         that is explicitly called from the main code
 * @retval Marker value to confirm MSP object file is linked
 */
uint32_t MSP_ForceInclude(void)
{
    return 0xDEADBEEF; // Unique marker to confirm this function is called
}

/**
 * @brief  DeInitialize the Global MSP.
 * @retval None
 */
void HAL_MspDeInit(void)
{
    /* Reset the RCC clock configuration to the default reset state */
    HAL_RCC_DeInit();

    /* Disable SYSCFG clock */
    __HAL_RCC_SYSCFG_CLK_DISABLE();

    /* Disable Power Clock */
    __HAL_RCC_PWR_CLK_DISABLE();
}

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */
