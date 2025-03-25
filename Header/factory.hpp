#ifndef _FACTORY_HPP
#define _FACTORY_HPP


/* Platform define via build-System or config */

#if defined(STM32)
    #include "stm32facotry.hpp"
#elif defined(ARDUINO)
    #include "arduinofactory.hpp"
#elif defined(ESP32)
    #include "esp32factory.hpp"
#else
    #error "Please select a supported platform."
#endif

















#endif /* _FACTORY_HPP */