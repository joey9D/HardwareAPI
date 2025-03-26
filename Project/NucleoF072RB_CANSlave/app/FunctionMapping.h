/*
 * FunctionMapping.h
 *
 *  Created on: Dec 18, 2023
 *      Author: michael.grathwohl
 */

#ifndef FUNCTIONMAPPING_H_
#define FUNCTIONMAPPING_H_

#include <array>
#include "Cia417_VirtualIOMapping.h"
#include "IOHandler.h"

template <typename _IOclass, uint8_t _len>
class FunctionMapping
{
public:
	FunctionMapping() = default;
	virtual ~FunctionMapping() = default;

	void setPinToMap(_IOclass &gpio)
	{
		if(_GpioCnt < _len)
		{
			_MapTable[_GpioCnt].gpio = &gpio;
			++_GpioCnt;
		}
	};

	void setFunctionToPin(uint8_t number, virtualIOMapping_data_t MappingFunction)
	{
		if(number < getPinCount())
		{
			_MapTable[number].MappingFunction = MappingFunction;
		}
	}

	void setFunctionToPin(uint8_t number, virtualIOMapping_data_t MappingFunction, uint8_t priority)
	{
		if(number < getPinCount())
		{
			_MapTable[number].MappingFunction = MappingFunction;
			_MapTable[number].prio = priority;
		}
	}

	uint8_t getPinCount()
	{
		return _GpioCnt;
	}

	_IOclass* getGpio(uint8_t number)
	{
		_IOclass* retval = nullptr;
		if(number < getPinCount())
		{
			retval = _MapTable[number].gpio;
		}
		return retval;
	}

	virtualIOMapping_data_t getPinMapping(uint8_t number)
	{
		virtualIOMapping_data_t tmp;
		if(number < getPinCount())
		{
			tmp = _MapTable[number].MappingFunction;
		}
		return tmp;
	}

private:
	typedef struct
	{
		_IOclass* gpio = nullptr;
		virtualIOMapping_data_t MappingFunction;
		uint8_t prio = 0;
	}mapping_t;

	uint8_t _GpioCnt = 0;
	std::array<mapping_t, _len> _MapTable;

};

#endif /* FUNCTIONMAPPING_H_ */
