#pragma once

#include <cstdint>


class GpioInterface
{
public:
    GpioInterface() = default;
    virtual ~GpioInterface() = default;

    virtual bool readPin() const = 0;
    virtual void writePin(bool value) = 0;
    virtual void togglePin() = 0;
    virtual bool lockPin() const = 0;
    // virtual void EXTI_IRQHandler();
    // virtual void EXTI_Risising_Callback();
    // virtual void EXTI_Falling_Callback();

    /**
     * @note Will be implemented in derived classes
     * for specific mcu/hw implementation.
     *
     */
    // virtual uint16_t getPin() const = 0;
    // virtual Port getPort() const = 0;
    // virtual Mode getMode() const = 0;
    // virtual Pull getPull() const = 0;
    // virtual Speed getSpeed() const = 0;
};
