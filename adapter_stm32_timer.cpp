/*
 * timer_stm32.cpp
 *
 *  Created on: Mar 7, 2025
 *      Author: jan.kristel
 */

#include "adapter_stm32_timer.hpp"
#include "adapter_stm32_gpio.hpp"

bool AdapterSTM32GPIO::read();

TimerSTM32 :: TimerSTM32(uint32_t debounceTime){
	_debounceTime = debounceTime;
}

TimerSTM32 :: ~TimerSTM32(){}

void TimerSTM32 :: startTime(){
	_debounceStart = getCurrentTime();
} /* END STARTTIME */

void TimerSTM32 :: stopTime(){
	_debounceEnd = getCurrentTime();
} /* END STOPTIME */

bool TimerSTM32 :: isTimeExpired(){
	if (_debounceEnd - _debounceStart > _debounceTime) {
		return 1;
	}
} /* END ISTIMEEXPIRED */

uint32_t TimerSTM32 :: getCurrentTime() {
	return HAL_GetTick();
} /* END GETCURRENTTIME */

bool TimerSTM32 :: isDebouncePinOn() const {
	bool retvalue = false;
	if (_debounceTime != 0 ) {
		switch (_debounceState) {
		case 0:
			if (isPinOn()) {
				startTime();
				_debounceState = 1;
			}
			break;
		case 1:
			if (isTimeExpired()) {
				_debounceState = 2;
			}
			break;
		case 2:
			retvalue = true;
			if (!isPinOn) {
				startTime(_debounceTime);
				_debounceState = 3;
			}
			break;
		case 3:
			retvalue = true;
			if (!isPinOn()) {
				if (isTimeExpired()) {
					_debounceState = 0;
				}
			} else {
				stopTime();
				_debounceState = 2;
			}
			break;
		default:
			_debounceState = 0;
			break;
		}
	} else {
		retvalue = read();
	}

	return retvalue;
} /* END ISDEBOUNCEPINON */
