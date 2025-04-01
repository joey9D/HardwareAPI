/*
 * input_base.cpp
 *
 *  Created on: Mar 25, 2025
 *      Author: jan.kristel
 */


#include "input_base.h"

Input_base::Input_base(uint32_t debounceTime, uint8_t debounceState, Timer debounceTimer) 
    : _debounceTime(debounceTime), _debouceState(debounceState), _debounceTimer(debounceTimer)
{}

Input_base::~Input_base() = default;

bool isInputPinOn() 
{
    bool retval = false;
    if (HAL_GPIO_ReadPin(getPort(), getPin()) == GPIO_PIN_SET) {
        retval = true;
    }

    if (isPinInverted()) {
        retval = !retval;
    }

    return retval;
}

bool isDebouncePinOn() const;
