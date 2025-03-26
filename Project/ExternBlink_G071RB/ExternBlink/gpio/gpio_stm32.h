/*
 * gpio_stm32.h
 *
 *  Created on: Mar 25, 2025
 *      Author: jan.kristel
 */

#ifndef GPIO_STM32_H_
#define GPIO_STM32_H_


#include "gpio_base.h"
#include "stm32g0xx_hal.h"

#ifdef  __cplusplus
extern "C" {
#endif



class GPIO_stm32 : public GPIO_base
{
    private:
        uint32_t _pull;
        uint32_t _speed;
        uint32_t _alternate;
        GPIO_TypeDef* _port;
    public:
        GPIO_stm32(uint32_t pin, uint32_t mode, uint32_t pull, uint32_t speed, uint32_t alternate, GPIO_TypeDef *port, bool pinInverted);
        ~GPIO_stm32() = default;
        void init();
        uint32_t getPull() const;
        uint32_t getSpeed() const;
        uint32_t getAlternate() const;
        GPIO_TypeDef* getPort() const;
};

#ifdef __cplusplus
}
#endif /* END cpluscplus */

#endif /* GPIO_STM32_H_ */
