#ifdef STM32_PLATFORM

#include "../drivers/stm32_hal_wrapper/common/stm32_hal_inc.hpp"
#include "spi_dma_stm32.hpp"
#include <cassert>

// Konstruktor
SpiDMA::SpiDMA(SPI_HandleTypeDef &hspi,
               SPI_TypeDef *spiInstance,
               uint32_t txPriority,
               uint32_t rxPriority,
               uint32_t dmaMode,
               uint32_t dataAlignment)
    : _hspi(hspi), _spiInstance(spiInstance),
      _txPriority(txPriority), _rxPriority(rxPriority),
      _dmaMode(dmaMode), _dataAlignment(dataAlignment),
      _txInitialized(false), _rxInitialized(false)
{
}

bool SpiDMA::init_dma_TX()
{
    if (_txInitialized)
    {
        return true; // Bereits initialisiert
    }

    DMA_Channel_TypeDef *txChannel = nullptr;
    DMA_Channel_TypeDef *rxChannel = nullptr;
    uint32_t txRequest = 0;
    uint32_t rxRequest = 0;

    // DMA-Channels und Requests ermitteln
    if (!getDMAChannels(&txChannel, &rxChannel, &txRequest, &rxRequest))
    {
        return false;
    }

    // TX DMA konfigurieren
    configureTxDMA(txChannel, txRequest);

    // HAL DMA Initialisierung
    if (HAL_DMA_Init(&_hdma_spi_tx) != HAL_OK)
    {
        return false;
    }

    // DMA mit SPI Handle verknüpfen
    __HAL_LINKDMA(&_hspi, hdmatx, _hdma_spi_tx);

    _txInitialized = true;
    return true;
}

// DMA RX Initialisierung
bool SpiDMA::init_dma_RX()
{
    if (_rxInitialized)
    {
        return true; // Bereits initialisiert
    }

    DMA_Channel_TypeDef *txChannel = nullptr;
    DMA_Channel_TypeDef *rxChannel = nullptr;
    uint32_t txRequest = 0;
    uint32_t rxRequest = 0;

    // DMA-Channels und Requests ermitteln
    if (!getDMAChannels(&txChannel, &rxChannel, &txRequest, &rxRequest))
    {
        return false;
    }

    // RX DMA konfigurieren
    configureRxDMA(rxChannel, rxRequest);

    // HAL DMA Initialisierung
    if (HAL_DMA_Init(&_hdma_spi_rx) != HAL_OK)
    {
        return false;
    }

    // DMA mit SPI Handle verknüpfen
    __HAL_LINKDMA(&_hspi, hdmarx, _hdma_spi_rx);

    _rxInitialized = true;
    return true;
}

// Beide DMA initialisieren
bool SpiDMA::init_dma()
{
    enableDMAResources();
    return init_dma_TX() && init_dma_RX();
}

// DMA TX De-Initialisierung
bool SpiDMA::deInit_dma_TX()
{
    if (!_txInitialized)
    {
        return true; // Bereits de-initialisiert
    }

    if (HAL_DMA_DeInit(&_hdma_spi_tx) != HAL_OK)
    {
        return false;
    }

    _txInitialized = false;
    return true;
}

// DMA RX De-Initialisierung
bool SpiDMA::deInit_dma_RX()
{
    if (!_rxInitialized)
    {
        return true; // Bereits de-initialisiert
    }

    if (HAL_DMA_DeInit(&_hdma_spi_rx) != HAL_OK)
    {
        return false;
    }

    _rxInitialized = false;
    return true;
}

// Beide DMA de-initialisieren
bool SpiDMA::deInit_dma()
{
    bool txOk = deInit_dma_TX();
    bool rxOk = deInit_dma_RX();
    return txOk && rxOk;
}

// Status-Abfragen
bool SpiDMA::isTxReady() const
{
    return _txInitialized && (_hdma_spi_tx.State == HAL_DMA_STATE_READY);
}

bool SpiDMA::isRxReady() const
{
    return _rxInitialized && (_hdma_spi_rx.State == HAL_DMA_STATE_READY);
}

bool SpiDMA::areBothReady() const
{
    return isTxReady() && isRxReady();
}

// DMA-Resources aktivieren (Clock Enable)
void SpiDMA::enableDMAResources()
{
    __HAL_RCC_DMA1_CLK_ENABLE();

// Falls DMA2 vorhanden und benötigt
#ifdef DMA2
    __HAL_RCC_DMA2_CLK_ENABLE();
#endif
}

// Private: DMA-Channels und Requests ermitteln
bool SpiDMA::getDMAChannels(DMA_Channel_TypeDef **txChannel,
                            DMA_Channel_TypeDef **rxChannel,
                            uint32_t *txRequest,
                            uint32_t *rxRequest)
{
    switch (reinterpret_cast<uintptr_t>(_spiInstance))
    {
    case SPI1_BASE:
        *txChannel = DMA1_Channel3;
        *rxChannel = DMA1_Channel2;
        *txRequest = DMA_REQUEST_SPI1_TX;
        *rxRequest = DMA_REQUEST_SPI1_RX;
        return true;

    case SPI2_BASE:
        *txChannel = DMA1_Channel5;
        *rxChannel = DMA1_Channel4;
        *txRequest = DMA_REQUEST_SPI2_TX;
        *rxRequest = DMA_REQUEST_SPI2_RX;
        return true;

#ifdef SPI3_BASE
    case SPI3_BASE:
        *txChannel = DMA2_Channel2;
        *rxChannel = DMA2_Channel1;
        *txRequest = DMA_REQUEST_SPI3_TX;
        *rxRequest = DMA_REQUEST_SPI3_RX;
        return true;
#endif

#ifdef SPI4_BASE
    case SPI4_BASE:
        *txChannel = DMA2_Channel5;
        *rxChannel = DMA2_Channel4;
        *txRequest = DMA_REQUEST_SPI4_TX;
        *rxRequest = DMA_REQUEST_SPI4_RX;
        return true;
#endif

    default:
        assert(false && "Unsupported SPI instance for DMA");
        return false;
    }
}

// Private: TX DMA konfigurieren
void SpiDMA::configureTxDMA(DMA_Channel_TypeDef *channel, uint32_t request)
{
    _hdma_spi_tx.Instance = channel;
    _hdma_spi_tx.Init.Request = request;
    _hdma_spi_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
    _hdma_spi_tx.Init.PeriphInc = DMA_PINC_DISABLE;
    _hdma_spi_tx.Init.MemInc = DMA_MINC_ENABLE;
    _hdma_spi_tx.Init.PeriphDataAlignment = _dataAlignment; // <-- Konfigurierbar
    _hdma_spi_tx.Init.MemDataAlignment = _dataAlignment;    // <-- Konfigurierbar
    _hdma_spi_tx.Init.Mode = _dmaMode;                      // <-- Konfigurierbar
    _hdma_spi_tx.Init.Priority = _txPriority;               // <-- Konfigurierbar
}

// Private: RX DMA konfigurieren
void SpiDMA::configureRxDMA(DMA_Channel_TypeDef *channel, uint32_t request)
{
    _hdma_spi_rx.Instance = channel;
    _hdma_spi_rx.Init.Request = request;
    _hdma_spi_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;     // Kann hardcodiert bleiben
    _hdma_spi_rx.Init.PeriphInc = DMA_PINC_DISABLE;         // Kann hardcodiert bleiben
    _hdma_spi_rx.Init.MemInc = DMA_MINC_ENABLE;             // Kann hardcodiert bleiben
    _hdma_spi_rx.Init.PeriphDataAlignment = _dataAlignment; // Sollte konfigurierbar sein
    _hdma_spi_rx.Init.MemDataAlignment = _dataAlignment;    // Sollte konfigurierbar sein
    _hdma_spi_rx.Init.Mode = _dmaMode;                      // Sollte konfigurierbar sein
    _hdma_spi_rx.Init.Priority = _rxPriority;               // Sollte konfigurierbar sein
}

#endif // STM32_PLATFORM