/**
 ******************************************************************************
 * @file           : main.cpp
 * @brief          : Einfacher MISO-Test für Oszilloskop-Beobachtung
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2025 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "main.hpp"
#include <cstring>

/**
 * @brief Test-Konfiguration
 */
#define BUFFER_SIZE 16 // Größe der Sende-/Empfangspuffer

// Betriebsmodus
// #define SPI_MODE_MASTER // SPI im Master-Modus
#define SPI_MODE_SLAVE // SPI im Slave-Modus

/**
 * @brief Testmuster für SPI-Übertragung
 * Einfaches 'O' (ASCII 0x4F) als MISO-Nachricht
 */
const uint8_t TEST_PATTERN[] = {
    'O', 'O', 'O', 'O', // Einfach nur 'O' als Testmuster
    'O', 'O', 'O', 'O', // Wiederholt für Zuverlässigkeit
    'O', 'O', 'O', 'O', // und leichtere Erkennung auf dem Oszilloskop
    'O', 'O', 'O', 'O'  // Das ASCII 'O' hat den Wert 0x4F
};

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{
  // Definiere Puffer für SPI-Übertragung
  uint8_t txBuffer[BUFFER_SIZE] = {0};
  uint8_t rxBuffer[BUFFER_SIZE] = {0};

  // Kopiere Testmuster in den Sendepuffer
  memcpy(txBuffer, TEST_PATTERN, sizeof(TEST_PATTERN));

  /* === System-Initialisierung === */

  // Hardware-Interface erstellen
  HardwareInterface *hw = HardwareFactory::create();

  // System initialisieren
  hw->init_sys();

  // Pins initialisieren
  hw->initAllPins();

  /* === SPI-Konfiguration === */

#ifdef SPI_MODE_MASTER
  // Konfiguriere NSS-Pin als Output für Master-Modus
  boardPins.spi1_nss.setPinMode(Mode::Output_Push_Pull);
  boardPins.spi1_nss.setPinAlternate(Alternate::None);
  boardPins.spi1_nss.gpio_init();
  boardPins.spi1_nss.writePin(true); // Default: CS auf High (deaktiviert)
#endif

  // SPI initialisieren
  peripherals.spi1.spi_init();

  // DMA für SPI1 konfigurieren
  static SpiDMA spi1_dma(
      *peripherals.spi1.get_handle(),
      peripherals.spi1.get_handle()->Instance,
      DMA_PRIORITY_HIGH,
      DMA_PRIORITY_HIGH,
      DMA_NORMAL,
      DMA_PDATAALIGN_BYTE);

  // DMA mit SPI verknüpfen und initialisieren
  peripherals.spi1_dma = &spi1_dma;
  peripherals.spi1.set_dma(peripherals.spi1_dma);
  peripherals.spi1_dma->init_dma();

  // SPI mit aktivierter DMA initialisieren
  peripherals.spi1.spi_init();

  /* === Hauptschleife für kontinuierlichen MISO-Test === */
  while (1)
  {
#ifdef SPI_MODE_MASTER
    // Starte SPI-Transaktion im Master-Modus
    boardPins.spi1_nss.writePin(false); // CS aktivieren (Low)
    hw->delay(1);

    // Sende Testmuster und empfange gleichzeitig MISO-Daten
    peripherals.spi1.transmitReceive(txBuffer, rxBuffer, BUFFER_SIZE, 1000);

    boardPins.spi1_nss.writePin(true); // CS deaktivieren (High)
#else
    // Slave-Modus: Bereite Antwortdaten vor und warte auf Master
    peripherals.spi1.transmitReceive(txBuffer, rxBuffer, BUFFER_SIZE, 5000);
#endif

    // Kurze Pause vor der nächsten Übertragung
    hw->delay(200);
  }
}
