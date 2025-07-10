#ifndef HARDWARE_FACTORY_H
#define HARDWARE_FACTORY_H

#ifdef __cplusplus
#include "Hardware_Interface.h"


// extern HardwareInterface* _hardware;

// extern "C" void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
//   if (_hardware) {
//       _hardware->HandlePinInterrupt(GPIO_Pin);
//   }
// }

class HardwareFactory {
public:
    static HardwareInterface* Create() {
        #if defined(STM32F0)
            #include "../STM32/STM32F0/STM32F0_Hardware.h"
            #include "../STM32/Common/CO_driver_target.h"
            static STM32F0_Hardware instance;
        #elif defined(STM32F1)
            #include "../STM32/STM32F1/STM32F1_Hardware.h"
            #include "../STM32/Common/CO_driver_target.h"
            static STM32F1_Hardware instance;
        #elif defined(STM32F4)
            #include "../STM32/STM32F4/STM32F4_Hardware.h"
            #include "../STM32/Common/CO_driver_target.h"
            static STM32F4_Hardware instance;
        #elif defined(STM32F7)
            #include "../STM32/STM32F7/STM32F7_Hardware.h"
            #include "../STM32/Common/CO_driver_target.h"
            static STM32F7_Hardware instance;
        #elif defined(STM32G0)
            #include "../STM32/STM32G0/STM32G0_Hardware.h"
            #include "../STM32/Common/CO_driver_target.h"
            static STM32G0_Hardware instance;
        #elif defined(STM32H7)
            #include "../STM32/STM32H7/STM32H7_Hardware.h"
            #include "../STM32/Common/CO_driver_target.h"
            static STM32H7_Hardware instance;
        #elif defined(STM32L0)
            #include "../STM32/STM32L0/STM32L0_Hardware.h"
            #include "../STM32/Common/CO_driver_target.h"
            static STM32L0_Hardware instance;
        #elif defined(STM32MP)
            #include "../STM32/STM32MP/STM32MP_Hardware.h"
            #include "../STM32/Common/CO_driver_target.h"
            static STM32MP_Hardware instance;
        #elif defined(STM32WB)
            #include "../STM32/STM32WB/STM32WB_Hardware.h"
            #include "../STM32/Common/CO_driver_target.h"
            static STM32WB_Hardware instance;
        #elif defined(STM32WL)
            #include "../STM32/STM32WL/STM32WL_Hardware.h"
            #include "../STM32/Common/CO_driver_target.h"
            static STM32WL_Hardware instance;
        #else
            #error "Unsupported STM32 series"
        #endif
        
        return &instance;
    }
};
extern "C" {  // Move extern "C" here to expose C-compatible API
#endif

// C-Compatible API (visible to both C and C++)
typedef void* HardwareInstance;
HardwareInstance CreateHardwareInstance();  // C can call this

#ifdef __cplusplus
} // extern "C"
#endif

#endif



