#pragma once

template <typename PlatformDMAHandle>
class ISpiDMABase
{
public:
    virtual ~ISpiDMABase() = default;

    // DMA Initialisierung
    virtual bool init_dma_TX() = 0;
    virtual bool init_dma_RX() = 0;
    virtual bool init_dma() = 0;

    // DMA De-Initialisierung
    virtual bool deInit_dma_TX() = 0;
    virtual bool deInit_dma_RX() = 0;
    virtual bool deInit_dma() = 0;

    // Status-Abfrage
    virtual bool isTxReady() const = 0;
    virtual bool isRxReady() const = 0;
    virtual bool areBothReady() const = 0;

    // Platform-spezifische Handle-Getter
    virtual PlatformDMAHandle *getTxHandle() = 0;
    virtual PlatformDMAHandle *getRxHandle() = 0;

    // Clock/Resource Management
    virtual void enableDMAResources() = 0;
};

// Platform-spezifische Type-Aliases - HIER passiert die Auswahl!
#ifdef STM32_PLATFORM
#include "../drivers/stm32_hal_wrapper/common/stm32_hal_inc.hpp"
using ISpiDMA = ISpiDMABase<DMA_HandleTypeDef>;
#elif defined(ESP_PLATFORM) || defined(ESP32_PLATFORM)
#include "driver/spi_master.h"
using ISpiDMA = ISpiDMABase<spi_dma_chan_t>;
#endif