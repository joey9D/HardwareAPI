#pragma once
#ifdef __cplusplus

#include "hw_interface.hpp"

#ifdef STM32C0
	#include "stm32c0_hw.hpp"
#elif defined(STM32G0)
	#include "stm32g0_hw.hpp"
// ESP32 PLATFORM DISABLED FOR STM32-ONLY BUILD
// #elif defined(ESP32C6)
// 	#include "esp32c6_hw.hpp"
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
