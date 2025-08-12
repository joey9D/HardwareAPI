#pragma once

#include "hw_enum_classes.hpp"

template <typename>
class ISpiBase
{
public:
    virtual ~ISpiBase() = default;

    // Polling
    virtual bool transmit(const T *data, size_t length) = 0;
    virtual bool receive(T *data, size_t length) = 0;
    virtual bool transmitReceive(const T *txData, T *rxData, size_t length) = 0;

    // DMA
    virtual bool transmit_DMA(const T *data, size_t length) = 0;
    virtual bool receive_DMA(T *data, size_t length) = 0;
    virtual bool transmitReceive_DMA(const T *txData, T *rxData, size_t length) = 0;

    // Interrupt
    virtual bool transmit_IT(const T *data, size_t length) = 0;
    virtual bool receive_IT(T *data, size_t length) = 0;
    virtual bool transmitReceive_IT(const T *txData, T *rxData, size_t length) = 0;
};

#ifdef STM32_PLATFORM
using ISpi = ISpiBase<uint16_t>;
#elif defined(ESP_PLATFORM) || defined(ESP32_PLATFORM)
using ISpi = ISpiBase<uint64_t>;
#endif