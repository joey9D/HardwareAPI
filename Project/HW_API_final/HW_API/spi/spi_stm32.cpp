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
#include "stm32_error_handle.hpp"
#include "stm32x0_gpio_mapping.hpp"

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
    RCC_PeriphCLKInitTypeDef PeriphClkInit{};

    if (_instance == SPI1)
    {
#ifdef STM32C0xx
        PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_I2S1;
        PeriphClkInit.I2s1ClockSelection = RCC_I2S1CLKSOURCE_SYSCLK;
        if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
        {
            Error_Handler();
        }
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
    _hspi.Init.Mode = static_cast<uint32_t>(_mode);
    _hspi.Init.Direction = static_cast<uint32_t>(_direction);
    _hspi.Init.DataSize = static_cast<uint32_t>(_dataSize);
    _hspi.Init.CLKPolarity = static_cast<uint32_t>(_clockPolarity);
    _hspi.Init.CLKPhase = static_cast<uint32_t>(_clockPhase);
    _hspi.Init.NSS = static_cast<uint32_t>(_nss);
    _hspi.Init.BaudRatePrescaler = static_cast<uint32_t>(_baudRatePrescaler);
    _hspi.Init.FirstBit = static_cast<uint32_t>(_firstBit);
    _hspi.Init.TIMode = static_cast<uint32_t>(_tiMode);
    _hspi.Init.CRCCalculation = static_cast<uint32_t>(_crcCalculation);
    _hspi.Init.CRCPolynomial = _crcPolynomial;
    _hspi.Init.CRCLength = static_cast<uint32_t>(_crcLength);
    _hspi.Init.NSSPMode = static_cast<uint32_t>(_nsspMode);

    // Initialize HAL SPI
    HAL_StatusTypeDef status = HAL_SPI_Init(&_hspi);
    if (status != HAL_OK)
    {
        assert(false && "HAL_SPI_Init failed!");
        return false;
    }

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
