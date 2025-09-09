# SPI-Kommunikation: Umfassender Leitfaden

## 1. SPI-Grundlagen

### 1.1. Was ist SPI?

Serial Peripheral Interface (SPI) ist ein synchrones, serielles Kommunikationsprotokoll, das für die Kommunikation zwischen Mikrocontrollern und Peripheriegeräten verwendet wird.

### 1.2. Signale im SPI-Bus

- **SCLK**: Serial Clock (vom Master generiert)
- **MOSI**: Master Out, Slave In (Datenleitung vom Master zum Slave)
- **MISO**: Master In, Slave Out (Datenleitung vom Slave zum Master)
- **NSS/CS**: Slave Select/Chip Select (aktiviert den spezifischen Slave)

### 1.3. SPI-Vorteile

- Full-Duplex-Kommunikation (gleichzeitiges Senden und Empfangen)
- Einfaches Hardware-Interface
- Höhere Geschwindigkeit als I²C oder UART
- Flexible Datenlängen

## 2. SPI-Kommunikationsmodi

### 2.1. Hauptmodi

| Modus | Beschreibung | STM32-Konstante |
|-------|-------------|-----------------|
| **Full-Duplex** | Gleichzeitiges Senden und Empfangen auf separaten MOSI/MISO-Leitungen | `SPI_DIRECTION_2LINES` |
| **Half-Duplex** | Eine Bidirektionale Leitung für abwechselndes Senden/Empfangen | `SPI_DIRECTION_1LINE` |
| **Simplex Tx-Only** | Nur-Senden-Modus | `SPI_DIRECTION_1LINE` mit `SPI_CR1_BIDIOE=1` |
| **Simplex Rx-Only** | Nur-Empfangen-Modus | `SPI_DIRECTION_2LINES_RXONLY` |

### 2.2. Clock-Polarität und -Phase

- **CPOL**: Clock Polarität (0=Idle Low, 1=Idle High)
- **CPHA**: Clock Phase (0=Erste Flanke, 1=Zweite Flanke)

| SPI-Modus | CPOL | CPHA | Beschreibung |
|-----------|------|------|-------------|
| Mode 0 | 0 | 0 | Clock idle low, Daten bei steigender Flanke |
| Mode 1 | 0 | 1 | Clock idle low, Daten bei fallender Flanke |
| Mode 2 | 1 | 0 | Clock idle high, Daten bei fallender Flanke |
| Mode 3 | 1 | 1 | Clock idle high, Daten bei steigender Flanke |

## 3. STM32 SPI-HAL: Kritische Aspekte

### 3.1. Wichtige HAL-Verhaltensweisen

- **Master receive() im Full-Duplex**: Wird automatisch zu `HAL_SPI_TransmitReceive()` - sendet und empfängt gleichzeitig!
- **Slave receive()**: Benötigt Clock vom Master, um Daten zu empfangen

```c
// HAL-Code, der erklärt, warum receive() für Master problematisch ist
if ((hspi->Init.Mode == SPI_MODE_MASTER) && (hspi->Init.Direction == SPI_DIRECTION_2LINES))
{
    hspi->State = HAL_SPI_STATE_BUSY_RX;
    /* Call transmit-receive function to send Dummy data on Tx line and generate clock on CLK line */
    return HAL_SPI_TransmitReceive(hspi, pData, pData, Size, Timeout);
}
```

### 3.2. Timeout-Mechanismen

HAL_MAX_DELAY: Wartet unbegrenzt (gefährlich!)
Sinnvolle Timeouts: 100-1000ms je nach Operation
Kurze Timeouts: Für einzelne Bytes (~100ms)
Längere Timeouts: Für längere Übertragungen (~1000ms)

## 4. Kritische Reihenfolgeregeln

### 4.1. Slave First, Master Second

```c
// RICHTIG
spi2.spi_init();       // Slave zuerst initialisieren
spi1.spi_init();       // Master danach initialisieren

// RICHTIG für Übertragung
spi2.receive(...);     // Slave zuerst in Empfang setzen
spi1.transmit(...);    // Master danach senden
```

### 4.2. NSS (Chip Select) Management

```c
// Gesamte Kommunikationssequenz unter einem NSS-Zyklus
boardPins.spi1_nss.writePin(false);   // NSS aktivieren (LOW)

// Alle Übertragungen durchführen
spi1.transmit(...);
// ...weitere Operationen...

boardPins.spi1_nss.writePin(true);    // NSS deaktivieren (HIGH)
```

## 5. Typische Probleme und Lösungen

### 5.1. Nullwerte oder 0xFF im Empfangspuffer

**Problem:** Die typischen 0xFF (255) Werte in Empfangspuffern zeigen, dass keine echten Daten empfangen wurden.

**Ursachen:**

1. Master-receive() verwendet denselben Buffer zum Senden und Empfangen
2. Fehlende Clock-Generation
3. Falsche Reihenfolge (Master sendet bevor Slave empfangsbereit ist)

**Lösung:**

- Bei Full-Duplex Master: transmitReceive() mit separaten Sende-/Empfangspuffern
- Korrekte Reihenfolge: Slave zuerst, Master danach

### 5.2. Full-Duplex Master-Receive Problem

```c
// FALSCH - Master im Full-Duplex-Modus
spi1.receive(rxBuffer, 5, timeout);  // Verwendet rxBuffer auch zum Senden!

// RICHTIG - Master im Full-Duplex-Modus
uint8_t dummyTxBuffer[5] = {0};  // Dummy-Daten zum Clock-Erzeugen
spi1.transmitReceive(dummyTxBuffer, rxBuffer, 5, timeout);
```

### 5.3. Slave-Kommunikation

Der Slave kann nur antworten, wenn:

1. Der Master den Clock generiert
2. NSS aktiv (LOW) ist
3. Der Slave bereits auf Empfang konfiguriert ist

## 6. Best Practices

### 6.1. Hardware-Setup

- Verbinden Sie alle 4 Leitungen zwischen Master und Slave (SCLK, MOSI, MISO, NSS)
- Gemeinsame GND-Verbindung zwischen Geräten ist KRITISCH
- Pull-Up-Widerstände an NSS-Pins reduzieren Störungen

### 6.2. Software-Implementierung

- Verwenden Sie immer passende Timeouts
- Prüfen Sie Return-Status aller SPI-Operationen
- Initialisieren Sie alle Buffer vor Verwendung
- Nutzen Sie für Master-Receive im Full-Duplex immer transmitReceive()

### 6.3. Timing-Tipps

- Ausreichende Delays zwischen SPI-Operationen (z.B. 10-100ms)
- Bei schnellen Operationen: Prüfen Sie die Baudrate und passen Sie den Prescaler an
- NSS sollte mindestens 1-2 Clock-Zyklen vor und nach dem Transfer aktiv bleiben

## 7. Debuggen von SPI-Problemen

### 7.1. Typische Debug-Punkte

- Nach SPI-Initialisierung: Prüfen der Konfigurationsregister
- Nach transmit(): Überprüfen des TXE-Flags
- Nach receive(): Überprüfen des Empfangspuffers und RXNE-Flags
- Status-Flags überprüfen: HAL_OK = 0, HAL_ERROR = 1, HAL_BUSY = 2, HAL_TIMEOUT = 3

### 7.2. Hardware-Debugging

- Logic Analyzer oder Oszilloskop für SCLK, MOSI, MISO und NSS
- Verifizieren Sie die NSS-Aktivierung (muss LOW sein während der Kommunikation)
- Überprüfen Sie die Clock-Generation (SPI Clock sollte nur während der Übertragung aktiv sein)

## 8. Fazit

SPI ist ein leistungsfähiges Protokoll für schnelle Kommunikation zwischen Mikrocontrollern und Peripheriegeräten. Die entscheidenden Punkte für erfolgreiche SPI-Kommunikation sind:

1. Verstehen der verschiedenen Kommunikationsmodi
2. Richtige Reihenfolge einhalten (Slave zuerst, Master danach)
3. Korrektes NSS-Management
4. Verwendung von transmitReceive() für Master im Full-Duplex-Modus
5. Angemessene Timeout-Zeiten
6. Korrekte physische Verbindungen mit gemeinsamer GND

Mit diesem Wissen können Sie robuste SPI-Kommunikation implementieren und typische Probleme vermeiden.
