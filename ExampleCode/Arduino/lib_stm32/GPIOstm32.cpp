#include "GPIOstm32.h"

GPIOstm32::GPIOstm32(uint32_t pin, uint32_t mode, GPIO_TypeDef *port, bool pinInverted) 
    : GPIObase(pin, mode, pinInverted), _port(port) 
{

}

static void GPIOstm32::init() {
    GPIO_InitTypeDef gpio_initStruct = {0};
    gpio_initStruct.Pin = getPin();
    gpio_initStruct.Mode = getMode();
    // gpio_initStruct.Pull = getPull();
    // gpio_initStruct.Speed = getSpeed();
    // gpio_initStruct.Alternate = getAlternate();
    HAL_GPIO_Init(getPort(), &gpio_initStruct); 
}

uint32_t GPIOstm32::getPull() const {
    return _pull;
}

uint32_t GPIOstm32::getSpeed() const {
    return _speed;
}

uint32_t GPIOstm32::getAlternate() const {
    return _alternate;
}

GPIO_TypeDef GPIOstm32::*getPort() const {
    return _port;
}