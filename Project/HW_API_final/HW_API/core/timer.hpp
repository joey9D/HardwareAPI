/*
 * timer.hpp
 *
 *  Created on: Jul 7, 2025
 *      Author: jan.kristel
 */

#ifndef SYS_CLOCK_TIMER_HPP_
#define SYS_CLOCK_TIMER_HPP_

#include "hw_interface.hpp"
#include <cstdint>

// Only include HAL headers if we're on STM32 platform
#ifdef STM32_PLATFORM
#include "../drivers/stm32_hal_wrapper/common/stm32_hal_inc.hpp"

#ifdef __cplusplus

class Timer
{
public:
	void startTime(uint32_t ms)
	{
		_waitTime_ms = ms;
		_startTime = HAL_GetTick();
	}

	void stopTime()
	{
		_waitTime_ms = 0;
	}

	void resetTime()
	{
		_startTime = HAL_GetTick();
	}

	bool isTimeExpired()
	{
		bool retval = false;
		uint32_t diffTime = getCurrentDiffTime();

		if((_waitTime_ms > 0) && (diffTime > _waitTime_ms))
		{
			stopTime();
			retval = true;
			_diffTime_ms = diffTime;
		}
		return retval;
	}

	uint32_t getCurrentDiffTime()
	{
		return (HAL_GetTick() - _startTime);
	}

	uint32_t getExpiredDiffTime() const
	{
		return _diffTime_ms;
	}

private:
	uint32_t _startTime = 0;
	uint32_t _waitTime_ms = 0;
	uint32_t _diffTime_ms = 0;
};

#endif /* __cplusplus */

#endif /* STM32_PLATFORM */

#endif /* SYS_CLOCK_TIMER_HPP_ */
