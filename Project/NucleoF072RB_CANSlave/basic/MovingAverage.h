/*
 * MovingAverage.h
 *
 *  Created on: May 3, 2024
 *      Author: michael.grathwohl
 */

#ifndef MOVINGAVERAGE_H_
#define MOVINGAVERAGE_H_

#include <cstdint>
#include <array>

template <typename T, const uint16_t _len>
class SimpleMovingAverage
{

public:
	// constructor
	SimpleMovingAverage()
	{}

	// function to add new data in the list
	void addData(T num)
	{
		uint16_t newWrIdx = _writeIdx;
		++newWrIdx;
		if(newWrIdx >= _len)
		{
			newWrIdx = 0;
		}
		_array.at(newWrIdx) = num;
		_writeIdx = newWrIdx;

	}

	// function to calculate mean
	uint32_t getMean()
	{
		uint32_t temp_sum = 0;
		for(uint16_t i=0; i<_len; i++)
		{
			temp_sum += _array.at(i);
		}
		return (temp_sum / _len);
	}

private:
	std::array<T, _len> _array{};
	uint16_t _writeIdx;
};


#endif /* MOVINGAVERAGE_H_ */
