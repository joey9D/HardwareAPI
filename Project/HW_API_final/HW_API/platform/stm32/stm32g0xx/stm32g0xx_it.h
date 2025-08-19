/*
 * stm32g0xx_it.h
 *
 *  Created on: Aug 1, 2025
 *      Author: jan.kristel
 */

#ifndef __STM32G0XX_IT_H
#define __STM32G0XX_IT_H

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g0xx_hal.h"

    /* Exported types ------------------------------------------------------------*/
    /* Exported constants --------------------------------------------------------*/
    /* Exported macro ------------------------------------------------------------*/
    /* Exported functions ------------------------------------------------------- */

    void NMI_Handler(void);
    void HardFault_Handler(void);
    void SVC_Handler(void);
    void PendSV_Handler(void);
    void SysTick_Handler(void);

    /* DMA Interrupt Handlers für SPI */
    void DMA1_Channel1_IRQHandler(void);
    void DMA1_Channel2_3_IRQHandler(void);
    void DMA1_Ch4_7_DMA2_Ch1_5_DMAMUX1_OVR_IRQHandler(void);

    /* Externe DMA Handles für Interrupt Handler */
    extern DMA_HandleTypeDef hdma_spi1_tx;
    extern DMA_HandleTypeDef hdma_spi1_rx;
    extern DMA_HandleTypeDef hdma_spi2_tx;
    extern DMA_HandleTypeDef hdma_spi2_rx;

#ifdef __cplusplus
}
#endif

#endif /* __STM32G0XX_IT_H */
