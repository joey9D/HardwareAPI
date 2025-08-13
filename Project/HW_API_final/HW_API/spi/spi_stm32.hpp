#pragma once

#ifdef STM32_PLATFORM
#include "../drivers/stm32_hal_wrapper/common/stm32_hal_inc.hpp"
#endif

#include "spi_interface.hpp"

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
        SpiCRCPolynomial crcPolynomial,
        SpiCRCLength crcLength,
        SpiNSSPMode nsspMode,
        SpiDMA *dma = nullptr);

    // - init
    bool spi_init()
    {
        return (HAL_SPI_Init(&_hspi) == HAL_OK);
    }

    // Polling
    bool transmit(const uint16_t *data, size_t length) override;
    bool receive(uint16_t *data, size_t length) override;
    bool transmitReceive(const uint16_t *txData, uint16_t *rxData, size_t length) override;

    // DMA
    void set_dma(SpiDMA *dma);
    SpiDMA *get_dma() const;
    bool transmit_DMA(const uint16_t *data, size_t length) override;
    bool receive_DMA(uint16_t *data, size_t length) override;
    bool transmitReceive_DMA(const uint16_t *txData, uint16_t *rxData, size_t length) override;

    // Interrupt
    bool transmit_IT(const uint16_t *data, size_t length) override;
    bool receive_IT(uint16_t *data, size_t length) override;
    bool transmitReceive_IT(const uint16_t *txData, uint16_t *rxData, size_t length) override;

    SPI_HandleTypeDef *get_handle();

private:
    Gpio &_sck;
    Gpio &_miso;
    Gpio &_mosi;
    Gpio &_cs;

    SpiMode _spiMode;
    SpiDirection _spiDirection;
    SpiDataSize _spiDataSize;
    SpiClockPolarity _spiClockPolarity;
    SpiClockPhase _spiClockPhase;
    SpiNSS _spiNSS;
    SpiBaudRatePrescaler _spiBaudRatePrescaler;
    SpiFirstBit _spiFirstBit;
    SpiTIMode _spiTIMode;
    SpiCRCCalculation _spiCRCCalculation;
    SpiCRCPolynomial _spiCRCPolynomial;
    SpiCRCLength _spiCRCLength;
    SpiNSSPMode _spiNSSPMode;

    SPI_HandleTypeDef _hspi;
    SpiDMA *_dma;
};
