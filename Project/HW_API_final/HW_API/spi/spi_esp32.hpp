#pragma once

#ifdef ESP_PLATFORM
#include "../core/hw_enum_classes.hpp"

class Spi : public ISpi
{
public:
    Spi(
        Gpio &sck,
        Gpio &miso,
        Gpio &mosi,
        Gpio &cs,
        SPI_TypeDef *instance,
        SpiMode mode,
        SpiDirection direction,
        SpiDataSize dataSize,
        SpiClockPolarity clkPolarity,
        SpiClockPhase clkPhase,
        SpiNSS nss,
        SpiBaudRatePrescaler baudRatePrescaler,
        SpiFirstBit firstBit,
        SpiTIMode tiMode,
        SpiCRCCalculation crcCalculation,
        uint32_t crcPolynomial,
        SpiCRCLength crcLength,
        SpiNSSPMode nsspMode);

    // - init
    bool spi_init() override;

    // Polling
    bool transmit(const uint8_t *data, uint16_t length, uint32_t timeout) override;
    bool receive(uint8_t *data, uint16_t length, uint32_t timeout) override;
    bool transmitReceive(const uint8_t *txData, uint8_t *rxData, uint16_t length, uint32_t timeout) override;

    // Dma
    SPI_HandleTypeDef *get_handle();
    void set_dma(Dma *dma);
    Dma *get_dma() const;

    bool transmit_DMA(const uint8_t *data, uint16_t length, uint32_t timeout = 0) override;
    bool receive_DMA(uint8_t *data, uint16_t length, uint32_t timeout = 0) override;
    bool transmitReceive_DMA(const uint8_t *txData, uint8_t *rxData, uint16_t length, uint32_t timeout = 0) override;

private:
    Gpio &_sck;
    Gpio &_miso;
    Gpio &_mosi;
    Gpio &_cs;

    SPI_TypeDef *_instance; // Wie wird Spi fuer esp32 gehandelt?

    SpiMode _mode;
    SpiDirection _direction;
    SpiDataSize _dataSize;
    SpiClockPolarity _clockPolarity;
    SpiClockPhase _clockPhase;
    SpiNSS _nss;
    SpiBaudRatePrescaler _baudRatePrescaler;
    SpiFirstBit _firstBit;
    SpiTIMode _tiMode;
    SpiCRCCalculation _crcCalculation;
    uint32_t _crcPolynomial;
    SpiCRCLength _crcLength;
    SpiNSSPMode _nsspMode;

    SPI_HandleTypeDef _hspi; // Wie wird Spi fuer esp32 gehandelt?
    Dma *_dma = nullptr;     // Wie wird Spi fuer esp32 gehandelt?
};
