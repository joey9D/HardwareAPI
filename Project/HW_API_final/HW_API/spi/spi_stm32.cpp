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
#include <cassert>

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
            return SPI_MODE_MASTER; // Dies ist (SPI_CR1_MSTR | SPI_CR1_SSI) in der HAL
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
            return SPI_DIRECTION_2LINES; // Full-Duplex: MOSI + MISO gleichzeitig
        case SpiDirection::HalfDuplex:
            return SPI_DIRECTION_1LINE; // Half-Duplex: Eine Leitung für Tx/Rx
        case SpiDirection::RxOnly:
            return SPI_DIRECTION_2LINES_RXONLY; // Rx-Only: Nur MISO aktiv
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
        // Plattformunabhängige Implementierung - prüft zur Laufzeit Verfügbarkeit
        // Auf Plattformen, die NSSP nicht unterstützen, wird 0 zurückgegeben
        // Auf unterstützten Plattformen die entsprechende Konstante
        uint32_t result = 0;

        switch (nssp)
        {
        case SpiNSSPMode::Software:
#if defined(SPI_NSSP_MODE_SOFTWARE)
            result = SPI_NSSP_MODE_SOFTWARE;
#endif
            break;

        case SpiNSSPMode::Hardware:
#if defined(SPI_NSSP_MODE_HARDWARE)
            result = SPI_NSSP_MODE_HARDWARE;
#endif
            break;

        default:
#if defined(SPI_NSSP_MODE_SOFTWARE)
            result = SPI_NSSP_MODE_SOFTWARE;
#endif
            break;
        }

        return result;
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
    // SpiCRCPolynomial crcPolynomial,
    uint32_t crcPolynomial,
    SpiCRCLength crcLength,
    SpiNSSPMode nsspMode)
    : _sck(sck),
      _miso(miso),
      _mosi(mosi),
      _cs(cs),
      _instance(instance),
      _mode(mode),
      _direction(direction),
      _dataSize(dataSize),
      _clockPolarity(clkPolarity),
      _clockPhase(clkPhase),
      _nss(nss),
      _baudRatePrescaler(baudRatePrescaler),
      _firstBit(firstBit),
      _tiMode(tiMode),
      _crcCalculation(crcCalculation),
      _crcPolynomial(crcPolynomial),
      _crcLength(crcLength),
      _nsspMode(nsspMode)
{
    // Nur Member initialisieren, KEINE Hardware-Initialisierung!
}

bool Spi::spi_init()
{
    RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

    if (_instance == SPI1)
    {
#ifdef STM32C0xx
        PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_SPI1;
        PeriphClkInit.I2s1ClockSelection = RCC_I2S1CLKSOURCE_SYSCLK;
#endif
        __HAL_RCC_SPI1_CLK_ENABLE();
    }
#ifdef SPI2
    else if (_instance == SPI2)
    {
        __HAL_RCC_SPI2_CLK_ENABLE();
    }
#endif
#ifdef SPI3
    else if (_instance == SPI3)
    {
        __HAL_RCC_SPI3_CLK_ENABLE();
    }
#endif
    // TODO: Peripheral clock configuration for SPIx
    // #ifdef SPI4
    //     else if (_instance == SPI4)
    //     {
    //         __HAL_RCC_SPI4_CLK_ENABLE();
    //     }
    // #endif
    else
    {
        // Unsupported SPI instance
        return false;
    }

    _sck.gpio_init();
    _miso.gpio_init();
    _mosi.gpio_init();
    _cs.gpio_init();

    _hspi.Instance = _instance;
    _hspi.Init.Mode = spiModeToHAL(_mode);
    _hspi.Init.Direction = spiDirectionToHAL(_direction);
    _hspi.Init.DataSize = spiDataSizeToHAL(_dataSize);
    _hspi.Init.CLKPolarity = spiClockPolarityToHAL(_clockPolarity);
    _hspi.Init.CLKPhase = spiClockPhaseToHAL(_clockPhase);
    _hspi.Init.NSS = spiNSSToHAL(_nss);
    _hspi.Init.BaudRatePrescaler = spiBaudRatePrescalerToHAL(_baudRatePrescaler);
    _hspi.Init.FirstBit = spiFirstBitToHAL(_firstBit);
    _hspi.Init.TIMode = spiTIModeToHAL(_tiMode);
    _hspi.Init.CRCCalculation = spiCRCCalculationToHAL(_crcCalculation);
    _hspi.Init.CRCPolynomial = _crcPolynomial;
    _hspi.Init.CRCLength = spiCRCLengthToHAL(_crcLength);
    _hspi.Init.NSSPMode = spiNSSPModeToHAL(_nsspMode);

    // Initialize HAL SPI
    HAL_StatusTypeDef status = HAL_SPI_Init(&_hspi);
    if (status != HAL_OK)
    {
        assert(false && "HAL_SPI_Init failed!");
        return false;
    }

    // // Additional configuration for Slave mode
    // if (_spiMode == SpiMode::Slave)
    // {
    //     // Ensure CR1 register is properly configured for slave mode
    //     // This addresses potential issues with certain STM32 devices
    //     _instance->CR1 &= ~(SPI_CR1_MSTR); // Clear master bit to force slave mode

    //     // General handling for STM32 in slave mode
    //     // Enable RXNE interrupt in slave mode if available in this STM32 family
    //     if ((_instance->CR2 & SPI_CR2_RXNEIE) == 0)
    //     {
    //         _instance->CR2 |= SPI_CR2_RXNEIE;
    //     }

    //     // For FullDuplex or RxOnly direction, ensure the slave is ready to receive
    //     if (_spiDirection == SpiDirection::FullDuplex || _spiDirection == SpiDirection::RxOnly)
    //     {
    //         _instance->CR1 |= SPI_CR1_SSI; // Set internal slave select
    //     }
    // }

    // // Spezielle Behandlung für HalfDuplex-Modus als Transmit-Only
    // if (_spiDirection == SpiDirection::HalfDuplex)
    // {
    //     // In HalfDuplex-Modus kann das BIDIOE-Bit gesetzt werden, um Transmit-Only zu aktivieren
    //     SET_BIT(_hspi.Instance->CR1, SPI_CR1_BIDIOE);
    // }

    // // Überprüfen und korrigieren der Register-Konfiguration nach der HAL-Initialisierung
    // // Diese Konfiguration ist für alle STM32-Plattformen allgemein gültig
    // if (_spiMode == SpiMode::Slave)
    // {
    //     // Für Slave-Modus: Explizit CR1 konfigurieren
    //     // Stelle sicher, dass das MSTR-Bit für Slave-Modus gelöscht ist
    //     CLEAR_BIT(_hspi.Instance->CR1, SPI_CR1_MSTR);

    //     // Bei Problemen mit NSS im Hard-Input-Modus kann das SSI-Bit gelöscht werden
    //     if (_spiNSS == SpiNSS::Hard_In)
    //     {
    //         CLEAR_BIT(_hspi.Instance->CR1, SPI_CR1_SSI);
    //     }

    //     // CR1 konfigurieren mit relevanten Einstellungen
    //     uint32_t cr1Config = 0;

    //     // Richtungseinstellung
    //     cr1Config |= spiDirectionToHAL(_spiDirection);

    //     // Taktpolarität und -phase
    //     cr1Config |= spiClockPolarityToHAL(_spiClockPolarity);
    //     cr1Config |= spiClockPhaseToHAL(_spiClockPhase);

    //     // NSS-Management (für Software NSS)
    //     if (_spiNSS == SpiNSS::Soft)
    //     {
    //         cr1Config |= SPI_CR1_SSM;
    //     }

    //     // Andere Einstellungen beibehalten
    //     cr1Config |= spiFirstBitToHAL(_spiFirstBit);

    //     // Aktuelle CR1-Konfiguration sichern
    //     uint32_t currentCR1 = _hspi.Instance->CR1;

    //     // CR1 aktualisieren - bestimmte Bits beibehalten, andere ersetzen
    //     _hspi.Instance->CR1 = (currentCR1 & ~(SPI_CR1_MSTR | SPI_CR1_SSI)) | cr1Config;

    //     // SPI aktivieren
    //     SET_BIT(_hspi.Instance->CR1, SPI_CR1_SPE);
    // }

    return true;
}

// Polling
bool Spi::transmit(const uint8_t *data, uint16_t length, uint32_t timeout)
{
    HAL_StatusTypeDef status = HAL_SPI_Transmit(&_hspi, (uint8_t *)data, length, timeout);
    return (status == HAL_OK);
}

bool Spi::receive(uint8_t *data, uint16_t length, uint32_t timeout)
{
    HAL_StatusTypeDef status = HAL_SPI_Receive(&_hspi, (uint8_t *)data, length, timeout);
    return (status == HAL_OK);
}

bool Spi::transmitReceive(const uint8_t *txData, uint8_t *rxData, uint16_t length, uint32_t timeout)
{
    HAL_StatusTypeDef status = HAL_SPI_TransmitReceive(&_hspi, (uint8_t *)txData, rxData, length, timeout);
    return (status == HAL_OK);
}

SPI_HandleTypeDef *Spi::get_handle()
{
    return &_hspi;
}

// Dma
void Spi::set_dma(Dma *dma)
{
    _dma = dma;
}

Dma *Spi::get_dma() const
{
    return _dma;
}

bool Spi::transmit_DMA(const uint8_t *data, uint16_t length, uint32_t timeout)
{
    if (_dma == nullptr)
    {
        assert(false && "DMA not set for SPI!");
        return false;
    }

    HAL_StatusTypeDef status = HAL_SPI_Transmit_DMA(&_hspi, (uint8_t *)data, length);
    if (status != HAL_OK)
    {
        assert(false && "HAL_SPI_Transmit_DMA failed!");
        return false;
    }

    if (timeout == 0)
    {
        return true;
    }

    // blocked; waiting with HAL-State
    uint32_t startTime = HAL_GetTick();
    while (!_dma->isTransferComplete())
    {
        if ((HAL_GetTick() - startTime) > timeout)
        {
            HAL_SPI_Abort(&_hspi);
            return false;
        }

        if (_dma->isTransferError())
        {
            return false;
        }
    }
    return true;
}

bool Spi::receive_DMA(uint8_t *data, uint16_t length, uint32_t timeout)
{
    if (_dma == nullptr)
    {
        assert(false && "DMA not set for SPI!");
        return false;
    }

    HAL_StatusTypeDef status = HAL_SPI_Receive_DMA(&_hspi, data, length);
    if (status != HAL_OK)
    {
        assert(false && "HAL_SPI_Receive_DMA failed!");
        return false;
    }

    if (timeout == 0)
    {
        return true;
    }

    // blocked; waiting with HAL-State
    uint32_t startTime = HAL_GetTick();
    while (!_dma->isTransferComplete())
    {
        if ((HAL_GetTick() - startTime) > timeout)
        {
            HAL_SPI_Abort(&_hspi);
            return false;
        }

        if (_dma->isTransferError())
        {
            return false;
        }
    }
    return true;
}

bool Spi::transmitReceive_DMA(const uint8_t *txData, uint8_t *rxData, uint16_t length, uint32_t timeout)
{
    if (_dma == nullptr)
    {
        assert(false && "DMA not set for SPI!");
        return false;
    }

    HAL_StatusTypeDef status = HAL_SPI_TransmitReceive_DMA(&_hspi, (uint8_t *)txData, rxData, length);
    if (status != HAL_OK)
    {
        assert(false && "HAL_SPI_TransmitReceive_DMA failed!");
        return false;
    }

    if (timeout == 0)
    {
        return true;
    }

    uint32_t startTime = HAL_GetTick();
    while (!_dma->isTransferComplete())
    {
        if ((HAL_GetTick() - startTime) > timeout)
        {
            HAL_SPI_Abort(&_hspi);
            return false;
        }

        if (_dma->isTransferError())
        {
            return false;
        }
    }
    return true;
}
