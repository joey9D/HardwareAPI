/**
 * @file spi_stm32.cpp
 * @author Jan Kristel
 * @brief
 * @version 0.1
 * @date 2025-08-13
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "spi_stm32.hpp"

#include "../drivers/stm32_hal_wrapper/common/stm32_hal_inc.hpp"

#include "hw_factory.hpp"
#include "hw_enum_classes.hpp"
#include "hw_enum_stm32.hpp"
#include "stm32x0_gpio_mapping.hpp"

namespace
{

    using namespace HW_API::STM32;

    uint32_t spiModeToHAL(SpiMode mode)
    {
        switch (mode)
        {
        case SpiMode::Master:
            return SPI_MODE_MASTER;
        case SpiMode::Slave:
            return SPI_MODE_SLAVE;
        default:
            return SPI_MODE_MASTER;
        }
    }

    uint32_t spiDirectionToHAL(SpiDirection dir)
    {
        switch (dir)
        {
        case SpiDirection::FullDuplex:
            return SPI_DIRECTION_2LINES;
        case SpiDirection::HalfDuplex:
            return SPI_DIRECTION_2LINES_RXONLY;
        case SpiDirection::Simplex:
            return SPI_DIRECTION_1LINE;
        default:
            return SPI_DIRECTION_2LINES;
        }
    }

    uint32_t spiDataSizeToHAL(SpiDataSize size)
    {
        switch (size)
        {
        case SpiDataSize::Bits4:
            return SPI_DATASIZE_4BIT;
        case SpiDataSize::Bits5:
            return SPI_DATASIZE_5BIT;
        case SpiDataSize::Bits6:
            return SPI_DATASIZE_6BIT;
        case SpiDataSize::Bits7:
            return SPI_DATASIZE_7BIT;
        case SpiDataSize::Bits8:
            return SPI_DATASIZE_8BIT;
        case SpiDataSize::Bits9:
            return SPI_DATASIZE_9BIT;
        case SpiDataSize::Bits10:
            return SPI_DATASIZE_10BIT;
        case SpiDataSize::Bits11:
            return SPI_DATASIZE_11BIT;
        case SpiDataSize::Bits12:
            return SPI_DATASIZE_12BIT;
        case SpiDataSize::Bits13:
            return SPI_DATASIZE_13BIT;
        case SpiDataSize::Bits14:
            return SPI_DATASIZE_14BIT;
        case SpiDataSize::Bits15:
            return SPI_DATASIZE_15BIT;
        case SpiDataSize::Bits16:
            return SPI_DATASIZE_16BIT;
        default:
            return SPI_DATASIZE_8BIT;
        }
    }

    uint32_t spiClockPolarityToHAL(SpiClockPolarity pol)
    {
        switch (pol)
        {
        case SpiClockPolarity::Low:
            return SPI_POLARITY_LOW;
        case SpiClockPolarity::High:
            return SPI_POLARITY_HIGH;
        default:
            return SPI_POLARITY_LOW;
        }
    }

    uint32_t spiClockPhaseToHAL(SpiClockPhase phase)
    {
        switch (phase)
        {
        case SpiClockPhase::FirstEdge:
            return SPI_PHASE_1EDGE;
        case SpiClockPhase::SecondEdge:
            return SPI_PHASE_2EDGE;
        default:
            return SPI_PHASE_1EDGE;
        }
    }

    uint32_t spiNSSToHAL(SpiNSS nss)
    {
        switch (nss)
        {
        case SpiNSS::Soft:
            return SPI_NSS_SOFT;
        case SpiNSS::Hard_In:
            return SPI_NSS_HARD_INPUT;
        case SpiNSS::Hard_Out:
            return SPI_NSS_HARD_OUTPUT;
        default:
            return SPI_NSS_SOFT;
        }
    }

    uint32_t spiNSSPModeToHAL(SpiNSSPMode nssp)
    {
        switch (nssp)
        {
        case SpiNSSPMode::Software:
            return SPI_NSSP_MODE_SOFTWARE;
        case SpiNSSPMode::Hardware:
            return SPI_NSSP_MODE_HARDWARE;
        default:
            return SPI_NSSP_MODE_SOFTWARE;
        }
    }

    uint32_t spiBaudRatePrescalerToHAL(SpiBaudRatePrescaler prescaler)
    {
        switch (prescaler)
        {
        case SpiBaudRatePrescaler::Prescaler2:
            return SPI_BAUDRATEPRESCALER_2;
        case SpiBaudRatePrescaler::Prescaler4:
            return SPI_BAUDRATEPRESCALER_4;
        case SpiBaudRatePrescaler::Prescaler8:
            return SPI_BAUDRATEPRESCALER_8;
        case SpiBaudRatePrescaler::Prescaler16:
            return SPI_BAUDRATEPRESCALER_16;
        case SpiBaudRatePrescaler::Prescaler32:
            return SPI_BAUDRATEPRESCALER_32;
        case SpiBaudRatePrescaler::Prescaler64:
            return SPI_BAUDRATEPRESCALER_64;
        case SpiBaudRatePrescaler::Prescaler128:
            return SPI_BAUDRATEPRESCALER_128;
        case SpiBaudRatePrescaler::Prescaler256:
            return SPI_BAUDRATEPRESCALER_256;
        default:
            return SPI_BAUDRATEPRESCALER_16;
        }
    }

    uint32_t spiFirstBitToHAL(SpiFirstBit firstBit)
    {
        switch (firstBit)
        {
        case SpiFirstBit::MSB:
            return SPI_FIRSTBIT_MSB;
        case SpiFirstBit::LSB:
            return SPI_FIRSTBIT_LSB;
        default:
            return SPI_FIRSTBIT_MSB;
        }
    }

    uint32_t spiTIModeToHAL(SpiTIMode tiMode)
    {
        switch (tiMode)
        {
        case SpiTIMode::Disable:
            return SPI_TIMODE_DISABLE;
        case SpiTIMode::Enable:
            return SPI_TIMODE_ENABLE;
        default:
            return SPI_TIMODE_DISABLE;
        }
    }

    uint32_t spiCRCCalculationToHAL(SpiCRCCalculation crcCalc)
    {
        switch (crcCalc)
        {
        case SpiCRCCalculation::Disable:
            return SPI_CRCCALCULATION_DISABLE;
        case SpiCRCCalculation::Enable:
            return SPI_CRCCALCULATION_ENABLE;
        default:
            return SPI_CRCCALCULATION_DISABLE;
        }
    }

    uint32_t spiCRCPolynomialToHAL(SpiCRCPolynomial poly)
    {
        switch (poly)
        {
        case SpiCRCPolynomial::Polynomial7:
            return SPI_CRC_POLYNOMIAL_7;
        case SpiCRCPolynomial::Polynomial8:
            return SPI_CRC_POLYNOMIAL_8;
        case SpiCRCPolynomial::Polynomial16:
            return SPI_CRC_POLYNOMIAL_16;
        default:
            return SPI_CRC_POLYNOMIAL_7;
        }
    }

    uint32_t spiCRCLengthToHAL(SpiCRCLength len)
    {
        switch (len)
        {
        case SpiCRCLength::Length_Data:
            return SPI_CRC_LENGTH_DATASIZE;
        case SpiCRCLength::Length8:
            return SPI_CRC_LENGTH_8BIT;
        case SpiCRCLength::Length16:
            return SPI_CRC_LENGTH_16BIT;
        default:
            return SPI_CRC_LENGTH_DATASIZE;
        }
    }

} // namespace

Spi::Spi(
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
    SpiNSSPMode nsspMode)
    : _sck(sck), _miso(miso), _mosi(mosi), _cs(cs),
      _instance(instance),
      _spiMode(mode), _spiDirection(direction), _spiDataSize(dataSize),
      _spiClockPolarity(clkPolarity), _spiClockPhase(clkPhase), _spiNSS(nss),
      _spiBaudRatePrescaler(baudRatePrescaler), _spiFirstBit(firstBit),
      _spiTIMode(tiMode), _spiCRCCalculation(crcCalculation),
      _spiCRCPolynomial(crcPolynomial), _spiCRCLength(crcLength),
      _spiNSSPMode(nsspMode)
{
    // Nur Member initialisieren, KEINE Hardware-Initialisierung!
}

bool Spi::spi_init()
{
    switch (_instance) // Ignoriere den Fall, dass _instance nicht gesetzt ist
    {
    case SPI1:
        __HAL_RCC_SPI1_CLK_ENABLE();
        break;
    case SPI2:
        __HAL_RCC_SPI2_CLK_ENABLE();
        break;
    case SPI3:
        __HAL_RCC_SPI3_CLK_ENABLE();
        break;
    case SPI4:
        __HAL_RCC_SPI4_CLK_ENABLE();
        break;
    case SPI5:
        __HAL_RCC_SPI5_CLK_ENABLE();
        break;
    case SPI6:
        __HAL_RCC_SPI6_CLK_ENABLE();
        break;
    default:
        break;
    }

    // GPIO initialisieren
    _sck.gpio_init();
    _miso.gpio_init();
    _mosi.gpio_init();
    _cs.gpio_init();

    // SPI Handle initialisieren
    _hspi.Instance = _instance;
    _hspi.Init.Mode = spiModeToHAL(_spiMode);
    _hspi.Init.Direction = spiDirectionToHAL(_spiDirection);
    _hspi.Init.DataSize = spiDataSizeToHAL(_spiDataSize);
    _hspi.Init.CLKPolarity = spiClockPolarityToHAL(_spiClockPolarity);
    _hspi.Init.CLKPhase = spiClockPhaseToHAL(_spiClockPhase);
    _hspi.Init.NSS = spiNSSToHAL(_spiNSS);
    _hspi.Init.BaudRatePrescaler = spiBaudRatePrescalerToHAL(_spiBaudRatePrescaler);
    _hspi.Init.FirstBit = spiFirstBitToHAL(_spiFirstBit);
    _hspi.Init.TIMode = spiTIModeToHAL(_spiTIMode);
    _hspi.Init.CRCCalculation = spiCRCCalculationToHAL(_spiCRCCalculation);
    _hspi.Init.CRCPolynomial = spiCRCPolynomialToHAL(_spiCRCPolynomial);
    _hspi.Init.CRCLength = spiCRCLengthToHAL(_spiCRCLength);
    _hspi.Init.NSSPMode = spiNSSPModeToHAL(_spiNSSPMode);

    if (_dma != nullptr)
    {
        _dma->init_dma();
    }

    HAL_StatusTypeDef status = HAL_SPI_Init(&_hspi);
    if (status != HAL_OK)
    {
        assert(false && "HAL_SPI_Init failed!");
        return false;
    }
    return true;
}

// Polling
bool Spi::transmit(const uint8_t *data, size_t length)
{
    HAL_StatusTypeDef status = HAL_SPI_Transmit(&_hspi, (uint8_t *)data, length, HAL_MAX_DELAY);
    return (status == HAL_OK);
}

bool Spi::receive(const uint8_t *data, size_t length)
{
    HAL_StatusTypeDef status = HAL_SPI_Receive(&_hspi, (uint8_t *)data, length, HAL_MAX_DELAY);
    return (status == HAL_OK);
}

bool Spi::transmitReceive(const uint8_t *txData, uint8_t *rxData, size_t length)
{
    HAL_StatusTypeDef status = HAL_SPI_TransmitReceive(&_hspi, (uint8_t *)txData, rxData, length, HAL_MAX_DELAY);
    return (status == HAL_OK);
}

// DMA
bool Spi::transmit_DMA(const uint8_t *data, size_t length)
{
    // Prüfen ob DMA verfügbar
    if (_dma == nullptr || !_dma->isTxReady())
    {
        return false;
    }

    // DMA-Transfer starten
    HAL_StatusTypeDef status = HAL_SPI_Transmit_DMA(&_hspi, (uint8_t *)data, length);
    return (status == HAL_OK);
}

bool Spi::receive_DMA(uint8_t *data, size_t length)
{
    if (_dma == nullptr || !_dma->isRxReady())
    {
        return false;
    }

    HAL_StatusTypeDef status = HAL_SPI_Receive_DMA(&_hspi, data, length);
    return (status == HAL_OK);
}

bool Spi::transmitReceive_DMA(const uint8_t *txData, uint8_t *rxData, size_t length)
{
    if (_dma == nullptr || !_dma->areBothReady())
    {
        return false;
    }

    HAL_StatusTypeDef status = HAL_SPI_TransmitReceive_DMA(&_hspi, (uint8_t *)txData, rxData, length);
    return (status == HAL_OK);
}

// Interrupt
bool Spi::transmit_IT(const uint8_t *data, size_t length)
{
    HAL_StatusTypeDef status = HAL_SPI_Transmit_IT(&_hspi, (uint8_t *)data, length);
    return (status == HAL_OK);
}

bool Spi::receive_IT(uint8_t *data, size_t length)
{
    HAL_StatusTypeDef status = HAL_SPI_Receive_IT(&_hspi, data, length);
    return (status == HAL_OK);
}

bool Spi::transmitReceive_IT(const uint8_t *txData, uint8_t *rxData, size_t length)
{
    HAL_StatusTypeDef status = HAL_SPI_TransmitReceive_IT(&_hspi, (uint8_t *)txData, rxData, length);
    return (status == HAL_OK);
}
