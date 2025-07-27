#pragma once

#include "hw_enum_classes.hpp"
#include "gpio_interface.hpp"

class Gpio : public IGpio
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
    
        void gpio_init() override;
        
        // GPIO functions
        bool readPin() const override;
        void writePin(bool value) const override;
        void togglePin() const override;
        
        // Getter functions - adapted to interface
        uint64_t getPin() const override;  // ESP32 uses uint64_t
        Mode getMode() const override;
        Pull getPull() const override;
        Speed getSpeed() const override;
        
        // Helper functions
        bool isPinOn() const override;
        bool isDebouncePinOn() override;
        bool isPinInverted() const override;

    private:
        uint64_t _pin;
        Mode _mode;
        Pull _pull;
        Speed _speed;
        bool _inverted;
        uint32_t _debounceTime;
        uint8_t _debounceState;
        int64_t _lastTimeUs;
        Interrupt _intr;
};