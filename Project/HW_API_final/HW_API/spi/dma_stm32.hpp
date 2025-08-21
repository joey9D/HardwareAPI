#pragma once

#include "../drivers/stm32_hal_wrapper/common/stm32_hal_inc.hpp"
#include "dma_interface.hpp"
#include "hw_enum_stm32.hpp"

#ifdef STM32_PLATFORM

class Dma : public IDma
{
public:
    // Konstruktor mit allen DMA_InitTypeDef-Parametern
    Dma(
        // SPI_HandleTypeDef &hspi,
        DmaRequest request_tx,
        DmaRequest request_rx,
        DmaPeriphInc periphInc,
        DmaMemInc memInc,
        DmaPeriphDataSizeAlignment periphDataAlignment,
        DmaMemDataSizeAlignment memDataAlignment,
        DmaMode mode,
        DmaPriority priority);

    // Interface-Implementierung
    bool dma_init() override;
    bool dma_init_TX() override;
    bool dma_init_RX() override;
    bool dma_interrupts(uint32_t priority = 0) override;

    bool isTransferComplete() const override;
    bool isTransferBusy() const override;
    bool isTransferError() const override;

    void setSpiHandle(SPI_HandleTypeDef *hspi);

private:
    SPI_HandleTypeDef *_hspi;
    DmaRequest _request_tx;
    DmaRequest _request_rx;
    // DmaDirection _direction;
    DmaPeriphInc _periphInc;
    DmaMemInc _memInc;
    DmaPeriphDataSizeAlignment _periphDataAlignment;
    DmaMemDataSizeAlignment _memDataAlignment;
    DmaMode _mode;
    DmaPriority _priority;

    // Template
    template <SPI_TypeDef *SPIx>
    bool dma_init_TX();

    template <SPI_TypeDef *SPIx>
    bool dma_init_RX();
};

template <SPI_TypeDef *SPIx>
bool Dma::dma_init_TX()
{
    if (_hspi == nullptr || _hspi->Instance == nullptr)
    {
        assert(false && "SPI handle not set. Call setSpiHandle() before dma_init_TX()");
        return false;
    }

    DMA_HandleTypeDef &dma_handle_Tx = SPIDmaHandlers<SPIx>::getTxHandle();

    dma_handle_Tx.Instance = DMA1_Channel3;
    dma_handle_Tx.Init.Request = requestToHal(_request_tx);
    dma_handle_Tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
    dma_handle_Tx.Init.PeriphInc = periphIncToHal(_periphInc);
    dma_handle_Tx.Init.MemInc = memIncToHal(_memInc);
    dma_handle_Tx.Init.PeriphDataAlignment = periphDataAlignmentToHal(_periphDataAlignment);
    dma_handle_Tx.Init.MemDataAlignment = memDataAlignmentToHal(_memDataAlignment);
    dma_handle_Tx.Init.Mode = modeToHal(_mode);
    dma_handle_Tx.Init.Priority = priorityToHal(_priority);

    // HAL DMA Initialisierung
    if (HAL_DMA_Init(&dma_handle_Tx) != HAL_OK)
    {
        return false;
    }

    // DMA mit SPI Handle verknüpfen
    __HAL_LINKDMA(_hspi, hdmatx, dma_handle_Tx);

    return true;
}

template <SPI_TypeDef *SPIx>
bool Dma::dma_init_RX()
{
    // Prüfen, ob ein SPI-Handle gesetzt wurde
    if (_hspi == nullptr || _hspi->Instance == nullptr)
    {
        assert(false && "SPI handle not set. Call setSpiHandle() before dma_init_RX()");
        return false;
    }

    DMA_HandleTypeDef &dma_handle_Rx = SPIDmaHandlers<SPIx>::getRxHandle();

    dma_handle_Rx.Instance = DMA1_Channel2;
    dma_handle_Rx.Init.Request = requestToHal(_request_rx);
    dma_handle_Rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
    dma_handle_Rx.Init.PeriphInc = periphIncToHal(_periphInc);
    dma_handle_Rx.Init.MemInc = memIncToHal(_memInc);
    dma_handle_Rx.Init.PeriphDataAlignment = periphDataAlignmentToHal(_periphDataAlignment);
    dma_handle_Rx.Init.MemDataAlignment = memDataAlignmentToHal(_memDataAlignment);
    dma_handle_Rx.Init.Mode = modeToHal(_mode);
    dma_handle_Rx.Init.Priority = priorityToHal(_priority);

    // HAL DMA Initialisierung
    if (HAL_DMA_Init(&dma_handle_Rx) != HAL_OK)
    {
        return false;
    }

    // DMA mit SPI Handle verknüpfen
    __HAL_LINKDMA(_hspi, hdmarx, dma_handle_Rx);

    return true;
}

#endif // STM32_PLATFORM
