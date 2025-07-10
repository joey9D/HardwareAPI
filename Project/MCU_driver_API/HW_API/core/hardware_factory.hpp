#ifndef __HARDWARE_FACTORY_HPP
#define __HARDWARE_FACTORY_HPP

#ifdef __cplusplus

#include "hardware_interface.hpp"

namespace stm32
{
class HardwareFactory
{
    public:
        static HardwareInterface* create()
        {
            #ifdef STM32C0
                #include "stm32c0xx_hal.h"

                static
            #else
                #error "Unsupported STM32 series"
            #endif

            return &instance;
        }

}
} /* namespace stm32 */



#endif /* __cpluscplus */

#endif /* __HARDWARE_FACTORY_HPP */
