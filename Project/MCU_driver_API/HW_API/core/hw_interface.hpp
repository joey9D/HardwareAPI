/*
 * hardware_interface.hpp
 *
 *  Created on: Jul 10, 2025
 *      Author: jan.kristel
 */

#ifndef __HW_INTERFACE_HPP
#define __HW_INTERFACE_HPP


#ifdef __cplusplus
#include <cstdint>
#else
#include <stdint.h>
#endif

#include "hw_enum_classes.hpp"
#include "timer.hpp"

#ifdef __cplusplus

struct PinConfig_t
{
	uint16_t pin;
	Port port;
	Mode mode;
	Pull pull;
	Speed speed;
	bool invertedPin;
	uint32_t debounceTime;
	uint8_t debounceState;
	Timer debounceTimer;
	ExtiTrigger extiTrigger = ExtiTrigger::None;
};

class HardwareInterface
{
public:
    virtual ~HardwareInterface() = default;

    // System init
    virtual void init_sys() = 0;

    // clock
    virtual void init_clock() = 0;
	virtual void delay(uint32_t ms) = 0;

};

#endif /* end cplusplus */


#endif /* CORE_HW_INTERFACE_HPP_ */
