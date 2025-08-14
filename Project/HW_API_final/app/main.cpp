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
  // hw->initAllPins();

  // Initialize debounce state
  // bool lastButtonState = boardPins.button.isDebouncePinOn();

  // ===== SPI TEST CODE BEGINS =====
  // SPI GPIO Pins initialisieren
  boardPins.spi1_sck.gpio_init();
  boardPins.spi1_miso.gpio_init();
  boardPins.spi1_mosi.gpio_init();
  boardPins.spi1_nss.gpio_init();

  boardPins.spi2_sck.gpio_init();
  boardPins.spi2_miso.gpio_init();
  boardPins.spi2_mosi.gpio_init();
  boardPins.spi2_nss.gpio_init();

  // SPI1 als Master initialisieren
  Spi spi1(
      boardPins.spi1_sck,
      boardPins.spi1_miso,
      boardPins.spi1_mosi,
      boardPins.spi1_nss,
      SPI1,
      SpiMode::Master,
      SpiDirection::FullDuplex,
      SpiDataSize::Bits8,
      SpiClockPolarity::Low,
      SpiClockPhase::FirstEdge,
      SpiNSS::Soft,
      SpiBaudRatePrescaler::Prescaler16,
      SpiFirstBit::MSB,
      SpiTIMode::Disable,
      SpiCRCCalculation::Disable,
      SpiCRCPolynomial::Polynomial7,
      SpiCRCLength::Length8,
      SpiNSSPMode::Software,
      nullptr);

  // SPI2 als Slave initialisieren
  Spi spi2(
      boardPins.spi2_sck,
      boardPins.spi2_miso,
      boardPins.spi2_mosi,
      boardPins.spi2_nss,
      SPI2,
      SpiMode::Slave,
      SpiDirection::FullDuplex,
      SpiDataSize::Bits8,
      SpiClockPolarity::Low,
      SpiClockPhase::FirstEdge,
      SpiNSS::Hard_In,
      SpiBaudRatePrescaler::Prescaler16,
      SpiFirstBit::MSB,
      SpiTIMode::Disable,
      SpiCRCCalculation::Disable,
      SpiCRCPolynomial::Polynomial7,
      SpiCRCLength::Length8,
      SpiNSSPMode::Hardware,
      nullptr);

  // SPI-Peripherie initialisieren
  // WICHTIG: Slave ZUERST initialisieren, dann Master!
  spi2.spi_init(); // Slave zuerst
  spi1.spi_init(); // Master danach

  // Testdaten für Schritt-für-Schritt SPI-Kommunikation
  uint8_t masterTx1 = 'A'; // Master sendet 'A'
  uint8_t slaveTx2 = 'O';  // Slave sendet 'O'
  uint8_t masterRx2 = 0;   // Master empfängt hier
  uint8_t slaveRx1 = 0;    // Slave empfängt hier
  uint8_t dummy = 0x00;    // Dummy-Byte für einseitige Übertragungen

  // Status-Variablen für Debugging
  bool masterTx1Status = false;
  bool slaveRx1Status = false;
  bool slaveTx2Status = false;
  bool masterRx2Status = false;

  // String-Test Variablen
  const char *masterMessage = "Alpha";
  const char *slaveMessage = "Omega";
  uint8_t masterStringRx[10] = {0};
  uint8_t slaveStringRx[10] = {0};
  uint8_t stringDummy[10] = {0};

  bool masterStringTxStatus = false;
  bool slaveStringRxStatus = false;
  bool slaveStringTxStatus = false;
  bool masterStringRxStatus = false;

  // ===== SPI TEST CODE ENDS =====

  /* Infinite loop */
  while (1)
  {
    // boardPins.led.writePin(1); // Turn on LED
    // hw->delay(1000);           // Delay for 1 second
    // boardPins.led.writePin(0); // Turn off LED
    // hw->delay(1000);           // Delay for 1 second
    // Read current button state with debouncing
    // bool currentButtonState = boardPins.button.isDebouncePinOn();

    // Toggle LED on button press (rising edge detection)
    // if (!lastButtonState && currentButtonState)
    // {
    //   boardPins.led.togglePin();
    // }

    // Update button state
    // lastButtonState = currentButtonState;

    // ===== SCHRITT-FÜR-SCHRITT SPI TEST =====

    // ==== SCHRITT 1: Master sendet 'A', Slave empfängt ====
    boardPins.spi1_nss.writePin(false); // NSS aktivieren (aktiv low)

    // Master-Slave auf gleicher Hardware: Master MUSS Clock generieren
    // Daher: transmitReceive() verwenden, aber mit cleverer Implementierung
    uint8_t slaveRxTemp1 = 0xFF;   // Slave-Rx Buffer (für empfangene Daten)
    uint8_t slaveTxDummy1 = 0x00;  // Slave-Tx Dummy (unwichtig)
    uint8_t masterRxDummy1 = 0xFF; // Master-Rx Dummy (unwichtig)

    // SEQUENZ: Slave-Init + Master-Tx (Master generiert Clock)
    slaveRx1Status = spi2.transmitReceive(&slaveTxDummy1, &slaveRxTemp1, 1); // Slave bereit
    hw->delay(1);                                                            // Kurze Pause für Sync
    masterTx1Status = spi1.transmitReceive(&masterTx1, &masterRxDummy1, 1);  // Master sendet + Clock

    slaveRx1 = slaveRxTemp1; // Ergebnis kopieren

    boardPins.spi1_nss.writePin(true); // NSS deaktivieren
    hw->delay(100);

    // ==== SCHRITT 2: Slave sendet 'O', Master empfängt ====
    boardPins.spi1_nss.writePin(false); // NSS aktivieren (aktiv low)

    uint8_t slaveTxTemp2 = slaveTx2; // Slave-Tx Buffer (zu sendende Daten)
    uint8_t slaveRxDummy2 = 0xFF;    // Slave-Rx Dummy (unwichtig)
    uint8_t masterTxDummy2 = 0x00;   // Master-Tx Dummy (unwichtig, aber Clock!)
    uint8_t masterRxTemp2 = 0xFF;    // Master-Rx Buffer (für empfangene Daten)

    // SEQUENZ: Slave-Tx + Master-Rx (Master generiert Clock)
    slaveTx2Status = spi2.transmitReceive(&slaveTxTemp2, &slaveRxDummy2, 1);    // Slave sendet
    hw->delay(1);                                                               // Kurze Pause für Sync
    masterRx2Status = spi1.transmitReceive(&masterTxDummy2, &masterRxTemp2, 1); // Master empfängt + Clock

    masterRx2 = masterRxTemp2; // Ergebnis kopieren

    boardPins.spi1_nss.writePin(true); // NSS deaktivieren
    hw->delay(1000);

    // ==== SCHRITT 3: Master sendet "Alpha", Slave empfängt ====
    boardPins.spi1_nss.writePin(false); // NSS aktivieren (aktiv low)

    // String-Übertragung mit temporären Buffern
    uint8_t slaveRxTempStr[6] = {0}; // +1 für Null-Terminator
    uint8_t slaveTxDummyStr[5] = {0x00, 0x00, 0x00, 0x00, 0x00};
    uint8_t masterRxDummyStr[5] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

    // SEQUENZ: Slave-Init + Master-Tx String
    slaveStringRxStatus = spi2.transmitReceive(slaveTxDummyStr, slaveRxTempStr, 5);             // Slave bereit für "Alpha"
    hw->delay(1);                                                                               // Kurze Pause für Sync
    masterStringTxStatus = spi1.transmitReceive((uint8_t *)masterMessage, masterRxDummyStr, 5); // Master sendet "Alpha" + Clock

    // Ergebnis kopieren und Null-Terminator hinzufügen
    memcpy(slaveStringRx, slaveRxTempStr, 5);
    slaveStringRx[5] = '\0';

    boardPins.spi1_nss.writePin(true); // NSS deaktivieren
    hw->delay(100);

    // ==== SCHRITT 4: Slave sendet "Omega", Master empfängt ====
    boardPins.spi1_nss.writePin(false); // NSS aktivieren (aktiv low)

    // String-Übertragung mit temporären Buffern
    uint8_t masterRxTempStr[6] = {0}; // +1 für Null-Terminator
    uint8_t slaveTxTempStr[5];
    memcpy(slaveTxTempStr, slaveMessage, 5); // "Omega" kopieren
    uint8_t slaveRxDummyStr[5] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
    uint8_t masterTxDummyStr[5] = {0x00, 0x00, 0x00, 0x00, 0x00};

    // SEQUENZ: Slave-Tx + Master-Rx String
    slaveStringTxStatus = spi2.transmitReceive(slaveTxTempStr, slaveRxDummyStr, 5);    // Slave sendet "Omega"
    hw->delay(1);                                                                      // Kurze Pause für Sync
    masterStringRxStatus = spi1.transmitReceive(masterTxDummyStr, masterRxTempStr, 5); // Master empfängt "Omega" + Clock

    // Ergebnis kopieren und Null-Terminator hinzufügen
    memcpy(masterStringRx, masterRxTempStr, 5);
    masterStringRx[5] = '\0';

    boardPins.spi1_nss.writePin(true); // NSS deaktivieren

    // Debug-Pause: Hier sollte masterStringRx == "Omega" sein
    hw->delay(1000);

    // ===== SPI TEST CODE ENDS =====
  }
}
