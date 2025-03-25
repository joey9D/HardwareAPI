/*
 * adapter_stm32g071xx_gpio.hpp
 *
 *  Created on: Mar 5, 2025
 *      Author: jan.kristel
 */

#ifndef INC_ADAPTER_STM32_GPIO_HPP_
#define INC_ADAPTER_STM32_GPIO_HPP_

#include "stm32g0xx_hal.h"
#include "adapter_base_gpio.hpp"

/**
 * @brief Adaptation class to provide HAL gpio function compatibility.
 */
class AdapterSTM32GPIO : public AdapterBaseGPIO {
private:
	int _pull;
	int _speed;
	GPIO_TypeDef *_port = nullptr;
	// for write
	bool _pinState = true;

public:
	AdapterSTM32GPIO(uint16_t pin, GPIO_TypeDef* port, int pull, int speed, bool invertedPin = false);
	~AdapterSTM32GPIO();
	uint16_t getPin() const override;
	int getPull() const;
	int getSpeed() const;
	bool isPinOn() const;
	GPIO_TypeDef *getPort() const override;

	bool isPinInverted() const override;
	void config() override;
	void write(bool onState) override;
	bool read(uint16_t pin) const override;
	void toggle(uint16_t pin) override;
};


#endif /* INC_ADAPTER_STM32_GPIO_HPP_ */
