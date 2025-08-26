/**
 ******************************************************************************
 * @file           : main.cpp
 * @brief          : SPI-Master und Slave-Beispiel zum Senden und Empfangen
 ******************************************************************************
 */

// ========== KONFIGURATION ==========
#define GPIO_CODE
// #define MASTER_CONFIG
// #define SLAVE_CONFIG
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

#ifdef GPIO_CODE
void gpio_code()
{
  HardwareInterface *hw = HardwareFactory::create();

  hw->init_sys();
  // hw->initAllPins();

  boardPins.led.gpio_init();
  boardPins.button.gpio_init();

  bool lastButtonState = boardPins.button.isDebouncePinOn();

  /* Infinite loop */
  while (1)
  {
    //	  hw->togglePin();
    //	  hw->delay(500);
    bool currentButtonState = boardPins.button.isDebouncePinOn();

    if (!lastButtonState && currentButtonState)
    {
      boardPins.led.togglePin();
    }
    lastButtonState = currentButtonState;
  }
}
#endif

#ifdef MASTER_CONFIG
void master_code()
{
  // Hardware-Interface für systemweite Initialisierung holen
  HardwareInterface *hw = HardwareFactory::create();

  // System und Takt initialisieren
  hw->init_sys();
  hw->initAllPins();

  // SPI initialisieren
  peripherals.spi_master.spi_init();

  linkSpiWithDma(peripherals.spi_master, peripherals.dma_master);

  peripherals.dma_master.dma_init();

  // Puffer für Senden/Empfangen
  uint8_t txBuffer[BUFFER_SIZE] = {0};
  uint8_t rxBuffer[BUFFER_SIZE] = {0};

  while (true)
  {
    // Sendedaten vorbereiten (immer 'A' senden)
    txBuffer[0] = peripherals.txData;

    // SPI Transfer durchführen
    bool transferSuccess = peripherals.spi_master.transmitReceive(txBuffer, rxBuffer, BUFFER_SIZE, 1000);

    // Kurze Pause zwischen den Transfers
    hw->delay(100);
  }
}
#endif

#ifdef SLAVE_CONFIG
void slave_code()
{
  // Hardware-Interface für systemweite Initialisierung holen
  HardwareInterface *hw = HardwareFactory::create();

  // System und Takt initialisieren
  hw->init_sys();
  hw->initAllPins();

  // SPI initialisieren
  peripherals.spi_slave.spi_init();

  linkSpiWithDma(peripherals.spi_slave, peripherals.dma_slave);

  peripherals.dma_slave.dma_init();

  // Puffer für Senden/Empfangen
  uint8_t txBuffer[BUFFER_SIZE] = {0};
  uint8_t rxBuffer[BUFFER_SIZE] = {0};

  // Hauptschleife - Kontinuierlich senden und empfangen
  while (true)
  {
    // Sendedaten vorbereiten (immer 'O' senden)
    txBuffer[0] = peripherals.txData;

    // SPI Transfer durchführen (Slave wartet auf Master)
    bool transferSuccess = peripherals.spi_slave.transmitReceive(txBuffer, rxBuffer, BUFFER_SIZE, 1000);

    // Kurze Pause zwischen den Transfers
    hw->delay(100);
  }
}
#endif
/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{

#ifdef GPIO_CODE
  gpio_code();
#elif defined(MASTER_CONFIG)
  master_code();
#elif defined(SLAVE_CONFIG)
  slave_code();
#endif
}
