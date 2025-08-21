#pragma once

#include "../drivers/stm32_hal_wrapper/common/stm32_hal_inc.hpp"
#include "dma_interface.hpp"
#include "hw_enum_stm32.hpp"

#ifdef STM32_PLATFORM

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
        DmaPriority priority);

    // Interface-Implementierung
    bool dma_init() override;
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

    template <SPI_TypeDef *SPIx>
    bool dma_init_TX();

    template <SPI_TypeDef *SPIx>
    bool dma_init_RX();
};

#endif // STM32_PLATFORM
