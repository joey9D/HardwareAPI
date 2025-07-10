#ifndef __HARDWARE_INTERFACE_HPP
#define __HARDWARE_INTERFACE_HPP

#ifdef __cplusplus
#include <cstdint>
#else
#include <stdint.h>
#endif

#ifdef __cplusplus

class HardwareInterface
{
public:
    HardwareInterface() = default;
    virtual ~HardwareInterface() = default;

    // Core Sys/Clock
//    virtual void Clock_Init() = 0;
//    virtual void Delay(uint32_t ms) = 0;
//    virtual uint32_t GetTick() const = 0;

    // Gpio
    virtual bool readPin() const = 0;
    virtual void writePin(bool value) const = 0;
    virtual void togglePin() const = 0;
    virtual bool lockPin() const = 0;

};

#endif /* end cplusplus */

#endif /* __GPIO_INTERFACE_HPP */
