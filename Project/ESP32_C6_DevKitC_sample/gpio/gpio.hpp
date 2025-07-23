#pragma once

extern "C" {
    #include "gpio_types.h"

}
#include "main/hw_enum_classes.hpp"


class Gpio
{
    public:
        Gpio(
            uint64_t pin,
            Mode mode,
            Pull pull,
            Speed speed,
            bool inverted,
            uint32_t debounceTime,
            uint8_t debounceState,
            Interrupt intr
        );
        
    private:
        uint64_t _pin; // im Konstruktor wieder bit shift
        Mode _mode;
        Pull _pull;
        Speed _speed;
        bool _inverted;
        uint32_t _debounceTime;
        uint8_t _debounceState;
        // Timer debounceTimer;
        Interrupt _intr;
};