#pragma once

#ifdef STM32_PLATFORM
#include "../drivers/stm32_hal_wrapper/common/stm32_hal_inc.hpp"
#endif

#include "spi_interface.hpp"
#include "dma_stm32.hpp"
#include "../gpio/gpio_stm32.hpp"

// Forward declaration is now redundant since we include the header
// class Dma;

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
        // SpiCRCPolynomial crcPolynomial,
        uint32_t crcPolynomial,
        SpiCRCLength crcLength,
        SpiNSSPMode nsspMode);

    // - init
    bool spi_init() override;

    // Polling - byte-based interface
    bool transmit(const uint8_t *data, uint16_t length, uint32_t timeout) override;
    bool receive(uint8_t *data, uint16_t length, uint32_t timeout) override;
    bool transmitReceive(const uint8_t *txData, uint8_t *rxData, uint16_t length, uint32_t timeout) override;

    // SPI_HandleTypeDef *get_handle();

private:
    Gpio &_sck;
    Gpio &_miso;
    Gpio &_mosi;
    Gpio &_cs;

    SPI_TypeDef *_instance;

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
    // SpiCRCPolynomial _spiCRCPolynomial;
    uint32_t _spiCRCPolynomial;
    SpiCRCLength _spiCRCLength;
    SpiNSSPMode _spiNSSPMode;

    SPI_HandleTypeDef _hspi;
};
