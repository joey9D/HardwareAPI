#pragma once

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
    virtual void togglePin() = 0;
    virtual bool lockPin() = 0;

};

#endif /* end cplusplus */
