#pragma once

#include "hw_enum_classes.hpp"

template<typename PinType>
class IGpioBase
{
    public:
        virtual ~IGpioBase() = default;
        
        virtual void gpio_init() = 0;
        
        // GPIO functions
        virtual bool readPin() const = 0;
        virtual void writePin(bool value) const = 0;
        virtual void togglePin() const = 0;
        
        // Getter functions - jetzt mit Template-Parameter
        virtual PinType getPin() const = 0;
        virtual Mode getMode() const = 0;  
        virtual Pull getPull() const = 0;
        virtual Speed getSpeed() const = 0;
        
        // Helper functions
        virtual bool isPinOn() const = 0;
        virtual bool isDebouncePinOn() = 0;
        virtual bool isPinInverted() const = 0;
};

// Platform-spezifische Type-Aliases
#ifdef STM32_PLATFORM
using IGpio = IGpioBase<uint16_t>;
#elif ESP32_PLATFORM  
using IGpio = IGpioBase<uint64_t>;
#endif