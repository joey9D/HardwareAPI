/*
 * pin_config.h
 *
 *  Created on: Jul 22, 2025
 *      Author: jan.kristel
 */

#ifndef PIN_CONFIG_HPP_
#define PIN_CONFIG_HPP_

#include <array>
#include "gpio_interface.hpp"

// Platform-specific GPIO includes
#ifdef STM32_PLATFORM
#include "gpio_stm32.hpp"
// ESP32 PLATFORM DISABLED FOR STM32-ONLY BUILD
// #elif ESP32_PLATFORM
//     #include "gpio_esp32.hpp"
#endif

/**
 * struct PinConfig_t
{
	uint16_t pin;
	Port port;
	Mode mode;
	Pull pull;
	Speed speed;
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
	 * @brief STM32 GPIO Example
	 *
	 */
	// Gpio led{10, Port::A, Mode::Output_Push_Pull, Pull::None, Speed::Low, false, 0, 0, ExtiTrigger::None};
	// Gpio button{9, Port::A, Mode::Input, Pull::Up, Speed::Low, false, 50, 0, ExtiTrigger::None};

	/**
	 * @brief ESP32 GPIOP Example
	 *
	 */
	Gpio led{15, Mode::Output, Pull::None, Speed::Low, false, 0, 0, Interrupt::Disabled};
	Gpio button{9, Mode::Input, Pull::Up, Speed::Low, false, 50, 0, Interrupt::Disabled};

	std::array<Gpio *, 2> allPins{&led, &button};
};
inline BoardPins boardPins;

#endif /* PIN_CONFIG_HPP_ */
