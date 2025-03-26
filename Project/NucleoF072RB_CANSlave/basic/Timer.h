/*
 * Timer.h
 *
 *  Created on: Sep 22, 2023
 *      Author: michael.grathwohl
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <cstdint>
#include "Hardware_Factory_STM32.h" // Include the hardware factory header


class Timer
{
public:
	Timer()
	: _hardware( HardwareFactory::Create()) {}
	//Timer() = default;
	virtual ~Timer() = default;

	void startTime(const uint32_t ms)
	{
		_waitTime_ms = ms;
		_startTime = _hardware->GetTick();
	};

	void stopTime() { _waitTime_ms = 0; }
	void resetTime() { _startTime = _hardware->GetTick(); }// Use abstraction layer

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
	};

	uint32_t getCurrentDiffTime() { return (_hardware->GetTick() - _startTime); }// Use abstraction layer
	const uint32_t & getExpiredDiffTime() const { return _diffTime_ms; }

private:
	HardwareInterface* _hardware; // Reference to abstraction

	uint32_t _startTime = 0;
	uint32_t _waitTime_ms = 0;
	uint32_t _diffTime_ms = 0;
};

#endif /* TIMER_H_ */
