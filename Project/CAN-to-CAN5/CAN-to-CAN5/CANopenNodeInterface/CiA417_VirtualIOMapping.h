/*
 * VirtualIOMapping.h
 *
 *  Created on: Jan 3, 2024
 *      Author: michael.grathwohl
 */

#ifndef CIA417_VIRTUALIOMAPPING_H_
#define CIA417_VIRTUALIOMAPPING_H_


#include "CiA417_LiftTypes.h"

class CiA417_virtualIOMapping
{
public:

	CiA417_virtualIOMapping() = default;
	virtual ~CiA417_virtualIOMapping() = default;

    bool operator==(const CiA417_virtualIOMapping &data) const
    {
    	if(this->virt_ioMapping.basicFunction == data.virt_ioMapping.basicFunction
    		&& this->virt_ioMapping.subFunction == data.virt_ioMapping.subFunction
			&& this->virt_ioMapping.lift == data.virt_ioMapping.lift
			&& this->virt_ioMapping.floor == data.virt_ioMapping.floor
			&& this->virt_ioMapping.door == data.virt_ioMapping.door
			&& this->virt_ioMapping.functionData == data.virt_ioMapping.functionData)
    	{
    		return true;
    	}
    	return false;
    }

    bool operator!=(const CiA417_virtualIOMapping &data) const
    {
    	if(this->virt_ioMapping.basicFunction != data.virt_ioMapping.basicFunction
			|| this->virt_ioMapping.subFunction != data.virt_ioMapping.subFunction
			|| this->virt_ioMapping.lift != data.virt_ioMapping.lift
			|| this->virt_ioMapping.floor != data.virt_ioMapping.floor
			|| this->virt_ioMapping.door != data.virt_ioMapping.door
			|| this->virt_ioMapping.functionData != data.virt_ioMapping.functionData)
		{
			return true;
		}
		return false;
    }

    void clear()
    {
    	this->virt_ioMapping.basicFunction = 0;
		this->virt_ioMapping.subFunction = 0;
		this->virt_ioMapping.lift = 0;
		this->virt_ioMapping.floor = 0;
		this->virt_ioMapping.door = 0;
		this->virt_ioMapping.functionData = 0;
    }

    bool isEmpty()
    {
    	if(this->virt_ioMapping.basicFunction != 0
			|| this->virt_ioMapping.subFunction != 0
			|| this->virt_ioMapping.lift != 0
			|| this->virt_ioMapping.floor != 0
			|| this->virt_ioMapping.door != 0
			|| this->virt_ioMapping.functionData != 0)
		{
			return false;
		}
		return true;
    }

    bool isEmptyExcludingData()
	{
		if(this->virt_ioMapping.basicFunction != 0
			|| this->virt_ioMapping.subFunction != 0
			|| this->virt_ioMapping.lift != 0
			|| this->virt_ioMapping.floor != 0
			|| this->virt_ioMapping.door != 0)
		{
			return false;
		}
		return true;
	}

    bool isEqualExcludingData(const virtualIOMapping_data_t& data)
	{
		if(this->virt_ioMapping.basicFunction == data.basicFunction
			&& this->virt_ioMapping.subFunction == data.subFunction
			&& this->virt_ioMapping.lift == data.lift
			&& this->virt_ioMapping.floor == data.floor
			&& this->virt_ioMapping.door == data.door)
		{
			return true;
		}
		return false;
	}

    uint32_t size()
    {
    	return sizeof(virtualIOMapping_data_t);
    }

    const virtualIOMapping_data_t & get_virtualIOMapping() const { return this->virt_ioMapping; }
    virtualIOMapping_data_t & get_mutable_virtualIOMapping() { return this->virt_ioMapping; }
    void set_virtualIOMapping(const virtualIOMapping_data_t & value) { this->virt_ioMapping = value; }

private:

    virtualIOMapping_data_t virt_ioMapping;
};


#endif /* CIA417_VIRTUALIOMAPPING_H_ */
