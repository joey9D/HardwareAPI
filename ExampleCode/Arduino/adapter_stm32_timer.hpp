/*
 * timer.hpp
 *
 *  Created on: Mar 6, 2025
 *      Author: jan.kristel
 */

#ifndef INC_ADAPTER_STM32_TIMER_HPP_
#define INC_ADAPTER_STM32_TIMER_HPP_

#include "adapter_base_timer.hpp"


class TimerSTM32 {
private:
	uint32_t _lastTime;
public:
	TimerSTM32(uint32_t debounceTime);
	~TimerSTM32();
	void startTime(uint32_t getCurrentTime()) override;
	void stopTime() override;
	bool isTimeExpired() const override;
	uint32_t getCurrentTime() const override;
	bool isDebouncePinOn() const override;
};



#endif /* INC_ADAPTER_STM32_TIMER_HPP_ */
