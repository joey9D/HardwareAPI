# SPI DMA Implementation

Dieses Dokument beschreibt die Implementierung und Verwendung der DMA-Funktionen in der SPI-Klasse.

## Übersicht

Die SPI-Klasse bietet DMA-Unterstützung für schnellere und effizientere Datenübertragung. DMA (Direct Memory Access) ermöglicht es dem SPI-Peripheriegerät, Daten direkt aus dem Speicher zu lesen oder in den Speicher zu schreiben, ohne dass die CPU beteiligt ist.

## Funktionen

Die SPI-Klasse bietet folgende DMA-Funktionen:

### Blockierende DMA-Transfers

Diese Funktionen blockieren den aufrufenden Thread, bis der DMA-Transfer abgeschlossen ist oder ein Timeout erreicht wird:

```cpp
bool transmit_DMA(const uint8_t *data, uint16_t length, uint32_t timeout);
bool receive_DMA(uint8_t *data, uint16_t length, uint32_t timeout);
bool transmitReceive_DMA(const uint8_t *txData, uint8_t *rxData, uint16_t length, uint32_t timeout);
```

### Nicht-blockierende DMA-Transfers

Für nicht-blockierende Transfers verwenden Sie die gleichen Funktionen, aber setzen den `timeout`-Parameter auf 0:

```cpp
// Nicht-blockierender DMA-Transfer
spi.transmit_DMA(data, length, 0);
```

### Status-Prüfung für nicht-blockierende Transfers

Nach einem nicht-blockierenden Transfer können Sie den Status mit folgenden Funktionen überprüfen:

```cpp
bool isDmaTransmitComplete();        // Prüft, ob der Tx-Transfer abgeschlossen ist
bool isDmaReceiveComplete();         // Prüft, ob der Rx-Transfer abgeschlossen ist
bool isDmaTransmitReceiveComplete(); // Prüft, ob sowohl Tx als auch Rx abgeschlossen sind
bool isDmaTransferInProgress();      // Prüft, ob ein Transfer noch läuft
bool abortDmaTransfer();             // Bricht einen laufenden DMA-Transfer ab
```

## Verwendungsbeispiele

### Blockierender DMA-Transfer

```cpp
uint8_t txData[] = {0x01, 0x02, 0x03};
uint8_t rxData[3];

// Blockierender Transfer mit 1000ms Timeout
if (spi.transmitReceive_DMA(txData, rxData, 3, 1000)) {
    // Transfer erfolgreich
} else {
    // Transfer fehlgeschlagen oder Timeout
}
```

### Nicht-blockierender DMA-Transfer

```cpp
uint8_t txData[] = {0x01, 0x02, 0x03};
uint8_t rxData[3];

// Nicht-blockierender Transfer (timeout = 0)
if (spi.transmitReceive_DMA(txData, rxData, 3, 0)) {
    // Transfer gestartet
    
    // Andere Operationen ausführen
    
    // Status prüfen
    while (!spi.isDmaTransmitReceiveComplete()) {
        // Warten oder andere Aufgaben ausführen
        
        // Optional: Timeout-Logik implementieren
        if (/* Timeout-Bedingung */) {
            spi.abortDmaTransfer();
            // Fehlerbehandlung
            break;
        }
    }
    
    // Transfer abgeschlossen
} else {
    // Transfer konnte nicht gestartet werden
}
```

### DMA-Initialisierung

```cpp
// GPIO-Pins für SPI
Gpio sckPin(GPIOA, GPIO_PIN_5, GpioMode::ALTERNATE_FUNCTION, GpioPull::NO_PULL, GpioSpeed::VERY_HIGH_SPEED, GpioAlternate::SPI1);
Gpio misoPin(GPIOA, GPIO_PIN_6, GpioMode::ALTERNATE_FUNCTION, GpioPull::NO_PULL, GpioSpeed::VERY_HIGH_SPEED, GpioAlternate::SPI1);
Gpio mosiPin(GPIOA, GPIO_PIN_7, GpioMode::ALTERNATE_FUNCTION, GpioPull::NO_PULL, GpioSpeed::VERY_HIGH_SPEED, GpioAlternate::SPI1);
Gpio csPin(GPIOA, GPIO_PIN_4, GpioMode::OUTPUT_PUSH_PULL, GpioPull::PULL_UP, GpioSpeed::VERY_HIGH_SPEED);

// SPI-DMA-Instanz erstellen
SpiDMA spiDma(
    DmaInstance::DMA1,        // DMA-Instance
    DmaStream::STREAM0,       // TX Stream
    DmaStream::STREAM1,       // RX Stream
    DmaChannel::CHANNEL3,     // TX Channel
    DmaChannel::CHANNEL3,     // RX Channel
    DmaDirection::MEMORY_TO_PERIPH,  // TX Direction
    DmaDirection::PERIPH_TO_MEMORY,  // RX Direction
    DmaMode::NORMAL,          // TX Mode
    DmaMode::NORMAL,          // RX Mode
    DmaPriority::HIGH,        // TX Priority
    DmaPriority::HIGH,        // RX Priority
    DmaIncrementMode::ENABLE, // TX Memory Increment
    DmaIncrementMode::ENABLE, // RX Memory Increment
    DmaIncrementMode::DISABLE,// TX Peripheral Increment
    DmaIncrementMode::DISABLE,// RX Peripheral Increment
    DmaDataAlignment::BYTE,   // TX Memory Data Size
    DmaDataAlignment::BYTE,   // RX Memory Data Size
    DmaDataAlignment::BYTE,   // TX Peripheral Data Size
    DmaDataAlignment::BYTE    // RX Peripheral Data Size
);

// SPI-Instanz erstellen und DMA zuweisen
Spi spi(
    sckPin, misoPin, mosiPin, csPin,
    SPI1,
    SpiMode::MASTER,
    SpiDirection::FULL_DUPLEX,
    SpiDataSize::DATASIZE_8BIT,
    SpiClockPolarity::LOW,
    SpiClockPhase::PHASE_1EDGE,
    SpiNSS::SOFT,
    SpiBaudRatePrescaler::PRESCALER_8,
    SpiFirstBit::MSB,
    SpiTIMode::DISABLE,
    SpiCRCCalculation::DISABLE,
    0,
    SpiCRCLength::CRC_8BIT,
    SpiNSSPMode::DISABLE,
    &spiDma
);

// SPI initialisieren
if (spi.spi_init()) {
    // SPI erfolgreich initialisiert
} else {
    // Fehler bei der Initialisierung
}
```
