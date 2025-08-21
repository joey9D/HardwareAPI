#pragma once

#include "../core/hw_enum_classes.hpp"

class ISpi
{
public:
    virtual ~ISpi() = default;

    // Initialization
    virtual bool spi_init() = 0;

    // Polling - Generic byte-based interface with configurable timeout
    virtual bool transmit(const uint8_t *data, uint16_t length, uint32_t timeout) = 0;
    virtual bool receive(uint8_t *data, uint16_t length, uint32_t timeout) = 0;
    virtual bool transmitReceive(const uint8_t *txData, uint8_t *rxData, uint16_t length, uint32_t timeout) = 0;

    virtual bool transmit_DMA(const uint8_t *data, uint16_t length, uint32_t timeout = 0) = 0;
    virtual bool receive_DMA(uint8_t *data, uint16_t length, uint32_t timeout = 0) = 0;
    virtual bool transmitReceive_DMA(const uint8_t *txData, uint8_t *rxData, uint16_t length, uint32_t timeout = 0) = 0;

    // virtual bool enableInterrupts(uint32_t priority = 1) = 0;
};
