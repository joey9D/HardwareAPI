#pragma once

#include <cstdint>


class GpioInterface
{
public:
    enum class mode : uint8_t
    {
        digital_output,
        open_drain,
        digital_input,
        analog,
        alternate_function
    };

    GpioInterface() = default;
    virtual ~GpioInterface() = default;

    virtual void setPin(bool state) = 0;

    virtual void toggle() = 0;

    virtual void mode(mode mode, bool state = false) = 0;

    virtual bool get() const = 0;

    virtual enum mode mode() const = 0;

    virtual uint16_t getPin() const = 0;
};
