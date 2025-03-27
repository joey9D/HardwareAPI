#ifndef CAN_HARDWARE_FACTORY_H
#define CAN_HARDWARE_FACTORY_H

#include "CANHardwareInterface.h"
//#include "Zephyr/ZephyrCANHardware.h"
#include "STM32/STM32CANHardware.h"
//#include "PIC/PICCANHardware.h"
#include <string>
#include <stdexcept>


class CANHardwareFactory {
public:
    static CANHardwareInterface* CreateHardware(const std::string& platform) {
        if (platform == "STM32") {
            return new STM32CANHardware();
//        } else if (platform == "Zephyr") {
//            return new ZephyrCANHardware();
//        } else if (platform == "PIC") {
//            return new PICCANHardware();
        } else {
            throw std::invalid_argument("Unsupported platform: " + platform);
        }
    }
};
#endif // CAN_HARDWARE_FACTORY_H


