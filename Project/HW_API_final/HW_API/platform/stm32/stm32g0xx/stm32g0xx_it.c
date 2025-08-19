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
/*                       DMA Interrupt Handlers für SPI                     */
/******************************************************************************/

/**
 * @brief This function handles DMA1 channel 1 global interrupt (SPI1 TX)
 */
void DMA1_Channel1_IRQHandler(void)
{
    // Verwende externe Handle-Referenzen für SPI1
    extern DMA_HandleTypeDef hdma_spi1_tx;
    HAL_DMA_IRQHandler(&hdma_spi1_tx);
}

/**
 * @brief This function handles DMA1 channel 2 global interrupt (SPI1 RX)  
 */
void DMA1_Channel2_3_IRQHandler(void)
{
    // Check which channel triggered the interrupt
    extern DMA_HandleTypeDef hdma_spi1_rx;
    extern DMA_HandleTypeDef hdma_spi2_tx;
    
    if (__HAL_DMA_GET_FLAG(&hdma_spi1_rx, DMA_FLAG_TC2))
    {
        HAL_DMA_IRQHandler(&hdma_spi1_rx);  // SPI1 RX (Channel 2)
    }
    
    if (__HAL_DMA_GET_FLAG(&hdma_spi2_tx, DMA_FLAG_TC3))
    {
        HAL_DMA_IRQHandler(&hdma_spi2_tx);  // SPI2 TX (Channel 3)
    }
}

/**
 * @brief This function handles DMA1 channel 4-7 global interrupt (SPI2 RX)
 */
void DMA1_Ch4_7_DMA2_Ch1_5_DMAMUX1_OVR_IRQHandler(void)
{
    extern DMA_HandleTypeDef hdma_spi2_rx;
    
    if (__HAL_DMA_GET_FLAG(&hdma_spi2_rx, DMA_FLAG_TC4))
    {
        HAL_DMA_IRQHandler(&hdma_spi2_rx);  // SPI2 RX (Channel 4)  
    }
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
