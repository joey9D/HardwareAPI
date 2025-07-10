#ifndef CAN_HARDWARE_FACTORY_H
#define CAN_HARDWARE_FACTORY_H

#include "CANHardwareInterface.h"

// Platform detection (define one of these in build system)
//#define PLATFORM_STM32
//#define PLATFORM_ZEPHYR
//#define PLATFORM_PIC

// Include platform-specific drivers conditionally
#if defined(PLATFORM_STM32)
    #include "STM32/STM32CANHardware.h"
#elif defined(PLATFORM_ZEPHYR)
    #include "Zephyr/ZephyrCANHardware.h"
#elif defined(PLATFORM_PIC)
    #include "PIC/PICCANHardware.h"
#else
    #error "No platform defined! Define PLATFORM_STM32, PLATFORM_ZEPHYR, or PLATFORM_PIC in your build."
#endif

class CANHardwareFactory 
{
public:
    // Create hardware instance for the target platform
    static CANHardwareInterface* CreateHardware() 
    {
        // Compile-time platform selection
        #if defined(PLATFORM_STM32)
            static STM32CANHardware instance;
            return &instance;
        #elif defined(PLATFORM_ZEPHYR)
            static ZephyrCANHardware instance;
            return &instance;
        #elif defined(PLATFORM_PIC)
            static PICCANHardware instance;
            return &instance;
        #else
            return nullptr; // Unreachable due to #error above
        #endif
    }
};

#endif // CAN_HARDWARE_FACTORY_H
