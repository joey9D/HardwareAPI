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
	// Gpio button{9, Port::A, Mode::Input, Pull::Up, Speed::Low, Alternate::None, false, 50, 0, ExtiTrigger::None};

	/**
	 * @brief STM32 SPI Configuration
	 *
	 */
	// SPI1 (Master) Pins konfigurieren - AF0 für SPI1 auf STM32G0
	Gpio spi1_sck{5, Port::A, Mode::Alternate_Push_Pull,
				  Pull::None, Speed::Very_High, Alternate::SPI_AF0, false, 0, 0, ExtiTrigger::None};
	Gpio spi1_mosi{7, Port::A, Mode::Alternate_Push_Pull,
				   Pull::None, Speed::Very_High, Alternate::SPI_AF0, false, 0, 0, ExtiTrigger::None};
	Gpio spi1_miso{6, Port::A, Mode::Alternate_Push_Pull,
				   Pull::None, Speed::Very_High, Alternate::SPI_AF0, false, 0, 0, ExtiTrigger::None};
	Gpio spi1_nss{4, Port::A, Mode::Output_Push_Pull,
				  Pull::Up, Speed::High, Alternate::None, false, 0, 0, ExtiTrigger::None};

	// SPI2 (Slave) Pins konfigurieren - AF1 für SPI2 auf STM32G0
	Gpio spi2_sck{14, Port::B, Mode::Alternate_Push_Pull,
				  Pull::None, Speed::Very_High, Alternate::SPI_AF1, false, 0, 0, ExtiTrigger::None};
	Gpio spi2_mosi{5, Port::B, Mode::Alternate_Push_Pull,
				   Pull::None, Speed::Very_High, Alternate::SPI_AF1, false, 0, 0, ExtiTrigger::None};
	Gpio spi2_miso{4, Port::B, Mode::Alternate_Push_Pull,
				   Pull::None, Speed::Very_High, Alternate::SPI_AF1, false, 0, 0, ExtiTrigger::None};
	Gpio spi2_nss{3, Port::B, Mode::Alternate_Push_Pull,
				  Pull::Up, Speed::Very_High, Alternate::SPI_AF1, false, 0, 0, ExtiTrigger::None};

	/**
	 * @brief ESP32 GPIO Configuration
	 */
	// Gpio led{15, Mode::Output, Pull::None, Speed::Low, false, 0, 0, Interrupt::Disabled};
	// Gpio button{9, Mode::Input, Pull::Up, Speed::Low, false, 50, 0, Interrupt::Disabled};

	std::array<Gpio *, 8> allPins{&spi1_sck, &spi1_mosi, &spi1_miso, &spi1_nss,
								  &spi2_sck, &spi2_mosi, &spi2_miso, &spi2_nss};
};
inline BoardPins boardPins;

// SPI-DMA-Instanzen
struct BoardPeripherals
{
	// SPI-Handle
	// SPI_HandleTypeDef hspi1;

	// SPI-DMA
	// SpiDMA spi1_dma{hspi1, SPI1};

	// SPI mit DMA
	// Spi spi1{boardPins.spi1_sck, boardPins.spi1_miso, boardPins.spi1_mosi, boardPins.spi1_cs,
	// 		 SPI1, SpiMode::Master, SpiDataSize::Bits8, &spi1_dma};
};

// Globale Instanz
inline BoardPeripherals peripherals;
