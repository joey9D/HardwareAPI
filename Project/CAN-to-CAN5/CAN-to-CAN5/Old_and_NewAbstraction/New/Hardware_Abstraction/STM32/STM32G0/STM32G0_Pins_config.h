#ifndef STM32G0_PINS_CONFIG_H
#define STM32G0_PINS_CONFIG_H

#include "stm32G0xx_hal.h" // Or your specific device's HAL header
#include "STM32G0_Hardware.h"


#include <cstdint>
#include "stm32G0xx_hal.h"
#include <array>
#include "Hardware_Definitions.h"
#include "ShiftRegisterIO.h"

enum class ExtiTrigger 
{
    None,
    Rising,
    Falling,
    RisingFalling
};


class Pin 
{
public:
    Pin(GPIO_TypeDef* port, uint16_t pin, bool inverted, uint32_t mode, uint32_t pull ,ExtiTrigger exti = ExtiTrigger::None)
        : port_(port), pin_(pin), inverted_(inverted), mode_(mode), pull_(pull) ,extiTrigger_(exti) {}

    void write(bool state) const 
    {
        HAL_GPIO_WritePin(port_, pin_, (state ^ inverted_) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    }
    bool read() const 
    {
        GPIO_PinState raw = HAL_GPIO_ReadPin(port_, pin_);
        return inverted_ ? raw == GPIO_PIN_RESET : raw == GPIO_PIN_SET;
    }
    void toggle() const 
    {
        HAL_GPIO_TogglePin(port_, pin_);
    }
    void init() const 
    {
        GPIO_InitTypeDef GPIO_InitStruct = {0};
        GPIO_InitStruct.Pin = pin_;
        GPIO_InitStruct.Mode = mode_;
        GPIO_InitStruct.Pull = pull_;


         // If EXTI is needed, override the mode
        if (extiTrigger_ != ExtiTrigger::None) {
            switch(extiTrigger_) {
                case ExtiTrigger::Rising:        GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING; break;
                case ExtiTrigger::Falling:       GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING; break;
                case ExtiTrigger::RisingFalling: GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING; break;
                default: break;
            }
        }
        HAL_GPIO_Init(port_, &GPIO_InitStruct);
    }

    GPIO_TypeDef* port() const { return port_; }
    uint16_t pin() const { return pin_; }
    bool inverted() const { return inverted_; }
    uint32_t mode() const { return mode_; }
    uint32_t pull() const { return pull_; }
    ExtiTrigger extiTrigger() const { return extiTrigger_; }


private:
    GPIO_TypeDef* port_;
    uint16_t pin_;
    bool inverted_;
    uint32_t mode_;
    uint32_t pull_;
    ExtiTrigger extiTrigger_;
};





#endif // PINS_CONFIG_H
