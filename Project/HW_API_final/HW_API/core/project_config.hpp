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
	Gpio led{10, Port::A, Mode::Output_Push_Pull, Pull::None, Speed::Low, Alternate::None, false, 0, 0, ExtiTrigger::None};
	Gpio button{9, Port::A, Mode::Input, Pull::Up, Speed::Low, Alternate::None, false, 50, 0, ExtiTrigger::None};
	// SPI-Pins
	// Gpio spi1_sck{GPIOA, GPIO_PIN_5, Mode::Alternate_Push_Pull, Pull::None, Speed::High, Alternate::SPI1_SCK};
	// Gpio spi1_miso{GPIOA, GPIO_PIN_6, Mode::Alternate_Push_Pull, Pull::None, Speed::High, Alternate::SPI1_MISO};
	// Gpio spi1_mosi{GPIOA, GPIO_PIN_7, Mode::Alternate_Push_Pull, Pull::None, Speed::High, Alternate::SPI1_MOSI};
	// Gpio spi1_cs{GPIOB, GPIO_PIN_6, Mode::Output_Push_Pull, Pull::Up, Speed::High};

	/**
	 * @brief ESP32 GPIO Configuration
	 */
	// Gpio led{15, Mode::Output, Pull::None, Speed::Low, false, 0, 0, Interrupt::Disabled};
	// Gpio button{9, Mode::Input, Pull::Up, Speed::Low, false, 50, 0, Interrupt::Disabled};

	std::array<Gpio *, 2> allPins{&led, &button};
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
