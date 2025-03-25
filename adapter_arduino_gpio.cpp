/*
 * adapter_arduino_gpio.cpp
 *
 *  Created on: Mar 6, 2025
 *      Author: jan.kristel
 */


#include "adapter_arduino_gpio.hpp"

AdapterArduinoGPIO :: ~AdapterArduinoGPIO(){}

void  AdapterArduinoGPIO :: config(uint16_t pin, int mode, int pull, int speed) {
	int arduinoMode;

	if (mode == 0) {
		arduinoMode = INPUT;
	} else {
		arduinoMode = OUTPUT;
	}

	if (pull == 1) {
		arduinoMode = INPUT_PULLUP;
	}

	pinMode(pin, arduinoMode);
}




