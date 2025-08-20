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

    // state
    DmaTxState getTxState() const;
    void setTxState(DmaTxState state);
    bool isTxComplete() const;
    bool isTxError() const;

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
    DmaTxState _txState;
};

#endif // STM32_PLATFORM
