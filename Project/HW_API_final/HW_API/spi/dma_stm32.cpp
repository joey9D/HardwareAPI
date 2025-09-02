#ifdef STM32_PLATFORM

#include "../drivers/stm32_hal_wrapper/common/stm32_hal_inc.hpp"
#include "hw_enum_stm32.hpp"
#include "dma_stm32.hpp"
#include <cassert>

// Globale DMA Handles für Interrupt-System (extern Deklarationen in stm32xx_it.h)
DMA_HandleTypeDef hdma_spi1_tx;
DMA_HandleTypeDef hdma_spi1_rx;
#if defined(SPI2)
DMA_HandleTypeDef hdma_spi2_tx;
DMA_HandleTypeDef hdma_spi2_rx;
#endif
#if defined(SPI3)
DMA_HandleTypeDef hdma_spi3_tx;
DMA_HandleTypeDef hdma_spi3_rx;
#endif
#if defined(SPI4)
DMA_HandleTypeDef hdma_spi4_tx;
DMA_HandleTypeDef hdma_spi4_rx;
#endif

DMA_HandleTypeDef *getTxHandle(SPI_TypeDef *SPIx)
{
    if (SPIx == SPI1)
    {
        return &hdma_spi1_tx;
    }
#if defined(SPI2)
    else if (SPIx == SPI2)
    {
        return &hdma_spi2_tx;
    }
#endif
#if defined(SPI3)
    else if (SPIx == SPI3)
    {
        return &hdma_spi3_tx;
    }
#endif
#if defined(SPI4)
    else if (SPIx == SPI4)
    {
        return &hdma_spi4_tx;
    }
#endif
    else
    {
        assert(false && "Unbekannte SPI-Instanz");
        return nullptr;
    }
}

DMA_HandleTypeDef *getRxHandle(SPI_TypeDef *SPIx)
{
    if (SPIx == SPI1)
    {
        return &hdma_spi1_rx;
    }
#if defined(SPI2)
    else if (SPIx == SPI2)
    {
        return &hdma_spi2_rx;
    }
#endif
#if defined(SPI3)
    else if (SPIx == SPI3)
    {
        return &hdma_spi3_rx;
    }
#endif
#if defined(SPI4)
    else if (SPIx == SPI4)
    {
        return &hdma_spi4_rx;
    }
#endif
    else
    {
        assert(false && "Unbekannte SPI-Instanz");
        return nullptr;
    }
}

/**
 * @brief toHal helper functions
 *
 */
// namespace
// {
//     using namespace HW_API::STM32;

//     uint32_t requestToHal(DmaRequest request)
//     {
//         switch (request)
//         {
//         case DmaRequest::SPI1_TX:
//             return DMA_REQUEST_SPI1_TX;
//         case DmaRequest::SPI1_RX:
//             return DMA_REQUEST_SPI1_RX;
//         // Fügen Sie hier weitere Fälle für andere SPI-Instanzen hinzu
//         default:
//             assert(false && "Unbekannte DMA-Anforderung");
//             return 0;
//         }
//     }

//     uint32_t periphIncToHal(DmaPeriphInc inc)
//     {
//         switch (inc)
//         {
//         case DmaPeriphInc::Enable:
//             return DMA_PINC_ENABLE;
//         case DmaPeriphInc::Disable:
//             return DMA_PINC_DISABLE;
//         default:
//             assert(false && "Unrichtige DMA-Peripherie-Inkrementierung");
//             return 0;
//         }
//     }

//     uint32_t memIncToHal(DmaMemInc inc)
//     {
//         switch (inc)
//         {
//         case DmaMemInc::Enable:
//             return DMA_MINC_ENABLE;
//         case DmaMemInc::Disable:
//             return DMA_MINC_DISABLE;
//         default:
//             assert(false && "Unrichtige DMA-Speicher-Inkrementierung");
//             return 0;
//         }
//     }

//     uint32_t periphDataAlignmentToHal(DmaPeriphDataSizeAlignment alignment)
//     {
//         switch (alignment)
//         {
//         case DmaPeriphDataSizeAlignment::Byte:
//             return DMA_PDATAALIGN_BYTE;
//         case DmaPeriphDataSizeAlignment::HalfWord:
//             return DMA_PDATAALIGN_HALFWORD;
//         case DmaPeriphDataSizeAlignment::Word:
//             return DMA_PDATAALIGN_WORD;
//         default:
//             assert(false && "Unrichtige DMA-Peripherie-Datenausrichtung");
//             return 0;
//         }
//     }

//     uint32_t memDataAlignmentToHal(DmaMemDataSizeAlignment alignment)
//     {
//         switch (alignment)
//         {
//         case DmaMemDataSizeAlignment::Byte:
//             return DMA_MDATAALIGN_BYTE;
//         case DmaMemDataSizeAlignment::HalfWord:
//             return DMA_MDATAALIGN_HALFWORD;
//         case DmaMemDataSizeAlignment::Word:
//             return DMA_MDATAALIGN_WORD;
//         default:
//             assert(false && "Unrichtige DMA-Speicher-Datenausrichtung");
//             return 0;
//         }
//     }

//     uint32_t modeToHal(DmaMode mode)
//     {
//         switch (mode)
//         {
//         case DmaMode::Normal:
//             return DMA_NORMAL;
//         case DmaMode::Circular:
//             return DMA_CIRCULAR;
//         default:
//             assert(false && "Unrichtiger DMA-Modus");
//             return 0;
//         }
//     }

//     uint32_t priorityToHal(DmaPriority priority)
//     {
//         switch (priority)
//         {
//         case DmaPriority::Low:
//             return DMA_PRIORITY_LOW;
//         case DmaPriority::Medium:
//             return DMA_PRIORITY_MEDIUM;
//         case DmaPriority::High:
//             return DMA_PRIORITY_HIGH;
//         case DmaPriority::VeryHigh:
//             return DMA_PRIORITY_VERY_HIGH;
//         default:
//             assert(false && "Unrichtige DMA-Priorität");
//             return 0;
//         }
//     }
// }

// Konstruktor ohne SPI-Handle
Dma::Dma(
    DmaRequest request_tx,
    DmaRequest request_rx,
    // DmaDirection direction,
    DmaPeriphInc periphInc,
    DmaMemInc memInc,
    DmaPeriphDataSizeAlignment periphDataAlignment,
    DmaMemDataSizeAlignment memDataAlignment,
    DmaMode mode,
    DmaPriority priority,
    DMA_Channel_TypeDef *instance_tx,
    DMA_Channel_TypeDef *instance_rx)
    : _hspi(nullptr),
      _instance_tx(instance_tx),
      _instance_rx(instance_rx),
      _request_tx(request_tx),
      _request_rx(request_rx),
      //   _direction(direction),
      _periphInc(periphInc),
      _memInc(memInc),
      _periphDataAlignment(periphDataAlignment),
      _memDataAlignment(memDataAlignment),
      _mode(mode),
      _priority(priority)
{
    // Konstruktor-Body bleibt leer
}

void Dma::setSpiHandle(SPI_HandleTypeDef *hspi)
{
    _hspi = hspi;

    if (_instance_tx == nullptr)
    {
        _instance_tx = getDefaultTxChannel(hspi->Instance);
    }
    if (_instance_rx == nullptr)
    {
        _instance_rx = getDefaultRxChannel(hspi->Instance);
    }
}

DMA_Channel_TypeDef *Dma::getDefaultTxChannel(SPI_TypeDef *spiInstance)
{
    if (spiInstance == SPI1)
    {
        return DMA1_Channel3;
    }
#if defined(SPI2)
    else if (spiInstance == SPI2)
    {
        return DMA1_Channel5; // Default für SPI2 TX
    }
#endif
#if defined(SPI3)
    else if (spiInstance == SPI3)
    {
        return DMA2_Channel2; // Default für SPI3 TX (je nach MCU)
    }
#endif

    assert(false && "Unsupported SPI instance for default TX channel");
    return nullptr;
}

DMA_Channel_TypeDef *Dma::getDefaultRxChannel(SPI_TypeDef *spiInstance)
{
    if (spiInstance == SPI1)
    {
        return DMA1_Channel2; // Default für SPI1 RX
    }
#if defined(SPI2)
    else if (spiInstance == SPI2)
    {
        return DMA1_Channel4; // Default für SPI2 RX
    }
#endif
#if defined(SPI3)
    else if (spiInstance == SPI3)
    {
        return DMA2_Channel1; // Default für SPI3 RX (je nach MCU)
    }
#endif

    assert(false && "Unsupported SPI instance for default RX channel");
    return nullptr;
}

bool Dma::dma_init()
{
    if (_hspi == nullptr || _hspi->Instance == nullptr)
    {
        assert(false && "SPI handle not set. Call setSpiHandle() before dma_init()");
        return false;
    }

    if (_instance_tx == nullptr && _instance_rx == nullptr)
    {
        return true;
    }

    __HAL_RCC_DMA1_CLK_ENABLE();

// dma2
#if defined(DMA2)
    if ((_instance_tx && _instance_tx >= DMA2_Channel1) ||
        (_instance_rx && _instance_rx >= DMA2_Channel1))
    {
        __HAL_RCC_DMA2_CLK_ENABLE();
    }
#endif

    bool success = true;

    // case 10 or 11: TX-channel
    if (_instance_tx != nullptr)
    {
        if (!dma_init_tx(_hspi->Instance))
        {
            assert(false && "DMA TX initialization failed");
            success = false;
        }
    }

    // case 01 or 11: RX-channel
    if (_instance_rx != nullptr)
    {
        if (!dma_init_rx(_hspi->Instance))
        {
            assert(false && "DMA RX initialization failed");
            success = false;
        }
    }

    return success;
}

bool Dma::dma_init_tx(void *spi_instance)
{
    SPI_TypeDef *SPIx = static_cast<SPI_TypeDef *>(spi_instance);
    return stm32_dma_init_tx(SPIx);
}

bool Dma::dma_init_rx(void *spi_instance)
{
    SPI_TypeDef *SPIx = static_cast<SPI_TypeDef *>(spi_instance);
    return stm32_dma_init_rx(SPIx);
}

bool Dma::stm32_dma_init_tx(SPI_TypeDef *SPIx)
{
    if (_hspi == nullptr || _hspi->Instance == nullptr)
    {
        assert(false && "SPI handle not set. Call setSpiHandle() before dma_init_TX()");
        return false;
    }

    DMA_HandleTypeDef *dma_handle_tx = getTxHandle(SPIx);
    if (dma_handle_tx == nullptr) // HINZUGEFÜGT: Null-Check
    {
        assert(false && "Failed to get TX DMA handle");
        return false;
    }

    dma_handle_tx->Instance = _instance_tx;
    dma_handle_tx->Init.Request = static_cast<uint32_t>(_request_tx);
    dma_handle_tx->Init.Direction = DMA_MEMORY_TO_PERIPH;
    dma_handle_tx->Init.PeriphInc = static_cast<uint32_t>(_periphInc);
    dma_handle_tx->Init.MemInc = static_cast<uint32_t>(_memInc);
    dma_handle_tx->Init.PeriphDataAlignment = static_cast<uint32_t>(_periphDataAlignment);
    dma_handle_tx->Init.MemDataAlignment = static_cast<uint32_t>(_memDataAlignment);
    dma_handle_tx->Init.Mode = static_cast<uint32_t>(_mode);
    dma_handle_tx->Init.Priority = static_cast<uint32_t>(_priority);

    // HAL DMA Initialisierung
    if (HAL_DMA_Init(dma_handle_tx) != HAL_OK)
    {
        return false;
    }

    // DMA mit SPI Handle verknüpfen
    __HAL_LINKDMA(_hspi, hdmatx, *dma_handle_tx);

    return true;
}

bool Dma::stm32_dma_init_rx(SPI_TypeDef *SPIx)
{
    // Prüfen, ob ein SPI-Handle gesetzt wurde
    if (_hspi == nullptr || _hspi->Instance == nullptr)
    {
        assert(false && "SPI handle not set. Call setSpiHandle() before dma_init_RX()");
        return false;
    }

    DMA_HandleTypeDef *dma_handle_rx = getRxHandle(SPIx);
    if (dma_handle_rx == nullptr) // HINZUGEFÜGT: Null-Check
    {
        assert(false && "Failed to get RX DMA handle");
        return false;
    }

    dma_handle_rx->Instance = _instance_rx;
    dma_handle_rx->Init.Request = requestToHal(_request_rx);
    dma_handle_rx->Init.Direction = DMA_PERIPH_TO_MEMORY;
    dma_handle_rx->Init.PeriphInc = periphIncToHal(_periphInc);
    dma_handle_rx->Init.MemInc = memIncToHal(_memInc);
    dma_handle_rx->Init.PeriphDataAlignment = periphDataAlignmentToHal(_periphDataAlignment);
    dma_handle_rx->Init.MemDataAlignment = memDataAlignmentToHal(_memDataAlignment);
    dma_handle_rx->Init.Mode = modeToHal(_mode);
    dma_handle_rx->Init.Priority = priorityToHal(_priority);

    // HAL DMA Initialisierung
    if (HAL_DMA_Init(dma_handle_rx) != HAL_OK)
    {
        return false;
    }

    // DMA mit SPI Handle verknüpfen
    __HAL_LINKDMA(_hspi, hdmarx, *dma_handle_rx);

    return true;
}

bool Dma::dma_interrupts(uint32_t priority)
{
    __HAL_RCC_DMA1_CLK_ENABLE();

    if (_hspi->Instance == SPI1)
    {
        HAL_NVIC_SetPriority(DMA1_Channel2_3_IRQn, priority, 0);
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

    return (HAL_SPI_GetError(_hspi) != HAL_SPI_ERROR_NONE);
}

#endif // STM32_PLATFORM