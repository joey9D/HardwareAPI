#pragma once

// extern "C" {
//     #include "gpio_types.h"

// }
#include "hw_enum_classes.hpp"


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
    
        void gpio_init();
        // void port_clock_enable(Port port) const;
        //		- functions
        bool readPin() const;
        void writePin(bool value) const;
        void togglePin() const;
        //		- getter
        uint16_t getPin() const;
        // GPIO_TypeDef *get_GPIO_TypeDef_port() const;
        Mode getMode() const;
        Pull getPull() const;
        Speed getSpeed() const;
    //	virtual Pin_State getPinState() const;
        //		- helper
        bool isPinOn() const;
        bool isDebouncePinOn();
        bool isPinInverted() const;


    private:
        uint64_t _pin; // im Konstruktor wieder bit shift
        Mode _mode;
        Pull _pull;
        Speed _speed;
        bool _inverted;
        uint32_t _debounceTime;
        uint8_t _debounceState;
        // Timer debounceTimer;
        int64_t _lastTimeUs;
        Interrupt _intr;
};