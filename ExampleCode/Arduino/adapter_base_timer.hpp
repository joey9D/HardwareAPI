/*
 * timer_base.hpp
 *
 *  Created on: Mar 7, 2025
 *      Author: jan.kristel
 */

#ifndef INC_ADAPTER_BASE_TIMER_HPP_
#define INC_ADAPTER_BASE_TIMER_HPP_

#include <cstdint>
// include the correct stm32xxxx_hal.h file with conditional compilation
#include "mcu_mapping.hpp"

class TimerBase {
private:
	uint32_t _debounceTime = 0;
	uint32_t _debounceStart;
	uint32_t _debounceEnd;
	uint8_t _debounceState;

public:
	virtual TimerBase(uint32_t debounceTime);
	virtual ~TimerBase() = default;
	virtual void startTime() = 0;
	virtual void stopTime() = 0;
	virtual bool isTimeExpired() const = 0;
	virtual uint32_t getCurrentTime() const;
	virtual bool isDebouncePinOn() const;
};


#endif /* INC_ADAPTER_BASE_TIMER_HPP_ */
