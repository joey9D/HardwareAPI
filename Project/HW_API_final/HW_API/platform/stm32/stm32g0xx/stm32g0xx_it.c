/*
 * stm32g0xx_it.c
 *
 *  Created on: Aug 1, 2025
 *      Author: jan.kristel
 */

/* Includes ------------------------------------------------------------------*/
#include "stm32g0xx_it.h"
#include "stm32g0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private user code ---------------------------------------------------------*/

/* External variables --------------------------------------------------------*/

/******************************************************************************/
/*           Cortex-M0+ Processor Interruption and Exception Handlers       */
/******************************************************************************/

/**
 * @brief This function handles Non maskable interrupt.
 */
void NMI_Handler(void)
{
    while (1)
    {
    }
}

/**
 * @brief This function handles Hard fault interrupt.
 */
void HardFault_Handler(void)
{
    while (1)
    {
    }
}

/**
 * @brief This function handles System service call via SWI instruction.
 */
void SVC_Handler(void)
{
}

/**
 * @brief This function handles Pendable request for system service.
 */
void PendSV_Handler(void)
{
}

/**
 * @brief This function handles System tick timer.
 */
void SysTick_Handler(void)
{
    HAL_IncTick();
}

/******************************************************************************/
/* STM32G0xx Peripheral Interrupt Handlers                                   */
/* Add here the Interrupt Handlers for the used peripherals.                */
/* For the available peripheral interrupt handler names,                     */
/* please refer to the startup file (startup_stm32g0xx.s).                  */
/******************************************************************************/

/* Add interrupt handlers here as needed */

/* C++ compatibility wrapper */
#ifdef __cplusplus
extern "C"
{
#endif

    /* Ensure this object file is linked even if no functions are called directly */
    __attribute__((used)) static const uint32_t stm32g0xx_it_force_link = 0xDEADBEEF;

#ifdef __cplusplus
}
#endif
