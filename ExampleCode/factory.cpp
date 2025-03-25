#include "IGPIO.h"

#ifdef PLATFORM_STM32
#include "GPIO_STM32.h"
#endif
#ifdef PLATFORM_ZEPHYR
#include "GPIO_Zephyr.h"
#endif

IGPIO* createGPIOInstance(void* port, uint16_t pin, bool inverted = false) {
#ifdef PLATFORM_STM32
    return new GPIO_STM32(static_cast<GPIO_TypeDef*>(port), pin, inverted);
#endif
#ifdef PLATFORM_ZEPHYR
    return new GPIO_Zephyr(static_cast<const struct device*>(port), pin, inverted);
#endif
    return nullptr; // Falls keine Plattform definiert ist
}
    