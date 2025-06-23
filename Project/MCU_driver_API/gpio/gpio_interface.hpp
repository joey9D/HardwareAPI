// #pragma once

#ifndef __GPIO_INTERFACE_HPP
#define __GPIO_INTERFACE_HPP


#ifdef __cplusplus
#include <cstdint>
#else
#include <stdint.h>
#endif


#ifdef __cplusplus

class GpioInterface
{
public:
    GpioInterface() = default;
    virtual ~GpioInterface() = default;

    virtual bool readPin() const = 0;
    virtual void writePin(bool value) = 0;
    virtual void togglePin() const = 0;
    virtual bool lockPin() const = 0;

};

#endif /* end cplusplus */

#endif /* __GPIO_INTERFACE_HPP */
