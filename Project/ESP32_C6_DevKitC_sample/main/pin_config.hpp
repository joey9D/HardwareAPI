#pragma once

#include <array>
#include "gpio/gpio.hpp"

/**
 *  uint64_t pin,
    Mode mode,
    Pull pull,
    Speed speed,
    bool inverted,
    uint32_t debounceTime,
    uint8_t debounceState,
    // ExtiTrigger extiTrigger
 */

struct BoardPins
{
    Gpio led {15, Mode::Output_Push_Pull, Pull::None, Speed::Low, false, 0, 0};
	Gpio button {9, Port::A, Mode::Input, Pull::Up, Speed::Low, false, 50, 0};


	std::array<Gpio*, 2> allPins {&led, &button};
};
inline BoardPins boardPins;