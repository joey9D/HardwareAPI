#pragma once

#include "../drivers/stm32_hal_wrapper/common/stm32_hal_inc.hpp"
#include "spi_dma_interface.hpp"

#ifdef STM32_PLATFORM

class SpiDMA : public ISpiDMA
{
public:
    // Konstruktor mit allen DMA_InitTypeDef-Parametern
    SpiDMA(SPI_HandleTypeDef &hspi, SPI_TypeDef *spiInstance,
           uint32_t txPriority,
           uint32_t rxPriority,
           uint32_t dmaMode,
           uint32_t periphDataAlignment,
           uint32_t memDataAlignment,
           uint32_t periphInc = DMA_PINC_DISABLE,
           uint32_t memInc = DMA_MINC_ENABLE,
           uint32_t direction = DMA_PERIPH_TO_MEMORY);

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

    // Neue Interface-Methoden für Transfer-Status
    bool isTransferInProgress_TX() const override;
    bool isTransferInProgress_RX() const override;
    bool isAnyTransferInProgress() const override;

    // Neue Interface-Methoden für Transfer-Abbruch
    bool abortTransfer_TX() override;
    bool abortTransfer_RX() override;
    bool abortTransfer() override;

    DMA_HandleTypeDef *getTxHandle() override { return &_hdma_spi_tx; }
    DMA_HandleTypeDef *getRxHandle() override { return &_hdma_spi_rx; }

    // Neue Interface-Methode für Interrupt-Konfiguration
    void configureDMAInterrupts(uint32_t txPriority = 0, uint32_t rxPriority = 0) override;

private:
    // STM32-spezifische Member
    SPI_HandleTypeDef &_hspi;
    SPI_TypeDef *_spiInstance;
    DMA_HandleTypeDef _hdma_spi_tx;
    DMA_HandleTypeDef _hdma_spi_rx;

    // Konfigurierbare Member - vollständig nach DMA_InitTypeDef
    uint32_t _txPriority;
    uint32_t _rxPriority;
    uint32_t _dmaMode;             // DMA_Mode (Normal/Circular)
    uint32_t _periphDataAlignment; // Peripherie-Datengröße (Byte/HalfWord/Word)
    uint32_t _memDataAlignment;    // Speicher-Datengröße (Byte/HalfWord/Word)
    uint32_t _periphInc;           // Peripherie-Adress-Increment (Enable/Disable)
    uint32_t _memInc;              // Speicher-Adress-Increment (Enable/Disable)
    uint32_t _direction;           // Transferrichtung

    // Boolean Member am Ende
    bool _txInitialized;
    bool _rxInitialized;

    // Private Hilfsmethoden
    bool getDMAChannels(DMA_Channel_TypeDef **txChannel,
                        DMA_Channel_TypeDef **rxChannel,
                        uint32_t *txRequest,
                        uint32_t *rxRequest);
    void configureTxDMA(DMA_Channel_TypeDef *channel, uint32_t request);
    void configureRxDMA(DMA_Channel_TypeDef *channel, uint32_t request);
    IRQn_Type getIRQFromDMAChannel(DMA_Channel_TypeDef *channel);

    // Copy/Assignment verhindern
    SpiDMA(const SpiDMA &) = delete;
    SpiDMA &operator=(const SpiDMA &) = delete;
};

#endif // STM32_PLATFORM
