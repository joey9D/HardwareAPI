/*
 * gpio.hpp
 *
 *  Created on: Jul 11, 2025
 *      Author: jan.kristel
 */

#ifndef GPIO_GPIO_STM32_HPP_
#define GPIO_GPIO_STM32_HPP_

//#include "stm32c0xx_hal.h"

//#include "hw_interface.hpp"
#include "gpio_interface.hpp"
#include "timer.hpp"
#include "stm32c0_hw.hpp"
// #include "hw_enum_classes.hpp"

#ifdef __cplusplus

class Gpio : public IGpio
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
	void gpio_init() override;
	void port_clock_enable(Port port) const override;
	//		- functions
	bool readPin() const override;
	void writePin(bool value) const override;
	void togglePin() const override;
//    virtual bool lockPin() const = 0;
	//		- getter
	uint16_t getPin() const override;
//	virtual uint16_t getPinNumber() const;
//	virtual Port getPort() const;
	GPIO_TypeDef *get_GPIO_TypeDef_port() const;
	Mode getMode() const override;
	Pull getPull() const override;
	Speed getSpeed() const override;
//	virtual Pin_State getPinState() const;
	//		- helper
	bool isPinOn() const override;
	bool isDebouncePinOn() override;
	bool isPinInverted() const override;
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
#endif /* GPIO_GPIO_STM32_HPP_ */
