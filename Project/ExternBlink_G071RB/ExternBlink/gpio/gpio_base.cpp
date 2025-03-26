/*
 * gpio_base.cpp
 *
 *  Created on: Mar 25, 2025
 *      Author: jan.kristel
 */


#include "gpio_base.h"


GPIO_base::GPIO_base(uint32_t pin, uint32_t mode, bool pinInverted)
    : _pin(pin), _mode(mode), _pinInverted(pinInverted)
{}

GPIO_base::~GPIO_base() {}


uint32_t GPIO_base::getPin() const
{
    return _pin;
}

uint32_t GPIO_base::getMode() const
{
    return _mode;
}

bool GPIO_base::isPinInverted() const
{
    return _pinInverted;
}


