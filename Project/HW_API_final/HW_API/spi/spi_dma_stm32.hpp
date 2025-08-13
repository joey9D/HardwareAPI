#pragma once

#include "spi_dma_interface.hpp"

#ifdef STM32_PLATFORM

class SpiDMA : public ISpiDMA // <-- Ohne _STM32!
{
public:
    // Konstruktor mit konfigurierbaren DMA-Parametern
    SpiDMA(SPI_HandleTypeDef &hspi, SPI_TypeDef *spiInstance,
           uint32_t txPriority = DMA_PRIORITY_LOW,
           uint32_t rxPriority = DMA_PRIORITY_HIGH,
           uint32_t dmaMode = DMA_NORMAL,
           uint32_t dataAlignment = DMA_PDATAALIGN_BYTE);

    // Interface-Implementierung
    bool init_dma_TX() override;
    bool init_dma_RX() override;
    bool init_dma() override;

    bool deInit_dma_TX() override;
    bool deInit_dma_RX() override;
    bool deInit_dma() override;

    bool isTxReady() const override;
    bool isRxReady() const override;
    bool areBothReady() const override;

    DMA_HandleTypeDef *getTxHandle() override { return &_hdma_spi_tx; }
    DMA_HandleTypeDef *getRxHandle() override { return &_hdma_spi_rx; }

    void enableDMAResources() override;

private:
    // STM32-spezifische Member
    SPI_HandleTypeDef &_hspi;
    SPI_TypeDef *_spiInstance;
    DMA_HandleTypeDef _hdma_spi_tx;
    DMA_HandleTypeDef _hdma_spi_rx;
    bool _txInitialized;
    bool _rxInitialized;

    // Konfigurierbare Member
    uint32_t _txPriority;
    uint32_t _rxPriority;
    uint32_t _dmaMode;
    uint32_t _dataAlignment;

    // Private Hilfsmethoden
    bool getDMAChannels(DMA_Channel_TypeDef **txChannel,
                        DMA_Channel_TypeDef **rxChannel,
                        uint32_t *txRequest,
                        uint32_t *rxRequest);
    void configureTxDMA(DMA_Channel_TypeDef *channel, uint32_t request);
    void configureRxDMA(DMA_Channel_TypeDef *channel, uint32_t request);

    // Copy/Assignment verhindern
    SpiDMA(const SpiDMA &) = delete;
    SpiDMA &operator=(const SpiDMA &) = delete;
};

#endif // STM32_PLATFORM
