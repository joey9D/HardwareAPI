#pragma once

#include <cstdint>


class GpioInterface
{
public:
    GpioInterface() = default;
    virtual ~GpioInterface() = default;

    virtual bool readPin() const = 0;
    virtual void writePin(bool value) = 0;
    virtual void tooglePin() = 0;
    virtual bool lockPin() = 0;
    virtual void EXTI_IRQHandler();
    virtual void EXTI_Risising_Callback();
    virtual void EXTI_Falling_Callback();

    virtual uint16_t getPin() const = 0;
    virtual uint32_t getPort() const = 0;
    virtual uint32_t getMode() const = 0;
    virtual uint32_t getPull() const = 0;
    virtual uint32_t getSpeed() const = 0;
};
