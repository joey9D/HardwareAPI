/**
 ******************************************************************************
 * @file           : main.cpp
 * @brief          : SPI-Master und Slave-Beispiel zum Senden und Empfangen
 ******************************************************************************
 */

// ========== KONFIGURATION ==========
// Kommentieren Sie eine der beiden Zeilen aus, je nachdem ob Sie
// Master oder Slave konfigurieren möchten:

#define MASTER_CONFIG // <-- Aktivieren für MASTER, auskommentieren für SLAVE
// #undef MASTER_CONFIG // <-- Aktivieren für SLAVE, auskommentieren für MASTER
// ==================================

#include "main.hpp"
#include "project_config.hpp"
#include "hw_factory.hpp"
#include "hw_interface.hpp"
#include <string.h>

// Gemeinsame Definitionen für Master und Slave
#define BUFFER_SIZE 16
#define TRANSFER_WAIT 0
#define TRANSFER_COMPLETE 1
#define TRANSFER_ERROR 2

void master_code()
{
  // Hardware-Interface für systemweite Initialisierung holen
  HardwareInterface *hw = HardwareFactory::create();

  // System und Takt initialisieren
  hw->init_sys();
  hw->initAllPins();

  // SPI initialisieren
  peripherals.spi1.spi_init();

  linkSpiWithDma(peripherals.spi1, peripherals.dma1);

  peripherals.dma1.dma_init();

  // Puffer für Senden/Empfangen
  uint8_t txBuffer[BUFFER_SIZE] = {0};
  uint8_t rxBuffer[BUFFER_SIZE] = {0};

  while (true)
  {
    // Sendedaten vorbereiten (immer 'A' senden)
    txBuffer[0] = peripherals.txData;

    // SPI Transfer durchführen
    bool transferSuccess = peripherals.spi1.transmitReceive(txBuffer, rxBuffer, BUFFER_SIZE, 1000);

    // Kurze Pause zwischen den Transfers
    hw->delay(100);
  }
}

void slave_code()
{
  // Hardware-Interface für systemweite Initialisierung holen
  HardwareInterface *hw = HardwareFactory::create();

  // System und Takt initialisieren
  hw->init_sys();
  hw->initAllPins();

  // SPI initialisieren
  peripherals.spi1.spi_init();

  linkSpiWithDma(peripherals.spi1, peripherals.dma1);

  peripherals.dma1.dma_init();

  // Puffer für Senden/Empfangen
  uint8_t txBuffer[BUFFER_SIZE] = {0};
  uint8_t rxBuffer[BUFFER_SIZE] = {0};

  // Hauptschleife - Kontinuierlich senden und empfangen
  while (true)
  {
    // Sendedaten vorbereiten (immer 'O' senden)
    txBuffer[0] = peripherals.txData;

    // SPI Transfer durchführen (Slave wartet auf Master)
    bool transferSuccess = peripherals.spi1.transmitReceive(txBuffer, rxBuffer, BUFFER_SIZE, 1000);

    // Kurze Pause zwischen den Transfers
    hw->delay(100);
  }
}

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{
#ifdef MASTER_CONFIG
  master_code();
#else
  slave_code();
#endif
}
