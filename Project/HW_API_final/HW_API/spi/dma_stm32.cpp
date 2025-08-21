#ifdef STM32_PLATFORM

#include "../drivers/stm32_hal_wrapper/common/stm32_hal_inc.hpp"
#include "dma_stm32.hpp"
#include <cassert>

// Globale DMA Handles für Interrupt-System (extern Deklarationen in stm32xx_it.h)
DMA_HandleTypeDef hdma_spi1_tx;
DMA_HandleTypeDef hdma_spi1_rx;

#if defined(SPI2)
DMA_HandleTypeDef hdma_spi2_tx;
DMA_HandleTypeDef hdma_spi2_rx;
#endif

// Basisdefinition
template <SPI_TypeDef *SPIx>
struct SPIDmaHandlers
{
    static DMA_HandleTypeDef &getTxHandle();
    static DMA_HandleTypeDef &getRxHandle();
};

template <>
struct SPIDmaHandlers<SPI1>
{
    static DMA_HandleTypeDef &getTxHandle() { return hdma_spi1_tx; }
    static DMA_HandleTypeDef &getRxHandle() { return hdma_spi1_rx; }
};

#if defined(SPI2)
template <>
struct SPIDmaHandlers<SPI2>
{
    static DMA_HandleTypeDef &getTxHandle() { return hdma_spi2_tx; }
    static DMA_HandleTypeDef &getRxHandle() { return hdma_spi2_rx; }
};
#endif

/**
 * @brief toHal helper functions
 *
 */
namespace
{
    using namespace HW_API::STM32;

    uint32_t requestToHal(DmaRequest request)
    {
        switch (request)
        {
        case DmaRequest::SPI1_TX:
            return DMA_REQUEST_SPI1_TX;
        case DmaRequest::SPI1_RX:
            return DMA_REQUEST_SPI1_RX;
        // Fügen Sie hier weitere Fälle für andere SPI-Instanzen hinzu
        default:
            assert(false && "Unbekannte DMA-Anforderung");
            return 0;
        }
    }

    uint32_t periphIncToHal(DmaPeriphInc inc)
    {
        switch (inc)
        {
        case DmaPeriphInc::ENABLE:
            return DMA_PERIPH_INC_ENABLE;
        case DmaPeriphInc::DISABLE:
            return DMA_PERIPH_INC_DISABLE;
        default:
            assert(false && "Unrichtige DMA-Peripherie-Inkrementierung");
            return 0;
        }
    }

    uint32_t memIncToHal(DmaMemInc inc)
    {
        switch (inc)
        {
        case DmaMemInc::ENABLE:
            return DMA_MEMORY_INC_ENABLE;
        case DmaMemInc::DISABLE:
            return DMA_MEMORY_INC_DISABLE;
        default:
            assert(false && "Unrichtige DMA-Speicher-Inkrementierung");
            return 0;
        }
    }

    uint32_t periphDataAlignmentToHal(DmaPeriphDataSizeAlignment alignment)
    {
        switch (alignment)
        {
        case DmaPeriphDataSizeAlignment::BYTE:
            return DMA_PERIPH_DATA_SIZE_BYTE;
        case DmaPeriphDataSizeAlignment::HALFWORD:
            return DMA_PERIPH_DATA_SIZE_HALFWORD;
        case DmaPeriphDataSizeAlignment::WORD:
            return DMA_PERIPH_DATA_SIZE_WORD;
        default:
            assert(false && "Unrichtige DMA-Peripherie-Datenausrichtung");
            return 0;
        }
    }

    uint32_t memDataAlignmentToHal(DmaMemDataSizeAlignment alignment)
    {
        switch (alignment)
        {
        case DmaMemDataSizeAlignment::BYTE:
            return DMA_MEMORY_DATA_SIZE_BYTE;
        case DmaMemDataSizeAlignment::HALFWORD:
            return DMA_MEMORY_DATA_SIZE_HALFWORD;
        case DmaMemDataSizeAlignment::WORD:
            return DMA_MEMORY_DATA_SIZE_WORD;
        default:
            assert(false && "Unrichtige DMA-Speicher-Datenausrichtung");
            return 0;
        }
    }

    uint32_t modeToHal(DmaMode mode)
    {
        switch (mode)
        {
        case DmaMode::NORMAL:
            return DMA_NORMAL;
        case DmaMode::CIRCULAR:
            return DMA_CIRCULAR;
        default:
            assert(false && "Unrichtiger DMA-Modus");
            return 0;
        }
    }

    uint32_t priorityToHal(DmaPriority priority)
    {
        switch (priority)
        {
        case DmaPriority::LOW:
            return DMA_PRIORITY_LOW;
        case DmaPriority::MEDIUM:
            return DMA_PRIORITY_MEDIUM;
        case DmaPriority::HIGH:
            return DMA_PRIORITY_HIGH;
        case DmaPriority::VERY_HIGH:
            return DMA_PRIORITY_VERY_HIGH;
        default:
            assert(false && "Unrichtige DMA-Priorität");
            return 0;
        }
    }
}

// Konstruktor ohne SPI-Handle
Dma::Dma(
    DmaRequest request_tx,
    DmaRequest request_rx,
    DmaDirection direction,
    DmaPeriphInc periphInc,
    DmaMemInc memInc,
    DmaPeriphDataSizeAlignment periphDataAlignment,
    DmaMemDataSizeAlignment memDataAlignment,
    DmaMode mode,
    DmaPriority priority)
    : _hspi(nullptr),
      _request_tx(request_tx),
      _request_rx(request_rx),
      //   _direction(direction),
      _periphInc(periphInc),
      _memInc(memInc),
      _periphDataAlignment(periphDataAlignment),
      _memDataAlignment(memDataAlignment),
      _mode(mode),
      _priority(priority),
      _txState(DmaTxState::READY)
{
    // Konstruktor-Body bleibt leer
}

void Dma::setSpiHandle(SPI_HandleTypeDef *hspi)
{
    _hspi = hspi;
}

// Beide DMA initialisieren
bool Dma::dma_init()
{
    // Prüfen, ob ein SPI-Handle gesetzt wurde
    if (_hspi == nullptr || _hspi->Instance == nullptr)
    {
        assert(false && "SPI handle not set. Call setSpiHandle() before dma_init()");
        return false;
    }

    __HAL_RCC_DMA1_CLK_ENABLE();

    bool tx_init = false;
    bool rx_init = false;

    if (_hspi->Instance == SPI1)
    {
        tx_init = dma_init_TX<SPI1>();
        rx_init = dma_init_RX<SPI1>();
    }
    else if (_hspi->Instance == SPI2)
    {
        tx_init = dma_init_TX<SPI2>();
        rx_init = dma_init_RX<SPI2>();
    }
    else
    {
        assert(false && "Unsupported SPI instance for DMA");
        return false;
    }

    return tx_init && rx_init;
}

bool Dma::dma_interrupts(uint32_t priority)
{
    if (!__HAL_RCC_DMA1_CLK_ENABLE())
    {
        assert(false && "DMA1 clock not enabled");
        __HAL_RCC_DMA1_CLK_ENABLE();
    }

    if (_hspi->Instance == SPI1)
    {
        HAL_NVIC_SetPriority(DMA1_Channel2_3_IRQHn, priority, 0);
        HAL_NVIC_EnableIRQ(DMA1_Channel2_3_IRQn);
    }
#ifdef SPI2
    else if (_hspi->Instance == SPI2)
    {
#ifdef DMA1_Channel4_5_IRQn
        HAL_NVIC_SetPriority(DMA1_Channel4_5_IRQn, priority, 0);
        HAL_NVIC_EnableIRQ(DMA1_Channel4_5_IRQn);

#elif defined(DMA1_Channel4_5_6_7_IRQn)
        // DMA1_Channel4_5_6_7_IRQn interrupt configuration (für SPI2 auf STM32G0)
        HAL_NVIC_SetPriority(DMA1_Channel4_5_6_7_IRQn, priority, 0);
        HAL_NVIC_EnableIRQ(DMA1_Channel4_5_6_7_IRQn);
#endif
    }
#endif
    else
    {
        return false;
    }
    return true;
}

bool Dma::isTransferComplete() const
{
    if (_hspi == nullptr || _hspi->Instance == nullptr)
    {
        assert(false && "SPI handle not set. Call setSpiHandle() before isTransferComplete()");
        return false;
    }

    return (HAL_SPI_GetState(_hspi) == HAL_SPI_STATE_READY);
}

bool Dma::isTransferBusy() const
{
    if (_hspi == nullptr || _hspi->Instance == nullptr)
    {
        assert(false && "SPI handle not set. Call setSpiHandle() before isTransferBusy()");
        return false;
    }

    HAL_SPI_StateTypeDef state = HAL_SPI_GetState(_hspi);
    return (
        state == HAL_SPI_STATE_BUSY_TX ||
        state == HAL_SPI_STATE_BUSY_RX ||
        state == HAL_SPI_STATE_BUSY_TX_RX);
}

bool Dma::isTransferError() const
{
    if (_hspi == nullptr || _hspi->Instance == nullptr)
    {
        assert(false && "SPI handle not set. Call setSpiHandle() before isTransferError()");
        return false;
    }

    return (HAL_SPI_GetState(_hspi) != HAL_SPI_ERROR_NONE);
}

#endif // STM32_PLATFORM