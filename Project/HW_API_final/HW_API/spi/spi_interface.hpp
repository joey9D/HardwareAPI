#pragma once

#include "hw_enum_classes.hpp"

template <typename TransferType>
class ISpiBase
{
public:
    virtual ~ISpiBase() = default;

    // Initialization
    virtual bool spi_init() = 0;

    // Polling
    virtual bool transmit(const TransferType *data, size_t length) = 0;
    virtual bool receive(TransferType *data, size_t length) = 0;
    virtual bool transmitReceive(const TransferType *txData, TransferType *rxData, size_t length) = 0;

    // DMA
    virtual bool transmit_DMA(const TransferType *data, size_t length) = 0;
    virtual bool receive_DMA(TransferType *data, size_t length) = 0;
    virtual bool transmitReceive_DMA(const TransferType *txData, TransferType *rxData, size_t length) = 0;

    // Interrupt
    virtual bool transmit_IT(const TransferType *data, size_t length) = 0;
    virtual bool receive_IT(TransferType *data, size_t length) = 0;
    virtual bool transmitReceive_IT(const TransferType *txData, TransferType *rxData, size_t length) = 0;
};

// Platform-specific SPI types
#ifdef STM32_PLATFORM
#ifdef TRANSFERSIZE8
using ISpi = ISpiBase<uint8_t>; // Standard: 8-bit
#elif defined(TRANSFERSIZE16)
using ISpi = ISpiBase<uint16_t>; // Standard: 16-bit
#endif
#elif defined(ESP_PLATFORM) || defined(ESP32_PLATFORM)
#ifdef TRANSFERSIZE8
using ISpi = ISpiBase<uint8_t>; // Standard: 8-bit
#elif defined(TRANSFERSIZE16)
using ISpi = ISpiBase<uint16_t>; // Standard: 16-bit
#endif /* Transfer Size */
#endif /* PLATFORM */