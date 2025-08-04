#pragma once
#ifdef __cplusplus

#include "hw_interface.hpp"

#ifdef STM32C0xx
	#include "../platform/stm32/stm32c0xx/stm32c0xx_hw.hpp"
#elif defined(STM32G0xx)
	#include "../platform/stm32/stm32g0xx/stm32g0xx_hw.hpp"
#elif defined(ESP32C6)
	#include "../platform/esp32/esp32c6_devkitc/esp32c6_devkitc1_hw.hpp"
#endif


class HardwareFactory
{
    public:
        static HardwareInterface* create()
        {
#ifdef STM32C0xx
        	static Stm32c0xx_hw instance;
        	return &instance;
#elif defined(STM32G0xx)
        	static Stm32g0xx_hw instance;
        	return &instance;
#elif defined(ESP32C6)
        	static Esp32c6_hw instance;
        	return &instance;
#else
			#error "Unsupported platform. Define STM32C0xx, STM32G0xx, or ESP32C6"
#endif
        }

}; /* class HardwareFactory */




#endif /* __cpluscplus */
