/**
 ******************************************************************************
 * @file           : main.cpp
 * @brief          : SPI-Master und Slave-Beispiel zum Senden und Empfangen
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

/*
 * WICHTIGER HINWEIS:
 *
 * Für den Wechsel zwischen MASTER- und SLAVE-Konfiguration müssen Sie
 * das Symbol MASTER_CONFIG aktivieren oder deaktivieren, indem Sie die
 * entsprechende Zeile auskommentieren oder aktivieren.
 *
 * MASTER-Konfiguration: MASTER_CONFIG ist definiert
 * SLAVE-Konfiguration: MASTER_CONFIG ist nicht definiert
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
  HardwareInterface *hwInterface = HardwareFactory::create();

  // System und Takt initialisieren
  hwInterface->init_sys();
  hwInterface->initAllPins();

  // SPI initialisieren
  peripherals.spi1.spi_init();

  // Puffer für Senden/Empfangen
  uint8_t txBuffer[BUFFER_SIZE] = {0};
  uint8_t rxBuffer[BUFFER_SIZE] = {0};

  // Hauptschleife - Kontinuierlich senden und empfangen
  while (true)
  {
    // Sendedaten vorbereiten (immer 'A' senden)
    txBuffer[0] = peripherals.txData; // 'A' im Master-Modus

    // SPI Transfer durchführen
    bool transferSuccess = peripherals.spi1.transmitReceive(txBuffer, rxBuffer, BUFFER_SIZE, 1000);

    // Kurze Pause zwischen den Transfers
    hwInterface->delay(100);
  }
}

void slave_code()
{
  // Hardware-Interface für systemweite Initialisierung holen
  HardwareInterface *hwInterface = HardwareFactory::create();

  // System und Takt initialisieren
  hwInterface->init_sys();
  hwInterface->initAllPins();

  // SPI initialisieren
  peripherals.spi1.spi_init();

  // Puffer für Senden/Empfangen
  uint8_t txBuffer[BUFFER_SIZE] = {0};
  uint8_t rxBuffer[BUFFER_SIZE] = {0};

  // Hauptschleife - Kontinuierlich senden und empfangen
  while (true)
  {
    // Sendedaten vorbereiten (immer 'O' senden)
    txBuffer[0] = peripherals.txData; // 'O' im Slave-Modus

    // SPI Transfer durchführen (Slave wartet auf Master)
    bool transferSuccess = peripherals.spi1.transmitReceive(txBuffer, rxBuffer, BUFFER_SIZE, 1000);

    // Kurze Pause zwischen den Transfers
    hwInterface->delay(100);
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
