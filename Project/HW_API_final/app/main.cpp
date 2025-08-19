/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.cpp
 * @brief          : Main program body for HW_API
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
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.hpp"
#include <cstring>

// Konfiguration: Aktivieren Sie entweder MASTER_MODE, SLAVE_MODE oder beide
#define MASTER_MODE
#define SLAVE_MODE

#define BUFFER_SIZE 16

// Transfer Status-Definitionen
#define TRANSFER_WAIT 0
#define TRANSFER_COMPLETE 1
#define TRANSFER_ERROR 2

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{
  // Create hardware interface using factory pattern
  HardwareInterface *hw = HardwareFactory::create();

  // Initialize system (HAL, clocks, etc.)
  hw->init_sys();

  // Initialize all pins defined in project_config.hpp
  hw->initAllPins();

  // Initialize User Button for manual trigger
  // boardPins.button.gpio_init();

  // Initialize debounce state
  // bool lastButtonState = false;
  // bool buttonPressed = false;

  // ===== SPI TEST CODE BEGINS =====

  // SPI initialisieren - Master und Slave für echte Kommunikation
  peripherals.spi1.spi_init(); // Master
  peripherals.spi2.spi_init(); // Slave

  // ===== SPI TIMEOUT KONFIGURATION =====
  const uint32_t SPI_DMA_TIMEOUT_MS = 1000; // 1 Sekunde für DMA

  // Test-/Response-Daten für bidirektionale SPI-Kommunikation mit DMA
  uint8_t aTxBuffer[BUFFER_SIZE] = 'A'; // Sendedaten
  uint8_t aRxBuffer[BUFFER_SIZE] = {0}; // Empfangsdaten

  // Blink-LED während auf Taste gedrückt wird
  while (boardPins.button.readPin() == true)
  {
    boardPins.led.togglePin();
    hw->delay(100);
  }
  boardPins.led.writePin(false); // LED ausschalten

  // Status-Variablen für Transfer
  uint32_t wTransferState = TRANSFER_WAIT;

  // Start SPI FullDuplex DMA transfer
  wTransferState = TRANSFER_WAIT;

  // NSS aktivieren (LOW) für SPI-Transfer
  boardPins.spi1_nss.writePin(false);

  // Starte DMA-Transfer (nicht-blockierend mit timeout=0)
  if (!peripherals.spi1.transmitReceive_DMA(aTxBuffer, aRxBuffer, BUFFER_SIZE, 0))
  {
    wTransferState = TRANSFER_ERROR;
  }

  /* Infinite loop */
  while (1)
  {
    // Prüfe den Status des DMA-Transfers
    if (peripherals.spi1.isDmaTransmitReceiveComplete())
    {
      // Transfer abgeschlossen
      wTransferState = TRANSFER_COMPLETE;

      // NSS deaktivieren (HIGH) nach Transfer
      boardPins.spi1_nss.writePin(true);
    }

    // Verarbeite Ergebnisse basierend auf Transfer-Status
    if (wTransferState == TRANSFER_COMPLETE)
    {
      // Vergleiche Sende- und Empfangspuffer
      if (memcmp(aTxBuffer, aRxBuffer, BUFFER_SIZE) == 0)
      {
        // Erfolg: LED einschalten
        boardPins.led.writePin(true);
      }
      else
      {
        // Fehler: LED langsam blinken
        boardPins.led.togglePin();
        hw->delay(500);
      }
    }
    else if (wTransferState == TRANSFER_ERROR)
    {
      // Fehler: LED langsam blinken
      boardPins.led.togglePin();
      hw->delay(500);
    }
    // Sonst: Warten, LED aus
  }
}
