#pragma once

#include "../drivers/stm32_hal_wrapper/common/stm32_hal_inc.hpp"
#include "dma_interface.hpp"
#include "hw_enum_stm32.hpp"

#ifdef STM32_PLATFORM

using namespace HW_API::STM32;

template <SPI_TypeDef *SPIx>
struct SPIDmaHandlers;

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
        DmaPriority priority,
        DMA_Channel_TypeDef *instance_tx = nullptr,
        DMA_Channel_TypeDef *instance_rx = nullptr);

    // Interface-Implementierung
    bool dma_init() override;
    bool dma_init_tx(void *spi_instance) override;
    bool dma_init_rx(void *spi_instance) override;
    // wrapper
    bool stm32_dma_init_tx(SPI_TypeDef *SPIx);
    bool stm32_dma_init_rx(SPI_TypeDef *SPIx);
    bool dma_interrupts(uint32_t priority = 0) override;

    bool isTransferComplete() const override;
    bool isTransferBusy() const override;
    bool isTransferError() const override;

    void setSpiHandle(SPI_HandleTypeDef *hspi);

private:
    SPI_HandleTypeDef *_hspi;

    DMA_Channel_TypeDef *_instance_tx;
    DMA_Channel_TypeDef *_instance_rx;

    DmaRequest _request_tx;
    DmaRequest _request_rx;
    // DmaDirection _direction;
    DmaPeriphInc _periphInc;
    DmaMemInc _memInc;
    DmaPeriphDataSizeAlignment _periphDataAlignment;
    DmaMemDataSizeAlignment _memDataAlignment;
    DmaMode _mode;
    DmaPriority _priority;

    // helper
    DMA_Channel_TypeDef *getDefaultTxChannel(SPI_TypeDef *spiInstance);
    DMA_Channel_TypeDef *getDefaultRxChannel(SPI_TypeDef *spiInstance);
};

#endif // STM32_PLATFORM
