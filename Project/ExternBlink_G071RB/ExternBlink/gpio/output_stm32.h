/*
 * output_stm32.h
 *
 *  Created on: Mar 25, 2025
 *      Author: jan.kristel
 */

#ifndef OUTPUT_STM32_H_
#define OUTPUT_STM32_H_

#include "gpio_stm32.h"
#include "output_base.h"

class Output_stm32 : public GPIO_stm32, public Output_base
{
    public:
       Output_stm32(uint32_t pin, uint32_t mode, uint32_t pull, uint32_t speed, uint32_t alternate, GPIO_TypeDef *port, bool pinInverted);
       ~Output_stm32() = default;
       void setPinOutput(bool activePinState) override;
       void toggle() override;
};


#endif /* OUTPUT_STM32_H_ */
