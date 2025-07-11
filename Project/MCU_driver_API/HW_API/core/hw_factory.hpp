/*
 * hw_factory.hpp
 *
 *  Created on: Jul 10, 2025
 *      Author: jan.kristel
 */

#ifndef __HW_FACTORY_HPP
#define __HW_FACTORY_HPP

#ifdef __cplusplus

#include "hw_interface.hpp"

#ifdef STM32C0
	#include "stm32c0_hw.hpp"
#elif defined(STM32G0)
	#include "stm32g0_hw.h"
#endif


class HardwareFactory
{
    public:
        static HardwareInterface* create()
        {
#ifdef STM32C0
        	static Stm32c0_hw instance;
#else
			#error "Unsupported STM32 series"
#endif
			return &instance;
        }

}; /* class HardwareFactory */




#endif /* __cpluscplus */



#endif /* CORE_HW_FACTORY_HPP_ */
