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
// Timer class is only available for STM32 platform
#ifdef STM32_PLATFORM
#include "timer.hpp"
#endif

#ifdef __cplusplus



class HardwareInterface
{
public:
    virtual ~HardwareInterface() = default;

    // System init
    virtual void init_sys() = 0;

    // clock
    virtual void init_clock() = 0;
	virtual void delay(uint32_t ms) = 0;

    // gpio
    virtual void initAllPins() = 0;
};

#endif /* end cplusplus */


#endif /* CORE_HW_INTERFACE_HPP_ */
