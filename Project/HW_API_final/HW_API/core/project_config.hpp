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
#include "../spi/spi_dma_interface.hpp"

// Platform-spezifische Includes
#ifdef STM32_PLATFORM
#include "../gpio/gpio_stm32.hpp"
#include "../spi/spi_stm32.hpp"
#include "../spi/spi_dma_stm32.hpp"
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

// class Gpio;

struct BoardPins
{
	/**
	 * @brief STM32 GPIO Configuration
	 */
	// Gpio led{10, Port::A, Mode::Output_Push_Pull, Pull::None, Speed::Low, Alternate::None, false, 0, 0, ExtiTrigger::None};
	// Gpio button{13, Port::C, Mode::Input, Pull::None, Speed::Low, Alternate::None, false, 50, 0, ExtiTrigger::None};
	Gpio led{0, Port::B, Mode::Output_Push_Pull, Pull::None, Speed::Low, Alternate::None, false, 0, 0, ExtiTrigger::None};
	Gpio button{13, Port::C, Mode::Input, Pull::None, Speed::Low, Alternate::None, false, 50, 0, ExtiTrigger::None};

	/**
	 * @brief STM32 SPI Configuration
	 *
	 */
	// SPI1 (Master) Pins konfigurieren - AF0 für SPI1 auf STM32G0
	Gpio spi1_sck{3, Port::B, Mode::Alternate_Push_Pull,
				  Pull::None, Speed::Very_High, Alternate::SPI_AF0, false, 0, 0, ExtiTrigger::None};
	Gpio spi1_mosi{5, Port::B, Mode::Alternate_Push_Pull,
				   Pull::None, Speed::Very_High, Alternate::SPI_AF0, false, 0, 0, ExtiTrigger::None};
	Gpio spi1_miso{4, Port::B, Mode::Alternate_Push_Pull,
				   Pull::None, Speed::Very_High, Alternate::SPI_AF0, false, 0, 0, ExtiTrigger::None};
	Gpio spi1_nss{15, Port::A, Mode::Output_Push_Pull,
				  Pull::Up, Speed::High, Alternate::None, false, 0, 0, ExtiTrigger::None};

	// SPI2 (Slave) Pins konfigurieren - AF1 für SPI2 auf STM32G0
	Gpio spi2_sck{5, Port::A, Mode::Alternate_Push_Pull,
				  Pull::None, Speed::Very_High, Alternate::SPI_AF1, false, 0, 0, ExtiTrigger::None};
	Gpio spi2_mosi{7, Port::A, Mode::Alternate_Push_Pull,
				   Pull::None, Speed::Very_High, Alternate::SPI_AF1, false, 0, 0, ExtiTrigger::None};
	Gpio spi2_miso{6, Port::A, Mode::Alternate_Push_Pull,
				   Pull::None, Speed::Very_High, Alternate::SPI_AF1, false, 0, 0, ExtiTrigger::None};
	Gpio spi2_nss{0, Port::B, Mode::Input, // Input-Modus für Software-NSS im Slave-Modus
				  Pull::Up, Speed::High, Alternate::None, false, 0, 0, ExtiTrigger::None};

	/**
	 * @brief ESP32 GPIO Configuration
	 */
	// Gpio led{15, Mode::Output, Pull::None, Speed::Low, false, 0, 0, Interrupt::Disabled};
	// Gpio button{9, Mode::Input, Pull::Up, Speed::Low, false, 50, 0, Interrupt::Disabled};

	std::array<Gpio *, 10> allPins{&led, &button,
								   &spi1_sck, &spi1_mosi, &spi1_miso, &spi1_nss,
								   &spi2_sck, &spi2_mosi, &spi2_miso, &spi2_nss};
};
inline BoardPins boardPins;

// SPI-DMA-Instanzen
struct BoardPeripherals
{
	Spi spi1{boardPins.spi1_sck,
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
			 SpiBaudRatePrescaler::Prescaler32,
			 SpiFirstBit::MSB,
			 SpiTIMode::Disable,
			 SpiCRCCalculation::Disable,
			 SpiCRCPolynomial::Polynomial7,
			 SpiCRCLength::Length8,
			 SpiNSSPMode::Software,
			 &spi1_dma};

	Spi spi2{boardPins.spi2_sck,
			 boardPins.spi2_miso,
			 boardPins.spi2_mosi,
			 boardPins.spi2_nss,
			 SPI2,
			 SpiMode::Slave,
			 SpiDirection::FullDuplex,
			 SpiDataSize::Bits8,
			 SpiClockPolarity::Low,
			 SpiClockPhase::FirstEdge,
			 SpiNSS::Soft,
			 SpiBaudRatePrescaler::Prescaler32,
			 SpiFirstBit::MSB,
			 SpiTIMode::Disable,
			 SpiCRCCalculation::Disable,
			 SpiCRCPolynomial::Polynomial7,
			 SpiCRCLength::Length8,
			 SpiNSSPMode::Software, // Geändert für Konsistenz mit SpiNSS::Soft
			 nullptr};

	// SPI-DMA für SPI1
	SpiDMA spi1_dma{
		DmaInstance::DMA1,				// DMA-Instance
		DmaStream::STREAM0,				// TX Stream
		DmaStream::STREAM1,				// RX Stream
		DmaChannel::CHANNEL1,			// TX Channel (abhängig vom STM32-Modell)
		DmaChannel::CHANNEL1,			// RX Channel (abhängig vom STM32-Modell)
		DmaDirection::MEMORY_TO_PERIPH, // TX Direction
		DmaDirection::PERIPH_TO_MEMORY, // RX Direction
		DmaMode::NORMAL,				// TX Mode
		DmaMode::NORMAL,				// RX Mode
		DmaPriority::HIGH,				// TX Priority
		DmaPriority::HIGH,				// RX Priority
		DmaIncrementMode::ENABLE,		// TX Memory Increment
		DmaIncrementMode::ENABLE,		// RX Memory Increment
		DmaIncrementMode::DISABLE,		// TX Peripheral Increment
		DmaIncrementMode::DISABLE,		// RX Peripheral Increment
		DmaDataAlignment::BYTE,			// TX Memory Data Size
		DmaDataAlignment::BYTE,			// RX Memory Data Size
		DmaDataAlignment::BYTE,			// TX Peripheral Data Size
		DmaDataAlignment::BYTE			// RX Peripheral Data Size
	};
};

// Globale Instanz
inline BoardPeripherals peripherals;
