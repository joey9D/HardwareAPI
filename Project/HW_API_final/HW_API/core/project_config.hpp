/*
 * project_config.h
 *
 *  Created on: Jul 22, 2025
 *      Author: jan.kristel
 */

#pragma once

#include <array>

#include "../gpio/gpio_interface.hpp"
// #include "../spi/spi_interface.hpp"
// #include "../spi/dma_interface.hpp"

// Platform-spezifische Includes
#ifdef STM32_PLATFORM
#include "../gpio/gpio_stm32.hpp"
// #include "../spi/spi_stm32.hpp"
// #include "../spi/dma_stm32.hpp"

using namespace HW_API::STM32;

#elif defined(ESP_PLATFORM)
#include "../gpio/gpio_esp32.hpp"
// #include "../spi/spi_esp32.hpp"
// #include "../spi/dma_esp32.hpp"

using namespace HW_API::ESP32;
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
	// Gpio button{9, Port::A, Mode::Input, Pull::Up, Speed::Low, Alternate::None, false, 50, 0, ExtiTrigger::None};

	/**
	 * @brief ESP32 GPIO Configuration (falls benötigt)
	 */
	Gpio led{15, Mode::Output, Pull::None, Speed::Low, false, 0, 0, Interrupt::Disabled}; // Alternate::None is default set in header.
	Gpio button{9, Mode::Input, Pull::Up, Speed::Low, false, 50, 0, Interrupt::Disabled};

#if defined(MASTER_CONFIG) || defined(SLAVE_CONFIG)
	/**
	 * @brief SPI Pins (PB3, PB4, PB5 und PB0 für NSS)
	 *
	 */
	Gpio spi1_sck{3, Port::B, Mode::Alternate_Push_Pull, Pull::None, Speed::Very_High, Alternate::SPI_AF0, false, 0, 0, ExtiTrigger::None};
	Gpio spi1_miso{4, Port::B, Mode::Alternate_Push_Pull, Pull::None, Speed::Very_High, Alternate::SPI_AF0, false, 0, 0, ExtiTrigger::None};
	Gpio spi1_mosi{5, Port::B, Mode::Alternate_Push_Pull, Pull::None, Speed::Very_High, Alternate::SPI_AF0, false, 0, 0, ExtiTrigger::None};
	Gpio spi1_nss{0, Port::B, Mode::Output_Push_Pull, Pull::Up, Speed::High, Alternate::SPI_AF0, false, 0, 0, ExtiTrigger::None};
#endif
	// Array mit allen GPIO-Pins (SPI, LEDs, Button)
	// std::array<Gpio *, 4> allPins{&spi1_sck, &spi1_miso, &spi1_mosi, &spi1_nss};
	std::array<Gpio *, 2> allPins{&led, &button};
};
// Globale Instanz der Board-Pins
inline BoardPins boardPins;

struct BoardPeripherals
{
#ifdef MASTER_CONFIG
	Spi spi_master{
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
		SpiNSS::Soft,
		SpiBaudRatePrescaler::Prescaler32,
		SpiFirstBit::MSB,
		SpiTIMode::Disable,
		SpiCRCCalculation::Disable,
		7,
		SpiCRCLength::Length8,
		SpiNSSPMode::Disable};

	const uint8_t txData = 'A'; // ASCII-Zeichen 'A' (0x41)

	Dma dma_master{
		// DMA1_Channel3, // TX-channel
		// DMA1_Channel2, // RX-channel
		DmaRequest::SPI1_TX,
		DmaRequest::SPI1_RX,
		// DmaDirection::MemToPeriph,
		DmaPeriphInc::Disable,
		DmaMemInc::Enable,
		DmaPeriphDataSizeAlignment::Byte,
		DmaMemDataSizeAlignment::Byte,
		DmaMode::Normal,
		DmaPriority::High};
#endif
#ifdef SLAVE_CONFIG
	Spi spi_slave{
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
		SpiNSS::Soft,
		SpiBaudRatePrescaler::Prescaler32,
		SpiFirstBit::MSB,
		SpiTIMode::Disable,
		SpiCRCCalculation::Disable,
		7,
		SpiCRCLength::Length8,
		SpiNSSPMode::Disable};

	const uint8_t txData = 'O'; // ASCII-Zeichen 'O' (0x4F)

	Dma dma_slave{
		// DMA1_Channel3, // TX-channel
		// DMA1_Channel2, // RX-channel
		DmaRequest::SPI1_TX,
		DmaRequest::SPI1_RX,
		// DmaDirection::MemToPeriph,
		DmaPeriphInc::Disable,
		DmaMemInc::Enable,
		DmaPeriphDataSizeAlignment::Byte,
		DmaMemDataSizeAlignment::Byte,
		DmaMode::Normal,
		DmaPriority::High};

#endif
};

// Globale Instanz der Peripherie
inline BoardPeripherals peripherals;
