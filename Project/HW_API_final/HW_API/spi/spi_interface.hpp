#pragma once

#include "../core/hw_enum_classes.hpp"

class ISpi
{
public:
    virtual ~ISpi() = default;

    // Initialization
    virtual bool spi_init() = 0;

    // Polling - Generic byte-based interface
    virtual bool transmit(const uint8_t *data, uint16_t length) = 0;
    virtual bool receive(uint8_t *data, uint16_t length) = 0;
    virtual bool transmitReceive(const uint8_t *txData, uint8_t *rxData, uint16_t length) = 0;

    // DMA - Generic byte-based interface
    virtual bool transmit_DMA(const uint8_t *data, uint16_t length) = 0;
    virtual bool receive_DMA(uint8_t *data, uint16_t length) = 0;
    virtual bool transmitReceive_DMA(const uint8_t *txData, uint8_t *rxData, uint16_t length) = 0;

    // Interrupt - Generic byte-based interface
    virtual bool transmit_IT(const uint8_t *data, uint16_t length) = 0;
    virtual bool receive_IT(uint8_t *data, uint16_t length) = 0;
    virtual bool transmitReceive_IT(const uint8_t *txData, uint8_t *rxData, uint16_t length) = 0;

    // Optional: Platform-specific frame size configuration
    virtual void setFrameSize(uint8_t bits) = 0;
    virtual uint8_t getFrameSize() const = 0;
};
