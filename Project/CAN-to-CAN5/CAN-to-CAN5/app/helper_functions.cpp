#include "helper_functions.h"

// void CANopenNode::triggerPDOsend()
// {
// 	_hardware->getTPDOsend(); // Trigger the TPDO send
// }

virtualIOMapping_data_t HelperFunctions::getODInputFunctionMapping(uint8_t PinNr)
{
	virtualIOMapping_data_t tmp;
	virtualIOMapping_data_t *p_temp;

	p_temp = getAddressODInputFunctionMapping(PinNr);
	if(p_temp != nullptr)
	{
		tmp = *p_temp;
	}

	return tmp;
}

virtualIOMapping_data_t HelperFunctions::getODOutputFunctionMapping(uint8_t PinNr)
{
	virtualIOMapping_data_t tmp;
	virtualIOMapping_data_t *p_temp;

	p_temp = getAddressODOutputFunctionMapping(PinNr);
	if(p_temp != nullptr)
	{
		tmp = *p_temp;
	}

	return tmp;
}


virtualIOMapping_data_t* HelperFunctions::getAddressODInputFunctionMapping(uint8_t PinNr)
{
	virtualIOMapping_data_t *tmp = nullptr;
	uint8_t subindex = PinNr+1;

	if(PinNr <= OD_CNT_ARR_6100)
	{
		tmp = (virtualIOMapping_data_t*)OD_getPtr(OD_ENTRY_H6100_inputGroup1, subindex, sizeof(virtualIOMapping_data_t), NULL);
	}

	return tmp;
}

virtualIOMapping_data_t* HelperFunctions::getAddressODOutputFunctionMapping(uint8_t PinNr)
{
	virtualIOMapping_data_t *tmp = nullptr;
	uint8_t subindex = PinNr+1;

	if(PinNr <= OD_CNT_ARR_6200)
	{
		tmp = (virtualIOMapping_data_t*)OD_getPtr(OD_ENTRY_H6200_outputGroup1, subindex, sizeof(virtualIOMapping_data_t), NULL);
	}

	return tmp;
}

void HelperFunctions::sendInputs()
{
	virtualIOMapping_data_t data;
	while(fifo_sendFunctionMapping.read(data))
	{
		if(OD_set_value(OD_ENTRY_H6010_virtualInputMapping, 0, &data, sizeof(virtualIOMapping_data_t), true) == ODR_OK)
		{
			//triggerPDOsend();
		}
	}
}

void HelperFunctions::pollRecvOutputs()
{
	virtualIOMapping_data_t data;
	while(fifo_recvFunctionMapping.read(data))
	{
	if(OD_get_value(OD_ENTRY_H6011_virtualOutputMapping, 0, &data, sizeof(virtualIOMapping_data_t), true) == ODR_OK)
	{
		test =data;
		adoptVirtOMapData(data);

	}
}
}

void HelperFunctions::static_callbackPdoVirtOMapData(void *object)
{
	if(object != nullptr) {
		static_cast<HelperFunctions*>(object)->callbackPdoVirtOMapData(object);
	}
}

void HelperFunctions::static_callbackSdoVirtOMapData(void *object)
{
	if(object != nullptr) {
		static_cast<HelperFunctions*>(object)->callbackSdoVirtOMapData(object);
	}
}

void HelperFunctions::callbackPdoVirtOMapData(void *object)
{
	assert(object != nullptr);

	//callback Function is called before data is copied to object
	//to do
	//RPDO->CANrxNew[0 oder 1] , 1 bei z.B. sync
	adoptVirtOMapData(*reinterpret_cast<virtualIOMapping_data_t *>(CO->RPDO->CANrxData));
}

void HelperFunctions::callbackSdoVirtOMapData(void *object)
{
	assert(object != nullptr);

	adoptVirtOMapData(*reinterpret_cast<virtualIOMapping_data_t *>(CO->SDOserver->CANrxData));
}

void HelperFunctions::adoptVirtOMapData(virtualIOMapping_data_t &data)
{
	_virtOMapData.set_virtualIOMapping(data);

	if(_virtOMapData != _oldVirtOMapData
		&& _CiA417Gateway.isLiftValid(_virtOMapData.get_virtualIOMapping().lift)
		&& _CiA417Gateway.isDoorValid(_virtOMapData.get_virtualIOMapping().door)
		&& _CiA417Gateway.isFloorValid(_virtOMapData.get_virtualIOMapping().floor)
	)
	{
		//_pdoSdo.QueueRPDO(data);
		_oldVirtOMapData = _virtOMapData;
	}
}

void HelperFunctions::writeInputMappingToOD(uint8_t index, const libCOL_input_t& input) 
{

	const uint16_t odIndex = index+1; // Adjust for 1-based indexing in OD
    virtualIOMapping_data_t mapping = getODInputFunctionMapping(index);
    mapping.functionData = input.functionData.raw;
	OD_set_value(OD_ENTRY_H6100_inputGroup1, odIndex, &mapping, sizeof(virtualIOMapping_data_t), true);
    

 }

/*
 * EOF
 */
