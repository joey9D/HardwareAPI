#pragma once


#include "hw_enum_classes.hpp"


class IGpio
{
    public:
        virtual ~IGpio() = default;

        // Initialization
        virtual void gpio_init() = 0;
        virtual void port_clock_enable(Port port) const = 0;

        // Functions
        virtual bool readPin() const = 0;
        virtual void writePin(bool value) const = 0;
        virtual void togglePin() const = 0;

        // Getters
        virtual uint16_t getPin() const = 0;
        virtual GPIO_TypeDef *get_GPIO_TypeDef_port() const = 0;
        virtual Mode getMode() const = 0;
        virtual Pull getPull() const = 0;
        virtual Speed getSpeed() const = 0;

        // Helper functions
        virtual bool isPinOn() const = 0;
        virtual bool isDebouncePinOn() = 0;
        virtual bool isPinInverted() const = 0;
}