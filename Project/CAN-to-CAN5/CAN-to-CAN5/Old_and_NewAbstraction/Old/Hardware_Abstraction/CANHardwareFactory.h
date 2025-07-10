#ifndef CAN_HARDWARE_FACTORY_H
#define CAN_HARDWARE_FACTORY_H

#include "CANHardwareInterface.h"
//#include "Zephyr/ZephyrCANHardware.h"
#include "STM32/STM32CANHardware.h"
//#include "PIC/PICCANHardware.h"
#include <string>
#include <stdexcept>
#include <cstring>




class CANHardwareFactory {
public:
    static CANHardwareInterface* CreateHardware(const std::string& platform)
    {
        if (strcmp(platform.c_str(), "STM32")== 0)
        {
            return new STM32CANHardware();
        }
        //  else if (platform == "Zephyr") {
       //    return new ZephyrCANHardware();
      //}   else if (platform == "PIC") {
     //      return new PICCANHardware();}
         else {
            return nullptr;
        }
    }
};
#endif // CAN_HARDWARE_FACTORY_H


