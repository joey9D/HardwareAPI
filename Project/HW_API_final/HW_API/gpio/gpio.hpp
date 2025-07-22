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
	Gpio(
		uint16_t pin,
		Port port,
		Mode mode,
		Pull pull,
		Speed speed,
		bool inverted,
		uint32_t debounceTime,
		uint8_t debounceState,
		ExtiTrigger extiTrigger
	);
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
	uint16_t _pin;
	Port _port;
	Mode _mode;
	Pull _pull;
	Speed _speed;
	bool _inverted;
	uint32_t _debounceTime;
	uint8_t _debounceState;
	Timer debounceTimer;
	ExtiTrigger _extiTrigger;
};

#endif /* __cplusplus */
#endif /* GPIO_GPIO_HPP_ */
