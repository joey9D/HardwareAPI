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

// MCU-Familien-Definitionen für bedingte Kompilierung
#if defined(STM32C0xx)
#define IS_STM32C0 1
#define IS_STM32G0 0
#define SUPPORTS_SPI2 0 // STM32C0 unterstützt nur SPI1
#elif defined(STM32G0xx)
#define IS_STM32C0 0
#define IS_STM32G0 1
#define SUPPORTS_SPI2 1 // STM32G0 unterstützt SPI2
#else
#error "Unsupported STM32 family, only STM32C0xx and STM32G0xx are supported"
#endif

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
#if defined(STM32C0xx)
	// SPI1 (Master) Pins konfigurieren für STM32C0xx
	Gpio spi1_sck{3, Port::B, Mode::Alternate_Push_Pull,
				  Pull::None, Speed::Very_High, Alternate::SPI_AF0, false, 0, 0, ExtiTrigger::None};
	Gpio spi1_mosi{5, Port::B, Mode::Alternate_Push_Pull,
				   Pull::None, Speed::Very_High, Alternate::SPI_AF0, false, 0, 0, ExtiTrigger::None};
	Gpio spi1_miso{4, Port::B, Mode::Alternate_Push_Pull,
				   Pull::None, Speed::Very_High, Alternate::SPI_AF0, false, 0, 0, ExtiTrigger::None};
	Gpio spi1_nss{15, Port::A, Mode::Output_Push_Pull,
				  Pull::Up, Speed::High, Alternate::None, false, 0, 0, ExtiTrigger::None};
#elif defined(STM32G0xx)
	// SPI1 Pins konfigurieren für STM32G0xx
	Gpio spi1_sck{3, Port::B, Mode::Alternate_Push_Pull,
				  Pull::None, Speed::Very_High, Alternate::SPI_AF0, false, 0, 0, ExtiTrigger::None};
	Gpio spi1_mosi{5, Port::B, Mode::Alternate_Push_Pull,
				   Pull::None, Speed::Very_High, Alternate::SPI_AF0, false, 0, 0, ExtiTrigger::None};
	Gpio spi1_miso{4, Port::B, Mode::Alternate_Push_Pull,
				   Pull::None, Speed::Very_High, Alternate::SPI_AF0, false, 0, 0, ExtiTrigger::None};

	// HINWEIS: NSS-Pin-Konfiguration je nach Modus (Master/Slave) anpassen
	// Für den SLAVE-Modus (Standard):
	Gpio spi1_nss{8, Port::A, Mode::Alternate_Push_Pull, // Als Alternate Function für Hardware-NSS im Slave-Modus
				  Pull::Up, Speed::High, Alternate::SPI_AF0, false, 0, 0, ExtiTrigger::None};

	// Für den MASTER-Modus (auskommentiert):
	/*
	Gpio spi1_nss{15, Port::A, Mode::Output_Push_Pull,    // Als Output für Software-NSS im Master-Modus
				  Pull::Up, Speed::High, Alternate::None, false, 0, 0, ExtiTrigger::None};
	*/
#endif

#if SUPPORTS_SPI2
	// SPI2 (Slave) Pins konfigurieren - nur für STM32G0 (verwendet AF1 für SPI2)
	Gpio spi2_sck{5, Port::A, Mode::Alternate_Push_Pull,
				  Pull::None, Speed::Very_High, Alternate::SPI_AF0, false, 0, 0, ExtiTrigger::None};
	Gpio spi2_mosi{7, Port::A, Mode::Alternate_Push_Pull,
				   Pull::None, Speed::Very_High, Alternate::SPI_AF0, false, 0, 0, ExtiTrigger::None};
	Gpio spi2_miso{6, Port::A, Mode::Alternate_Push_Pull,
				   Pull::None, Speed::Very_High, Alternate::SPI_AF0, false, 0, 0, ExtiTrigger::None};
	Gpio spi2_nss{0, Port::B, Mode::Input, // Input-Modus für Software-NSS im Slave-Modus
				  Pull::Up, Speed::High, Alternate::None, false, 0, 0, ExtiTrigger::None};
#endif

	/**
	 * @brief ESP32 GPIO Configuration
	 */
	// Gpio led{15, Mode::Output, Pull::None, Speed::Low, false, 0, 0, Interrupt::Disabled};
	// Gpio button{9, Mode::Input, Pull::Up, Speed::Low, false, 50, 0, Interrupt::Disabled};

#if SUPPORTS_SPI2
	std::array<Gpio *, 10> allPins{&led, &button,
								   &spi1_sck, &spi1_mosi, &spi1_miso, &spi1_nss,
								   &spi2_sck, &spi2_mosi, &spi2_miso, &spi2_nss};
#else
	std::array<Gpio *, 6> allPins{&led, &button,
								  &spi1_sck, &spi1_mosi, &spi1_miso, &spi1_nss};
#endif
};
inline BoardPins boardPins;

// Definition der Peripherie-Objekte
struct BoardPeripherals
{
	// DMA-Pointer (wird in der Initialisierungsfunktion gesetzt)
	SpiDMA *spi1_dma = nullptr;

#if defined(STM32C0xx)
	// SPI1 Konfiguration für STM32C0xx (typischerweise Master)
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
			 nullptr}; // DMA wird später gesetzt
#elif defined(STM32G0xx)
	// SPI1 Konfiguration für STM32G0xx
	// HINWEIS: Wechseln Sie zwischen den beiden Konfigurationen entsprechend des gewünschten Modus

	// SLAVE-MODUS KONFIGURATION - Standard für den Test
	Spi spi1{boardPins.spi1_sck,
			 boardPins.spi1_miso,
			 boardPins.spi1_mosi,
			 boardPins.spi1_nss,
			 SPI1,
			 SpiMode::Slave, // Slave-Modus
			 SpiDirection::FullDuplex,
			 SpiDataSize::Bits8,
			 SpiClockPolarity::Low,
			 SpiClockPhase::FirstEdge,
			 SpiNSS::Hard_In, // Hardware NSS im Slave-Modus
			 SpiBaudRatePrescaler::Prescaler32,
			 SpiFirstBit::MSB,
			 SpiTIMode::Disable,
			 SpiCRCCalculation::Disable,
			 SpiCRCPolynomial::Polynomial7,
			 SpiCRCLength::Length8,
			 SpiNSSPMode::Software,
			 nullptr}; // DMA wird später gesetzt

	// MASTER-MODUS KONFIGURATION - Auskommentiert, bei Bedarf tauschen
	/*
	Spi spi1{boardPins.spi1_sck,
			 boardPins.spi1_miso,
			 boardPins.spi1_mosi,
			 boardPins.spi1_nss,
			 SPI1,
			 SpiMode::Master,              // Master-Modus
			 SpiDirection::FullDuplex,
			 SpiDataSize::Bits8,
			 SpiClockPolarity::Low,
			 SpiClockPhase::FirstEdge,
			 SpiNSS::Soft,                 // Software NSS im Master-Modus
			 SpiBaudRatePrescaler::Prescaler32,
			 SpiFirstBit::MSB,
			 SpiTIMode::Disable,
			 SpiCRCCalculation::Disable,
			 SpiCRCPolynomial::Polynomial7,
			 SpiCRCLength::Length8,
			 SpiNSSPMode::Software,
			 nullptr}; // DMA wird später gesetzt
	*/
#endif

#if SUPPORTS_SPI2
	// DMA-Pointer für SPI2 (wird in der Initialisierungsfunktion gesetzt)
	SpiDMA *spi2_dma = nullptr;

	// SPI2 nur für MCU-Familien mit SPI2-Unterstützung (z.B. STM32G0)
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
			 SpiNSSPMode::Software,
			 nullptr}; // DMA wird später gesetzt
#endif
};

// Globale Instanz
inline BoardPeripherals peripherals;

// Keine vorgezogene DMA-Instanzierung hier, das muss in der main.cpp erfolgen
