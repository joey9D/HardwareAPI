#pragma once

#include <cstdint>


class GpioInterface
{
public:
    GpioInterface() = default;
    virtual ~GpioInterface() = default;

    virtual bool readPin() const = 0;
    virtual void writePin(bool state) = 0;
    virtual void tooglePin() = 0;

    virtual void setMode(Mode mode);
    virtual void setPull(Pull pull);
    virtual void setSpeed(Speed speed);

    virtual uint16_t getPin() const =0;
    virtual GPIO_TypeDef* getPort() const;
    virtual Mode getMode() const;
    virtual Pull getPull() const;
    virtual Speed getSpeed() const;
    virtual HAL_State getHALState() const;
};
