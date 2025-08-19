#ifdef STM32_PLATFORM

#include "../drivers/stm32_hal_wrapper/common/stm32_hal_inc.hpp"
#include "spi_dma_stm32.hpp"
#include <cassert>

// Globale DMA Handles für Interrupt-System (extern Deklarationen in stm32g0xx_it.h)
DMA_HandleTypeDef hdma_spi1_tx;
DMA_HandleTypeDef hdma_spi1_rx; 
DMA_HandleTypeDef hdma_spi2_tx;
DMA_HandleTypeDef hdma_spi2_rx;

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

// Transfer-Status-Abfragen (neu implementiert)
bool SpiDMA::isTransferInProgress_TX() const
{
    return _txInitialized && (_hdma_spi_tx.State == HAL_DMA_STATE_BUSY);
}

bool SpiDMA::isTransferInProgress_RX() const
{
    return _rxInitialized && (_hdma_spi_rx.State == HAL_DMA_STATE_BUSY);
}

bool SpiDMA::isAnyTransferInProgress() const
{
    return isTransferInProgress_TX() || isTransferInProgress_RX();
}

// Transfer-Abbruch-Funktionen (neu implementiert)
bool SpiDMA::abortTransfer_TX()
{
    if (!_txInitialized || !isTransferInProgress_TX())
    {
        return true; // Nichts abzubrechen
    }
    
    HAL_StatusTypeDef status = HAL_DMA_Abort(&_hdma_spi_tx);
    return (status == HAL_OK);
}

bool SpiDMA::abortTransfer_RX()
{
    if (!_rxInitialized || !isTransferInProgress_RX())
    {
        return true; // Nichts abzubrechen
    }
    
    HAL_StatusTypeDef status = HAL_DMA_Abort(&_hdma_spi_rx);
    return (status == HAL_OK);
}

bool SpiDMA::abortTransfer()
{
    // Beide Transfers abbrechen, falls aktiv
    bool txOk = abortTransfer_TX();
    bool rxOk = abortTransfer_RX();
    return txOk && rxOk;
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

// Neue Methode: Interrupt-Konfiguration
void SpiDMA::configureDMAInterrupts(uint32_t txPriority, uint32_t rxPriority)
{
    DMA_Channel_TypeDef *txChannel = nullptr;
    DMA_Channel_TypeDef *rxChannel = nullptr;
    uint32_t txRequest = 0;
    uint32_t rxRequest = 0;

    // DMA-Channels und Requests ermitteln
    if (!getDMAChannels(&txChannel, &rxChannel, &txRequest, &rxRequest))
    {
        return;
    }
    
    // IRQn bestimmen basierend auf dem DMA-Channel
    IRQn_Type txIRQn = getIRQFromDMAChannel(txChannel);
    IRQn_Type rxIRQn = getIRQFromDMAChannel(rxChannel);
    
    // Interrupts konfigurieren
    if (txIRQn != static_cast<IRQn_Type>(0))
    {
        HAL_NVIC_SetPriority(txIRQn, txPriority, 0);
        HAL_NVIC_EnableIRQ(txIRQn);
    }
    
    if (rxIRQn != static_cast<IRQn_Type>(0))
    {
        HAL_NVIC_SetPriority(rxIRQn, rxPriority, 0);
        HAL_NVIC_EnableIRQ(rxIRQn);
    }
}

// Private: IRQn aus DMA-Channel ermitteln
IRQn_Type SpiDMA::getIRQFromDMAChannel(DMA_Channel_TypeDef *channel)
{
    // STM32C0/G0-spezifisches Mapping: DMA-Channels → IRQn
    
    // DMA1 Channel 1
    if (channel == DMA1_Channel1)
    {
        return DMA1_Channel1_IRQn;
    }
    
    // DMA1 Channel 2 & 3 teilen sich einen IRQ in STM32C0/G0
    if (channel == DMA1_Channel2 || channel == DMA1_Channel3)
    {
        return DMA1_Channel2_3_IRQn;
    }
    
    // Für weitere Channels je nach MCU-Familie
#ifdef DMA1_Channel4_5_6_7_IRQn
    if (channel == DMA1_Channel4 || channel == DMA1_Channel5 || 
        channel == DMA1_Channel6 || channel == DMA1_Channel7)
    {
        return DMA1_Channel4_5_6_7_IRQn;
    }
#endif

#ifdef DMA1_Channel4_5_IRQn
    if (channel == DMA1_Channel4 || channel == DMA1_Channel5)
    {
        return DMA1_Channel4_5_IRQn;
    }
#endif

#ifdef DMA2
    // DMA2 Channel 1
    if (channel == DMA2_Channel1)
    {
        return DMA2_Channel1_IRQn;
    }
    
    // Je nach MCU-Familie weitere Mappings
#endif

    return static_cast<IRQn_Type>(0); // Kein gültiger IRQn gefunden
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
        // Korrekte STM32G071RB Channel-Zuordnung
        *txChannel = DMA1_Channel1;
        *rxChannel = DMA1_Channel2;
        *txRequest = DMA_REQUEST_SPI1_TX;
        *rxRequest = DMA_REQUEST_SPI1_RX;
        return true;

    case SPI2_BASE:
        // Korrekte STM32G071RB Channel-Zuordnung
        *txChannel = DMA1_Channel3;
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

// HAL-kompatible Callback-Funktionen
extern "C" {
    
/**
 * @brief SPI TX DMA Transfer Complete Callback
 * Wird von der HAL nach erfolgreichem DMA TX Transfer aufgerufen
 */
void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
{
    // Optional: Custom handling nach TX completion
    // Aktuell keine zusätzliche Logik erforderlich
}

/**
 * @brief SPI RX DMA Transfer Complete Callback  
 * Wird von der HAL nach erfolgreichem DMA RX Transfer aufgerufen
 */
void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi)
{
    // Optional: Custom handling nach RX completion
    // Aktuell keine zusätzliche Logik erforderlich
}

/**
 * @brief SPI TX/RX DMA Transfer Complete Callback
 * Wird von der HAL nach erfolgreichem DMA TX/RX Transfer aufgerufen
 */
void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi)
{
    // Optional: Custom handling nach TX/RX completion
    // Aktuell keine zusätzliche Logik erforderlich
}

/**
 * @brief SPI DMA Transfer Error Callback
 * Wird von der HAL bei DMA-Fehlern aufgerufen
 */
void HAL_SPI_ErrorCallback(SPI_HandleTypeDef *hspi)
{
    // Optional: Error handling
    // Aktuell keine zusätzliche Logik erforderlich
}

} // extern "C"

#endif // STM32_PLATFORM