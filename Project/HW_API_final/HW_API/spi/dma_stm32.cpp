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

// Globale Instanzen-Tracking für Callbacks
Dma *g_spi1DmaInstance = nullptr;
#if defined(SPI2)
Dma *g_spi2DmaInstance = nullptr;
#endif

// Hilfsfunktion für Callbacks
Dma *FindDmaInstanceBySpiHandle(SPI_HandleTypeDef *hspi)
{
    if (hspi == nullptr || hspi->Instance == nullptr)
    {
        return nullptr;
    }

    if (hspi->Instance == SPI1)
    {
        return g_spi1DmaInstance;
    }
#if defined(SPI2)
    else if (hspi->Instance == SPI2)
    {
        return g_spi2DmaInstance;
    }
#endif
    return nullptr;
}

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

    // for callbacks
    if (hspi->Instance == SPI1)
    {
        /* code */
    }
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

template <SPI_TypeDef *SPIx>
bool Dma::dma_init_TX()
{
    if (_hspi == nullptr || _hspi->Instance == nullptr)
    {
        assert(false && "SPI handle not set. Call setSpiHandle() before dma_init_TX()");
        return false;
    }

    DMA_HandleTypeDef &dma_handle_Tx = SPIDmaHandlers<SPIx>::getTxHandle();

    dma_handle_Tx.Instance = DMA1_Channel3;
    dma_handle_Tx.Init.Request = requestToHal(_request_tx);
    dma_handle_Tx.Init.Direction = DMA_DIRECTION_MEMORY_TO_PERIPH;
    dma_handle_Tx.Init.PeriphInc = periphIncToHal(_periphInc);
    dma_handle_Tx.Init.MemInc = memIncToHal(_memInc);
    dma_handle_Tx.Init.PeriphDataAlignment = periphDataAlignmentToHal(_periphDataAlignment);
    dma_handle_Tx.Init.MemDataAlignment = memDataAlignmentToHal(_memDataAlignment);
    dma_handle_Tx.Init.Mode = modeToHal(_mode);
    dma_handle_Tx.Init.Priority = priorityToHal(_priority);

    // HAL DMA Initialisierung
    if (HAL_DMA_Init(&dma_handle_Tx) != HAL_OK)
    {
        return false;
    }

    // DMA mit SPI Handle verknüpfen
    __HAL_LINKDMA(_hspi, hdmatx, dma_handle_Tx);

    return true;
}

template <SPI_TypeDef *SPIx>
bool Dma::dma_init_RX()
{
    // Prüfen, ob ein SPI-Handle gesetzt wurde
    if (_hspi == nullptr || _hspi->Instance == nullptr)
    {
        assert(false && "SPI handle not set. Call setSpiHandle() before dma_init_RX()");
        return false;
    }

    DMA_HandleTypeDef &dma_handle_Rx = SPIDmaHandlers<SPIx>::getRxHandle();

    dma_handle_Rx.Instance = DMA1_Channel2;
    dma_handle_Rx.Init.Request = requestToHal(_request_rx);
    dma_handle_Rx.Init.Direction = DMA_DIRECTION_PERIPH_TO_MEMORY;
    dma_handle_Rx.Init.PeriphInc = periphIncToHal(_periphInc);
    dma_handle_Rx.Init.MemInc = memIncToHal(_memInc);
    dma_handle_Rx.Init.PeriphDataAlignment = periphDataAlignmentToHal(_periphDataAlignment);
    dma_handle_Rx.Init.MemDataAlignment = memDataAlignmentToHal(_memDataAlignment);
    dma_handle_Rx.Init.Mode = modeToHal(_mode);
    dma_handle_Rx.Init.Priority = priorityToHal(_priority);

    // HAL DMA Initialisierung
    if (HAL_DMA_Init(&dma_handle_Rx) != HAL_OK)
    {
        return false;
    }

    // DMA mit SPI Handle verknüpfen
    __HAL_LINKDMA(_hspi, hdmarx, dma_handle_Rx);

    return true;
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
        HAL_NVIC_SetPriority(DMA1_Channel2_3_IRQHandler, priority, 0);
        HAL_NVIC_EnableIRQ(DMA1_Channel2_3_IRQn);
    }
#ifdef SPI2
    else if (_hspi->Instance == SPI2)
    {
#ifdef DMA1_Channel4_5_IRQn
        HAL_NVIC_SetPriority(DMA1_Channel4_5_IRQHandler, priority, 0);
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

DmaTxState Dma::getTxState() const
{
    return _txState;
}

void Dma::setTxState(DmaTxState state)
{
    _txState = state;
}

bool Dma::isTxComplete() const
{
    return _txState == DmaTxState::COMPLETE;
}

bool Dma::isTxError() const
{
    return _txState == DmaTxState::ERROR;
}

// HAL-kompatible Callback-Funktionen
extern "C"
{
    void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
    {
        Dma *dma = FindDmaInstanceBySpiHandle(hspi);
        if (dma)
        {
            dma->setTransferState(DmaTxState::COMPLETE);
        }
    }

    void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi)
    {
        Dma *dma = FindDmaInstanceBySpiHandle(hspi);
        if (dma)
        {
            dma->setTransferState(DmaTxState::COMPLETE);
        }
    }

    void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi)
    {
        Dma *dma = FindDmaInstanceBySpiHandle(hspi);
        if (dma)
        {
            dma->setTransferState(DmaTxState::COMPLETE);
        }
    }

    void HAL_SPI_ErrorCallback(SPI_HandleTypeDef *hspi)
    {
        Dma *dma = FindDmaInstanceBySpiHandle(hspi);
        if (dma)
        {
            dma->setTransferState(DmaTxState::ERROR);
        }
    }
}
#endif // STM32_PLATFORM