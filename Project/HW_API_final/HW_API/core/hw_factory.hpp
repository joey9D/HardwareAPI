#pragma once
#ifdef __cplusplus

#include "hw_interface.hpp"

#ifdef STM32C0xx
	#include "../platform/stm32/stm32c0xx/stm32c0xx_hw.hpp"
#elif defined(STM32G0xx)
	#include "../platform/stm32/stm32g0xx/stm32g0xx_hw.hpp"
// ESP32 PLATFORM DISABLED FOR STM32-ONLY BUILD
// #elif defined(ESP32C6)
// 	#include "esp32c6_hw.hpp"
#endif


class HardwareFactory
{
    public:
        static HardwareInterface* create()
        {
#ifdef STM32C0xx
        	static Stm32c0xx_hw instance;
#else
			#error "Unsupported STM32 series"
#endif
			return &instance;
        }

}; /* class HardwareFactory */




#endif /* __cpluscplus */
