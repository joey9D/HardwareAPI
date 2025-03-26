/*
 * GPIObase.h
 *
 *  Created on: Mar 25, 2025
 *      Author: jan.kristel
 */

#ifndef GPIO_BASE_H_
#define GPIO_BASE_H_


#include <stdint.h>
#include <string.h>
#include <stdbool.h>

class GPIO_base {
	private:
    	uint32_t _pin;
    	uint32_t _mode;
    	bool _pinInverted = false;
	public:
    	GPIO_base(uint32_t pin, uint32_t mode, bool pinInverted);
    	~GPIO_base();

    	uint32_t getPin() const;
    	uint32_t getMode() const;
    	bool isPinInverted() const;
};


#endif /* GPIO_BASE_H_ */
