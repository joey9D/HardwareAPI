#pragma once

#include <array>
#include "gpio.hpp"

/**
 *  uint64_t _pin; // im Konstruktor wieder bit shift
    Mode _mode;
    Pull _pull;
    Speed _speed;
    bool _inverted;
    uint32_t _debounceTime;
    uint8_t _debounceState;
    // Timer debounceTimer;
    Interrupt _intr;
};
 */

struct BoardPins
{
    Gpio led {15, Mode::Output, Pull::None, Speed::Low, false, 0, 0, Interrupt::Disabled};
	Gpio button {9, Mode::Input, Pull::Up, Speed::Low, false, 50, 0, Interrupt::Disabled};


	std::array<Gpio*, 2> allPins {&led, &button};
};
inline BoardPins boardPins;