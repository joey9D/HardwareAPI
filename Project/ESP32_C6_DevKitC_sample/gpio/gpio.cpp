extern "C"{
    #include <stdio.h>
    #include <inttypes.h>
    #include "sdkconfig.h"
    #include "gpio.h" // from esp
}

#include "gpio.hpp"
// #include "main/hw_enum_classes.hpp"

Gpio::Gpio(
    uint64_t pin,
    Mode mode,
    Pull pull,
    Speed speed,
    bool inverted,
    uint32_t debounceTime,
    uint8_t debounceState,
    Interrupt intr
) : _pin(pin), _mode(mode), _pull(pull), _speed(speed), 
    _inverted(inverted), _debounceTime(debounceTime), 
    _debounceState(debounceState), _intr(Interrupt::Disabled)
{
    // Initialization code can be added here if needed
}

// void Gpio::gpio_init()
// {

// }