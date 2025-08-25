#pragma once

template <typename PlatformDMAHandle>
class IDmaBase
{
public:
    virtual ~IDmaBase() = default;

    // DMA Initialisierung
    virtual bool dma_init() = 0;
    virtual bool dma_init_tx(void *spi_instance) = 0;
    virtual bool dma_init_rx(void *spi_instance) = 0;
    virtual bool dma_interrupts(uint32_t priority = 0) = 0;
    virtual bool isTransferComplete() const = 0;
    virtual bool isTransferBusy() const = 0;
    virtual bool isTransferError() const = 0;
};

// Platform-spezifische Type-Aliases - HIER passiert die Auswahl!
#ifdef STM32_PLATFORM
#include "../drivers/stm32_hal_wrapper/common/stm32_hal_inc.hpp"
using IDma = IDmaBase<DMA_HandleTypeDef>;
#elif defined(ESP_PLATFORM)
#include "driver/spi_master.h"
using IDma = IDmaBase<spi_dma_chan_t>;
#endif