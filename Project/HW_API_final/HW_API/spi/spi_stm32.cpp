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
        case SpiDirection::TxOnly:
            return SPI_DIRECTION_1LINE; // Tx-Only: wie Half-Duplex, aber BIDIOE wird gesetzt
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
        // STM32G0 doesn't support NSSP mode, return safe default
#ifdef SPI_NSSP_MODE_SOFTWARE
        switch (nssp)
        {
        case SpiNSSPMode::Software:
            return SPI_NSSP_MODE_SOFTWARE;
        case SpiNSSPMode::Hardware:
            return SPI_NSSP_MODE_HARDWARE;
        default:
            return SPI_NSSP_MODE_SOFTWARE;
        }
#else
        // STM32G0 fallback - return 0 as it's not supported
        return 0;
#endif
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
        // STM32G0 doesn't support these specific CRC polynomial constants
#ifdef SPI_CRC_POLYNOMIAL_7
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
#else
        // STM32G0 fallback - use standard polynomial values
        switch (poly)
        {
        case SpiCRCPolynomial::Polynomial7:
            return 7; // Direct polynomial value
        case SpiCRCPolynomial::Polynomial8:
            return 8;
        case SpiCRCPolynomial::Polynomial16:
            return 16;
        default:
            return 7;
        }
#endif
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
    SpiNSSPMode nsspMode,
    SpiDMA *dma)
    : _sck(sck), _miso(miso), _mosi(mosi), _cs(cs),
      _instance(instance),
      _spiMode(mode), _spiDirection(direction), _spiDataSize(dataSize),
      _spiClockPolarity(clkPolarity), _spiClockPhase(clkPhase), _spiNSS(nss),
      _spiBaudRatePrescaler(baudRatePrescaler), _spiFirstBit(firstBit),
      _spiTIMode(tiMode), _spiCRCCalculation(crcCalculation),
      _spiCRCPolynomial(crcPolynomial), _spiCRCLength(crcLength),
      _spiNSSPMode(nsspMode), _dma(dma)
{
    // Nur Member initialisieren, KEINE Hardware-Initialisierung!
}

bool Spi::spi_init()
{
    // Enable SPI clock based on instance
    if (_instance == SPI1)
    {
        __HAL_RCC_SPI1_CLK_ENABLE();
    }
    else if (_instance == SPI2)
    {
        __HAL_RCC_SPI2_CLK_ENABLE();
    }
    // STM32G0 supports only SPI1 and SPI2
#ifdef SPI3
    else if (_instance == SPI3)
    {
        __HAL_RCC_SPI3_CLK_ENABLE();
    }
#endif
#ifdef SPI4
    else if (_instance == SPI4)
    {
        __HAL_RCC_SPI4_CLK_ENABLE();
    }
#endif
#ifdef SPI5
    else if (_instance == SPI5)
    {
        __HAL_RCC_SPI5_CLK_ENABLE();
    }
#endif
#ifdef SPI6
    else if (_instance == SPI6)
    {
        __HAL_RCC_SPI6_CLK_ENABLE();
    }
#endif
    else
    {
        // Unsupported SPI instance
        return false;
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

    // Spezielle Behandlung für TxOnly-Modus
    if (_spiDirection == SpiDirection::TxOnly)
    {
        // BIDIOE-Bit setzen für Transmit-Only im Half-Duplex Modus
        SET_BIT(_hspi.Instance->CR1, SPI_CR1_BIDIOE);
    }

    // MSTR explizit für Master setzen (Absicherung gegen HAL-Inkonsistenzen)
    if (_spiMode == SpiMode::Master)
    {
        // SET_BIT(_hspi.Instance->CR1, SPI_CR1_MSTR);
    }

    // WICHTIG: SPI explizit aktivieren, da HAL dies nicht automatisch macht
    // Wenn dieser Teil später auskommentiert wird, wird die HAL den SPI
    // automatisch während des ersten Übertragungs-/Empfangsvorgangs aktivieren
    // AUSKOMMENTIEREN FÜR HAL-STANDARD-VERHALTEN: ↓
    // SET_BIT(_hspi.Instance->CR1, SPI_CR1_SPE);

    // Überprüfen und korrigieren der CR1/CR2-Register nach HAL-Initialisierung
    // if (_spiMode == SpiMode::Slave)
    // {
    //     // Für Slave-Modus: Überprüfen, ob Konfiguration korrekt ist
    //     // Wenn CR1 vollständig 0 ist, könnte ein HAL-Initialisierungsproblem vorliegen
    //     if ((_hspi.Instance->CR1 & (SPI_CR1_MSTR)) == 0)
    //     {
    //         // Für Slave: Explizit nur die benötigten Bits setzen
    //         // Nicht MSTR-Bit setzen, da wir im Slave-Modus sind
    //         // SSI-Bit nicht setzen für Hardware NSS (falls relevant)

    //         // Baudrate-Einstellungen beibehalten, auch wenn sie für Slave ignoriert werden
    //         uint32_t baudrate = spiBaudRatePrescalerToHAL(_spiBaudRatePrescaler);
    //         MODIFY_REG(_hspi.Instance->CR1, SPI_CR1_BR, baudrate);

    //         // Weitere spezifische Slave-Konfigurationen hier ...
    //     }
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

// DMA
bool Spi::transmit_DMA(const uint8_t *data, uint16_t length, uint32_t timeout)
{
    // Prüfen ob DMA verfügbar und initialisiert
    if (_dma == nullptr)
    {
        return false;
    }

    // DMA TX-Kanal initialisieren, falls noch nicht geschehen
    if (!_dma->isTxReady())
    {
        if (!_dma->init_dma_TX())
        {
            return false;
        }
    }

    // DMA-Transfer starten
    HAL_StatusTypeDef status = HAL_SPI_Transmit_DMA(&_hspi, (uint8_t *)data, length);
    if (status != HAL_OK)
    {
        return false;
    }

    // Wenn timeout = 0, sofort zurückkehren (nicht-blockierend)
    if (timeout == 0)
    {
        return true;
    }

    // Warten auf DMA-Completion mit Timeout (blockierend)
    uint32_t startTime = HAL_GetTick();
    while (_dma->isTransferInProgress_TX())
    {
        if ((HAL_GetTick() - startTime) > timeout)
        {
            // Timeout erreicht - Transfer abbrechen
            _dma->abortTransfer_TX();
            return false;
        }
    }

    return true;
}

bool Spi::receive_DMA(uint8_t *data, uint16_t length, uint32_t timeout)
{
    // Prüfen ob DMA verfügbar und initialisiert
    if (_dma == nullptr)
    {
        return false;
    }

    // DMA RX-Kanal initialisieren, falls noch nicht geschehen
    if (!_dma->isRxReady())
    {
        if (!_dma->init_dma_RX())
        {
            return false;
        }
    }

    // DMA-Transfer starten
    HAL_StatusTypeDef status = HAL_SPI_Receive_DMA(&_hspi, data, length);
    if (status != HAL_OK)
    {
        return false;
    }

    // Wenn timeout = 0, sofort zurückkehren (nicht-blockierend)
    if (timeout == 0)
    {
        return true;
    }

    // Warten auf DMA-Completion mit Timeout (blockierend)
    uint32_t startTime = HAL_GetTick();
    while (_dma->isTransferInProgress_RX())
    {
        if ((HAL_GetTick() - startTime) > timeout)
        {
            // Timeout erreicht - Transfer abbrechen
            _dma->abortTransfer_RX();
            return false;
        }
    }

    return true;
}

bool Spi::transmitReceive_DMA(const uint8_t *txData, uint8_t *rxData, uint16_t length, uint32_t timeout)
{
    // Prüfen ob DMA verfügbar und initialisiert
    if (_dma == nullptr)
    {
        return false;
    }

    // Beide DMA-Kanäle initialisieren, falls noch nicht geschehen
    if (!_dma->areBothReady())
    {
        if (!_dma->init_dma())
        {
            return false;
        }
    }

    // DMA-Transfer starten
    HAL_StatusTypeDef status = HAL_SPI_TransmitReceive_DMA(&_hspi, (uint8_t *)txData, rxData, length);
    if (status != HAL_OK)
    {
        return false;
    }

    // Wenn timeout = 0, sofort zurückkehren (nicht-blockierend)
    if (timeout == 0)
    {
        return true;
    }

    // Warten auf DMA-Completion mit Timeout (blockierend)
    uint32_t startTime = HAL_GetTick();
    while (_dma->isAnyTransferInProgress())
    {
        if ((HAL_GetTick() - startTime) > timeout)
        {
            // Timeout erreicht - Transfer abbrechen
            _dma->abortTransfer();
            return false;
        }
    }

    return true;
}

// Interrupt
bool Spi::transmit_IT(const uint8_t *data, uint16_t length, uint32_t timeout)
{
    HAL_StatusTypeDef status = HAL_SPI_Transmit_IT(&_hspi, (uint8_t *)data, length);
    if (status != HAL_OK)
    {
        return false;
    }

    // Warten auf Interrupt-Completion mit Timeout
    uint32_t startTime = HAL_GetTick();
    while (HAL_SPI_GetState(&_hspi) != HAL_SPI_STATE_READY)
    {
        if ((HAL_GetTick() - startTime) > timeout)
        {
            // Timeout erreicht - Transfer abbrechen
            HAL_SPI_Abort_IT(&_hspi);
            return false;
        }
    }

    return true;
}

bool Spi::receive_IT(uint8_t *data, uint16_t length, uint32_t timeout)
{
    HAL_StatusTypeDef status = HAL_SPI_Receive_IT(&_hspi, data, length);
    if (status != HAL_OK)
    {
        return false;
    }

    // Warten auf Interrupt-Completion mit Timeout
    uint32_t startTime = HAL_GetTick();
    while (HAL_SPI_GetState(&_hspi) != HAL_SPI_STATE_READY)
    {
        if ((HAL_GetTick() - startTime) > timeout)
        {
            // Timeout erreicht - Transfer abbrechen
            HAL_SPI_Abort_IT(&_hspi);
            return false;
        }
    }

    return true;
}

bool Spi::transmitReceive_IT(const uint8_t *txData, uint8_t *rxData, uint16_t length, uint32_t timeout)
{
    HAL_StatusTypeDef status = HAL_SPI_TransmitReceive_IT(&_hspi, (uint8_t *)txData, rxData, length);
    if (status != HAL_OK)
    {
        return false;
    }

    // Warten auf Interrupt-Completion mit Timeout
    uint32_t startTime = HAL_GetTick();
    while (HAL_SPI_GetState(&_hspi) != HAL_SPI_STATE_READY)
    {
        if ((HAL_GetTick() - startTime) > timeout)
        {
            // Timeout erreicht - Transfer abbrechen
            HAL_SPI_Abort_IT(&_hspi);
            return false;
        }
    }

    return true;
}

SPI_HandleTypeDef *Spi::get_handle()
{
    return &_hspi;
}

void Spi::set_dma(SpiDMA *dma)
{
    _dma = dma;
}

SpiDMA *Spi::get_dma() const
{
    return _dma;
}

bool Spi::isDmaTransmitComplete()
{
    if (_dma == nullptr)
    {
        return false;
    }
    return !_dma->isTransferInProgress_TX();
}

bool Spi::isDmaReceiveComplete()
{
    if (_dma == nullptr)
    {
        return false;
    }
    return !_dma->isTransferInProgress_RX();
}

bool Spi::isDmaTransmitReceiveComplete()
{
    if (_dma == nullptr)
    {
        return false;
    }
    return !_dma->isAnyTransferInProgress();
}

bool Spi::isDmaTransferInProgress()
{
    if (_dma == nullptr)
    {
        return false;
    }
    return _dma->isAnyTransferInProgress();
}

bool Spi::abortDmaTransfer()
{
    if (_dma == nullptr)
    {
        return false;
    }
    return _dma->abortTransfer();
}