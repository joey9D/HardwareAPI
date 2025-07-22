/*
 * gpio.hpp
 *
 *  Created on: Jul 11, 2025
 *      Author: jan.kristel
 */

#ifndef GPIO_GPIO_HPP_
#define GPIO_GPIO_HPP_

//#include "stm32c0xx_hal.h"

#include "hw_interface.hpp"
#include "timer.hpp"
#include "stm32c0_hw.hpp"

#ifdef __cplusplus

class Gpio
{
public:
	Gpio(PinConfig_t &config);
	// 		- init
	void gpio_init();
	void port_clock_enable(Port port) const;
	//		- functions
	bool readPin() const;
	void writePin(bool value) const;
	void togglePin() const;
//    virtual bool lockPin() const = 0;
	//		- getter
	uint16_t getPin() const;
//	virtual uint16_t getPinNumber() const;
//	virtual Port getPort() const;
	GPIO_TypeDef *get_GPIO_TypeDef_port() const;
	Mode getMode() const;
	Pull getPull() const;
	Speed getSpeed() const;
//	virtual Pin_State getPinState() const;
	//		- helper
	bool isPinOn() const;
	bool isDebouncePinOn();
	bool isPinInverted() const;
private:
	PinConfig_t _config;
};

#endif /* __cplusplus */
#endif /* GPIO_GPIO_HPP_ */
