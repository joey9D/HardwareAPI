/*
 * adapter_base_gpio.hpp
 *
 *  Created on: Mar 5, 2025
 *      Author: jan.kristel
 */

#ifndef INC_ADAPTER_BASE_GPIO_HPP_
#define INC_ADAPTER_BASE_GPIO_HPP_


#include <cstdint>
#include <assert.h>
#include <Arduino.h> // for usage in arduinoIDE


/**
 * @brief Base adapter class for GPIO adaptation for different mcu.
 */
class AdapterBaseGPIO {
private:
	uint16_t _pin;
	int _mode;
	bool _invertedPin = false;
	// for write
	bool _oldPinState = true;

public:
	AdapterBaseGPIO(uint16_t pin, int mode, bool inverted = false) {
		assert(port != NULL);
		_pin = pin;
		_mode = mode;
		_invertedPin = invertedPin;
	}
	/**
	 * @brief Destructor
	 */
	virtual ~AdapterBaseGPIO() = default;

	/**
	 * @brief Getter methods for the base attributes.
	 */
	virtual uint16_t getPin() const = 0;
	virtual int getMode() const = 0;
	virtual int getPull() const = 0;
	virtual int getSpeed() const = 0;
	virtual void* getPort() const = 0;
	virtual bool isPinInverted() const = 0;

	/**
	 * @brief 		Configuration of GPIO-Pin.
	 */
	virtual void config() = 0;

	/**
	 * @brief 		Set pin to High or Low.
	 *
	 * @param pin   Pin to be set/unset.
	 * @param value High=true Low=false.
	 */
	virtual void write(bool onState) = 0;

	/**
	 * @brief 		Read the specific input port.
	 *
	 * @param pin	Specifies the pin to be read.
	 * @return 		Input port pin value, High=true Low=false.
	 */
	virtual bool read(uint16_t pin) const = 0;

	/**
	 * @brief 		Changes the pin state.
	 *
	 * @param pin 	Toggle the specified GPIO pin.
	 */
	virtual void toggle(uint16_t pin) = 0;

};


#endif /* INC_ADAPTER_BASE_GPIO_HPP_ */
