/*
 * project_config.h
 *
 *  Created on: Jul 22, 2025
 *      Author: jan.kristel
 */

#pragma once

#include <array>

#include "../gpio/gpio_interface.hpp"
#include "../spi/spi_interface.hpp"
#include "../spi/dma_interface.hpp"

// Platform-spezifische Includes
#ifdef STM32_PLATFORM
#include "../gpio/gpio_stm32.hpp"
#include "../spi/spi_stm32.hpp"
#include "../spi/dma_stm32.hpp"

#endif

/**
 * struct PinConfig_t
{
	uint16_t pin;
	Port port;
	Mode mode;
	Pull pull;
	Speed speed;
	Alternate alternate;
	bool invertedPin;
	uint32_t debounceTime;
	uint8_t debounceState;
	ExtiTrigger extiTrigger;
	Timer debounceTimer;
};
 */

struct BoardPins
{
	/**
	 * @brief STM32 GPIO Configuration
	 */
	// Gpio led{10, Port::A, Mode::Output_Push_Pull, Pull::None, Speed::Low, Alternate::None, false, 0, 0, ExtiTrigger::None};
	// Gpio button{13, Port::A, Mode::Input, Pull::None, Speed::Low, Alternate::None, false, 50, 0, ExtiTrigger::None};

	/**
	 * @brief ESP32 GPIO Configuration (falls benötigt)
	 */
	// Gpio led{15, Mode::Output, Pull::None, Speed::Low, false, 0, 0, Interrupt::Disabled};
	// Gpio button{9, Mode::Input, Pull::Up, Speed::Low, false, 50, 0, Interrupt::Disabled};

	/**
	 * @brief SPI Pins (PB3, PB4, PB5 und PB0 für NSS)
	 *
	 */
	Gpio spi1_sck{3, Port::B, Mode::Alternate_Push_Pull, Pull::None, Speed::Very_High, Alternate::SPI_AF0, false, 0, 0, ExtiTrigger::None};
	Gpio spi1_miso{4, Port::B, Mode::Alternate_Push_Pull, Pull::None, Speed::Very_High, Alternate::SPI_AF0, false, 0, 0, ExtiTrigger::None};
	Gpio spi1_mosi{5, Port::B, Mode::Alternate_Push_Pull, Pull::None, Speed::Very_High, Alternate::SPI_AF0, false, 0, 0, ExtiTrigger::None};
	Gpio spi1_nss{0, Port::B, Mode::Output_Push_Pull, Pull::Up, Speed::High, Alternate::None, false, 0, 0, ExtiTrigger::None};

	// Array mit allen GPIO-Pins (SPI, LEDs, Button)
	std::array<Gpio *, 4> allPins{&spi1_sck, &spi1_miso, &spi1_mosi, &spi1_nss};
};
// Globale Instanz der Board-Pins
inline BoardPins boardPins;

struct BoardPeripherals
{
#ifdef MASTER_CONFIG
	Spi spi1{
		boardPins.spi1_sck,
		boardPins.spi1_miso,
		boardPins.spi1_mosi,
		boardPins.spi1_nss,
		SPI1,
		SpiMode::Master,
		SpiDirection::FullDuplex, // Full-Duplex für Senden und Empfangen
		SpiDataSize::Bits8,		  // 8-Bit für ASCII-Zeichen
		SpiClockPolarity::Low,
		SpiClockPhase::FirstEdge,
		SpiNSS::Soft, // Software NSS im Master-Modus
		SpiBaudRatePrescaler::Prescaler32,
		SpiFirstBit::MSB,
		SpiTIMode::Disable,
		SpiCRCCalculation::Disable,
		7,
		SpiCRCLength::Length8,
		SpiNSSPMode::Software};

	const uint8_t txData = 'A'; // ASCII-Zeichen 'A' (0x41)

#else // SLAVE_CONFIG
	Spi spi1{
		boardPins.spi1_sck,
		boardPins.spi1_miso,
		boardPins.spi1_mosi,
		boardPins.spi1_nss,
		SPI1,
		SpiMode::Slave,
		SpiDirection::FullDuplex, // Full-Duplex für Senden und Empfangen
		SpiDataSize::Bits8,		  // 8-Bit für ASCII-Zeichen
		SpiClockPolarity::Low,
		SpiClockPhase::FirstEdge,
		SpiNSS::Hard_In, // Hardware NSS im Slave-Modus
		SpiBaudRatePrescaler::Prescaler32,
		SpiFirstBit::MSB,
		SpiTIMode::Disable,
		SpiCRCCalculation::Disable,
		7,
		SpiCRCLength::Length8,
		SpiNSSPMode::Hardware};

	const uint8_t txData = 'O'; // ASCII-Zeichen 'O' (0x4F)
#endif

	Dma dma1{
		DmaRequest::SPI1_TX,
		DmaRequest::SPI1_RX,
		// DmaDirection::MemToPeriph,
		DmaPeriphInc::Disable,
		DmaMemInc::Enable,
		DmaPeriphDataSizeAlignment::Byte,
		DmaMemDataSizeAlignment::Byte,
		DmaMode::Normal,
		DmaPriority::High};
};

// Globale Instanz der Peripherie
inline BoardPeripherals peripherals;
