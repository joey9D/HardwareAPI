/*
 * adapter_arduino_gpio.hpp
 *
 *  Created on: Mar 6, 2025
 *      Author: jan.kristel
 */

#ifndef INC_ADAPTER_ARDUINO_GPIO_HPP_
#define INC_ADAPTER_ARDUINO_GPIO_HPP_

#include "adapter_base_gpio.hpp"

/**
 * @brief Adaptation class to provide arduino gpio function compatibility.
 */
class AdapterArduinoGPIO : public AdapterBaseGPIO {
private:
	uint8_t _port;

public:
	~AdapterArduinoGPIO()= default;
	uint8_t getPort() const override;
	void config(uint16_t pin, int mode, int pull, int speed) override;
	void write(uint16_t pin, bool value) override;
	void read(uint16_t pin) const override;
	void toggle(uint16_t pin) override;
};


#endif /* INC_ADAPTER_ARDUINO_GPIO_HPP_ */
