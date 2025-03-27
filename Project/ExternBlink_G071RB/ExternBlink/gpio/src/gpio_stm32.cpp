/*
 * gPIO_stm32.cpp
 *
 *  Created on: Mar 25, 2025
 *      Author: jan.kristel
 */


#include "gpio_stm32.h"
#include "main.h"
#include "stm32g0xx_hal_gpio.h"

GPIO_stm32::GPIO_stm32(uint32_t pin,
		uint32_t mode,
		uint32_t pull,
		uint32_t speed,
		uint32_t alternate,
		GPIO_TypeDef *port,
		bool pinInverted)
    : GPIO_base(pin, mode, pinInverted),
	  _pull(pull),
	  _speed(speed),
	  _alternate(alternate),
	  _port(port) {}

void GPIO_stm32::init()
{
    GPIO_InitTypeDef gpio_initStruct = {0};

    __HAL_RCC_GPIOC_CLK_ENABLE();

#ifdef GPIOA
    __HAL_RCC_GPIOA_CLK_ENABLE();
#elif defined(GPIOB)
    __HAL_RCC_GPIOB_CLK_ENABLE();
#elif defined(GPIOD)
    __HAL_RCC_GPIOD_CLK_ENABLE();
#elif defined(GPIOE)
    __HAL_RCC_GPIOE_CLK_ENABLE();
#elif defined(GPIOF)
    __HAL_RCC_GPIOF_CLK_ENABLE();
#endif

    HAL_GPIO_WritePin(GPIOA, LED_GREEN_Pin|LED_Extern_Pin, GPIO_PIN_RESET);

    gpio_initStruct.Pin = getPin();
    gpio_initStruct.Mode = getMode();
    gpio_initStruct.Pull = getPull();
    gpio_initStruct.Speed = getSpeed();
    gpio_initStruct.Alternate = getAlternate();
    HAL_GPIO_Init(getPort(), &gpio_initStruct);
}

uint32_t GPIO_stm32::getPull() const
{
    return _pull;
}

uint32_t GPIO_stm32::getSpeed() const
{
    return _speed;
}

uint32_t GPIO_stm32::getAlternate() const
{
    return _alternate;
}

GPIO_TypeDef* GPIO_stm32::getPort() const
{
    return _port;
}
