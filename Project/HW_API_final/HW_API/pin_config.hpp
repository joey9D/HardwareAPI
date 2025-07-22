/*
 * pin_config.h
 *
 *  Created on: Jul 22, 2025
 *      Author: jan.kristel
 */

#ifndef PIN_CONFIG_HPP_
#define PIN_CONFIG_HPP_

#include <array>
//#include "stm32c0xx_hal.h"
#include "gpio.hpp"


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

//class Gpio;

struct BoardPins
{
	Gpio led {15, Port::A, Mode::Output_Push_Pull, Pull::None, Speed::Low, false, 0, 0, ExtiTrigger::None};
	Gpio button {9, Port::A, Mode::Input, Pull::Up, Speed::Low, false, 50, 0, ExtiTrigger::None};


	std::array<Gpio*, 2> allPins {&led, &button};
};
inline BoardPins boardPins;

#endif /* PIN_CONFIG_HPP_ */
