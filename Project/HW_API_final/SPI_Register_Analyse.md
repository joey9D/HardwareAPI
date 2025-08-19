# Analyse der SPI-Registerwerte und HAL-Konfiguration

In dieser Analyse untersuchen wir die SPI-Register der STM32G071RB-Mikrocontroller für ein Master-Slave-Setup auf einem einzelnen Chip. Die Analyse enthält sowohl Daten aus unserem Projekt als auch Vergleichswerte aus einem Beispielprojekt der STM32CubeIDE.

## Register-Übersicht

| Register | SPI1 (Master) | SPI2 (Slave) | Bedeutung |
|----------|---------------|--------------|-----------|
| CR1      | 860 (0x35C)   | 64 (0x40)    | Control Register 1 |
| CR2      | 5888          | 5888         | Control Register 2 |
| SR       | 2             | 2            | Status Register |
| DR       | 0             | 0            | Data Register |
| CRCPR    | 7             | 7            | CRC Polynomial Register |
| RXCRCR   | 0             | 0            | RX CRC Register |
| TXCRCR   | 0             | 0            | TX CRC Register |
| I2SCFGR  | 0             | 0            | I2S Configuration Register |
| I2SPR    | 2             | 0            | I2S Prescaler Register |

## SPI1 (Master) Register-Details

### CR1 = 860 (0x35C)

- **0x040 (Bit 6)**: **SPE** - SPI Enable ✓ (SPI aktiviert)
- **0x004 (Bit 2)**: **MSTR** - Master Mode ✓ (als Master konfiguriert)
- **0x100 (Bit 8)**: **SSI** - Internal Slave Select ✓ (aktiv)
- **0x200 (Bit 9)**: **SSM** - Software Slave Management ✓ (aktiv)
- **0x018 (Bits 3-5)**: **BR[2:0]** - Baudrate Prescaler 011 = /16

### CR2 = 5888

- **0x0700 (Bits 8-11)**: **DS[3:0]** - Datengröße 0111 = 8-Bit
- **0x1000 (Bit 12)**: **FRXTH** - FIFO Empfangsschwellenwert

### SR = 2

- **0x002 (Bit 1)**: **TXE** - Transmit buffer empty ✓ (bereit zum Senden)

## SPI2 (Slave) Register-Details

### CR1 = 64 (0x40)

- **0x040 (Bit 6)**: **SPE** - SPI Enable ✓ (SPI aktiviert)
- **MSTR-Bit nicht gesetzt** - korrekt für Slave-Modus

### CR2 = 5888 (Slave)

- Identische Konfiguration wie SPI1 (Datengröße und FIFO-Schwellenwert)

## HAL-Konfigurationsattribute

### SPI1 Master HAL-Handle

- **Mode = 260 (0x104)**:
  - Erwartet: `SPI_MODE_MASTER (0)`
  - Tatsächlich: `SPI_MODE_SLAVE (0x4) + SPI_CR1_SSI (0x100)` - **HAL-Inkonsistenz!**
- **Direction = 0**: `SPI_DIRECTION_2LINES` (Full Duplex)
- **DataSize = 1792**: 8-Bit Datenformat
- **CLKPolarity = 0**: `SPI_POLARITY_LOW` (CPOL=0)
- **CLKPhase = 0**: `SPI_PHASE_1EDGE` (CPHA=0)
- **NSS = 512 (0x200)**: `SPI_NSS_SOFT` - Software NSS-Kontrolle
- **BaudRatePrescaler = 24 (0x18)**: `SPI_BAUDRATEPRESCALER_16` - Takt/16
- **FirstBit = 0**: `SPI_FIRSTBIT_MSB` - MSB zuerst
- **TIMode = 0**: `SPI_TIMODE_DISABLE` - Motorola-Modus (nicht TI)
- **CRCCalculation = 0**: CRC deaktiviert
- **CRCPolynomial = 7**: Standard-CRC-Polynom
- **CRCLength = 1**: 8-Bit CRC
- **NSSMode = 0**: `SPI_NSS_PULSE_DISABLE` - Kein NSS-Puls

### SPI2 Slave HAL-Handle

- **Mode = 0**: `SPI_MODE_SLAVE` - **Korrekt für Slave**
- **Direction = 0**: `SPI_DIRECTION_2LINES` (Full Duplex)
- **DataSize = 1792**: 8-Bit Datenformat
- **CLKPolarity = 0**: `SPI_POLARITY_LOW` (CPOL=0)
- **CLKPhase = 0**: `SPI_PHASE_1EDGE` (CPHA=0)
- **NSS = 0**: `SPI_NSS_HARD_INPUT` - Hardware NSS-Kontrolle
- **BaudRatePrescaler = 0**: `SPI_BAUDRATEPRESCALER_2` (wird im Slave-Modus ignoriert)
- Weitere Parameter identisch mit Master-Konfiguration

## Wichtige Beobachtungen

1. **SPE-Bit korrekt gesetzt**: Beide SPIs haben das SPE-Bit in CR1 gesetzt (0x40) und sind aktiviert.

2. **Master/Slave-Konfiguration korrekt**:  
   - SPI1 hat MSTR-Bit gesetzt (ist Master)
   - SPI2 hat MSTR-Bit nicht gesetzt (ist Slave)

3. **HAL-Handle-Inkonsistenzen**:
   - SPI1 HAL-Handle zeigt Mode=260, was einer merkwürdigen Kombination entspricht
   - Die tatsächlichen Register sind korrekt konfiguriert, ungeachtet dieser HAL-Inkonsistenz

4. **Betriebsmodus**:
   - Full-Duplex-Konfiguration für bidirektionale Kommunikation
   - 8-Bit Datenübertragung
   - CPOL=0, CPHA=0 (Mode 0)

## Vergleich mit STM32CubeIDE Beispielprojekt

### Initialisierungsablauf im Beispielprojekt

1. **Anfängliche Register-Werte** (vor HAL_SPI_Init):

   ```plaintext
   CR1 = 0
   CR2 = 1792
   SR = 2
   DR = 0
   CRCPR = 7
   RXCRCR = 0
   TXCRCR = 0
   I2SCFGR = 0
   I2SPR = 2
   ```

2. **Nach CR1/CR2 Konfiguration** (Master):

   ```plaintext
   CR1 = 804   // Wichtig: SPE-Bit (0x40) noch nicht gesetzt
   CR2 = 5888  // Datengröße und FIFO-Schwellenwert gesetzt
   ```

3. **Nach CR1/CR2 Konfiguration** (Slave):

   ```plaintext
   CR1 = 512   // Wichtig: SPE-Bit (0x40) noch nicht gesetzt
   CR2 = 5888  // Datengröße und FIFO-Schwellenwert gesetzt
   ```

### Schlüsselcode in der HAL

Der kritische Teil der STM32-HAL, der die CR1/CR2-Register initialisiert:

```c
// CR1-Konfiguration (Mode, Direction, Clock, NSS, etc.)
WRITE_REG(hspi->Instance->CR1, ((hspi->Init.Mode & (SPI_CR1_MSTR | SPI_CR1_SSI)) |
                                (hspi->Init.Direction & (SPI_CR1_RXONLY | SPI_CR1_BIDIMODE)) |
                                (hspi->Init.CLKPolarity & SPI_CR1_CPOL) |
                                (hspi->Init.CLKPhase & SPI_CR1_CPHA) |
                                (hspi->Init.NSS & SPI_CR1_SSM) |
                                (hspi->Init.BaudRatePrescaler & SPI_CR1_BR_Msk) |
                                (hspi->Init.FirstBit & SPI_CR1_LSBFIRST) |
                                (hspi->Init.CRCCalculation & SPI_CR1_CRCEN)));

// CR2-Konfiguration (NSS-Management, TI-Mode, Datengröße, FIFO-Schwelle)
WRITE_REG(hspi->Instance->CR2, (((hspi->Init.NSS >> 16U) & SPI_CR2_SSOE) |
                                (hspi->Init.TIMode & SPI_CR2_FRF) |
                                (hspi->Init.NSSPMode & SPI_CR2_NSSP) |
                                (hspi->Init.DataSize & SPI_CR2_DS_Msk) |
                                (frxth & SPI_CR2_FRXTH)));
```

**Wichtige Beobachtung:** In keinem dieser Schritte wird das SPE-Bit (SPI_CR1_SPE) gesetzt, was die Notwendigkeit der expliziten Aktivierung bestätigt.

### Bewertung von Mode = 260

Die Überprüfung im Beispielprojekt bestätigt, dass Mode = 260 (0x104) kein Bug, sondern ein erwartetes Verhalten ist:

- `SPI_MODE_MASTER` wird tatsächlich als Kombination aus `SPI_CR1_MSTR | SPI_CR1_SSI` definiert
- Dies entspricht dem Wert 260 (0x104) und ist für den Master-Modus korrekt

## Schlussfolgerungen

1. Die Aktivierung des SPI (SPE-Bit) erfordert explizite Maßnahmen nach der HAL-Initialisierung.
2. Die tatsächlichen Hardware-Register sind korrekt konfiguriert, auch wenn die HAL-internen Handles zunächst verwirrend erscheinen.
3. Mode = 260 ist korrekt für den SPI-Master und entspricht der HAL-Definition von `SPI_MODE_MASTER`.
4. Für ein zuverlässiges SPI-Setup muss entweder:
   - Die HAL-Initialisierungsmethode erweitert werden, um SPE zu setzen
   - Oder explizit das SPE-Bit nach der Initialisierung gesetzt werden

Dies ist ein bekanntes und erwartetes Verhalten der STM32 HAL, das durch korrektes Setzen der Register-Bits behoben werden kann.
