/*
 * CANNode.cpp
 *
 *  Created on: Dec 6, 2023
 *      Author: michael.grathwohl
 */

#include "CANopenNode.h"

#include "CANopen.h"
#include "OD.h"
#include "CiA417_LiftTypes.h"
#include "CiA417_VirtualIOMapping.h"
#include "globals.h"
static virtualIOMapping_data_t test;
SINGLETON_DEFINE(CANopenNode)
CANopenNode::CANopenNode()
{
	// TODO Auto-generated constructor stub
	_canOpenNodeParameter.desiredNodeID = DEFAULT_CAN_NODE_ID;
	_canOpenNodeParameter.activeNodeID = 0;
	_canOpenNodeParameter.baudrate = libCOL_BAUD_250k;
	_canOpenNodeParameter.timerHandle = nullptr;
	_canOpenNodeParameter.timerCall_in_us = DEFAULT_CAN_TIMERIRQ_IN_US;
	_canOpenNodeParameter.CANHandle = nullptr;
	_canOpenNodeParameter.HWInitFunction = nullptr;
	_canOpenNodeParameter.outStatusLEDGreen = 0;
	_canOpenNodeParameter.outStatusLEDRed = 0;
	_canOpenNodeParameter.canOpenStack = nullptr;

}

void CANopenNode::setCANNodeParameter(CAN_HandleTypeDef *hcan, TIM_HandleTypeDef* htim, void (*CANhwInit)(uint16_t baud))
{
	_canOpenNodeParameter.CANHandle = hcan;
	_canOpenNodeParameter.timerHandle = htim;
	_canOpenNodeParameter.HWInitFunction = CANhwInit;
}

bool CANopenNode::initNode()
{
	assert(_canOpenNodeParameter.CANHandle != nullptr);
	assert(_canOpenNodeParameter.timerHandle != nullptr);
	assert(_canOpenNodeParameter.HWInitFunction != nullptr);

	int16_t error = canopen_app_init(&_canOpenNodeParameter);
	if(error != CO_ERROR_NO || _canOpenNodeParameter.desiredNodeID != _canOpenNodeParameter.activeNodeID)
	{//init failed
		setLastError(1);
		setinitState(0);
	}
	else
	{// init succesful
		setinitState(1);
		setCallbackFunctions();
	}
	return isNodeInitOk();
}

bool CANopenNode::isNodeInitOk()
{
	if(_initState == 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void CANopenNode::setinitState(uint8_t val)
{
	_initState = val;
}

uint32_t CANopenNode::getLastError()
{
	return _error;
}

void CANopenNode::setLastError(uint32_t val)
{
	_error = val;
}

CAN_HandleTypeDef* CANopenNode::getCANHandler()
{
	return _canOpenNodeParameter.CANHandle;
}

TIM_HandleTypeDef* CANopenNode::getTimerHandler()
{
	return _canOpenNodeParameter.timerHandle;
}

void CANopenNode::setCallbackFunctions()
{
	CO_RPDO_initCallbackPre(_canOpenNodeParameter.canOpenStack->RPDO, OD_ENTRY_H6011_virtualOutputMapping, static_callbackPdoVirtOMapData);
	CO_SDOserver_initCallbackPre(_canOpenNodeParameter.canOpenStack->SDOserver, OD_ENTRY_H6011_virtualOutputMapping, static_callbackSdoVirtOMapData);

	uint8_t tmp = libCOL_lift1;
	OD_set_value(OD_ENTRY_H6001_liftNumber, 0, &tmp, sizeof(uint8_t), true);
	tmp = libCOL_Floor_NotUsed;
	OD_set_value(OD_ENTRY_H6002_floorNumber, 0, &tmp, sizeof(uint8_t), true);
	tmp = libCOL_door1 | libCOL_door2 | libCOL_door3 | libCOL_door4;
	OD_set_value(OD_ENTRY_H6003_carDoorNumber, 0, &tmp, sizeof(uint8_t), true);
}

void CANopenNode::process()
{
	if(canopen_app_process())
	{	
		//todo: logic
		switch(CO_NMT_getInternalState(_canOpenNodeParameter.canOpenStack->NMT))
		{
		case CO_NMT_PRE_OPERATIONAL:
		
			break;
		case CO_NMT_OPERATIONAL:
			//IOHandler::instance().ProcessIO();
			//sendInputs();
			//pollRecvOutputs();

			//triggerPDOsend();
			//pdoTest();
			break;
		case CO_NMT_STOPPED:
			break;
		default://CO_NMT_UNKNOWN
			break;
		}
	}

	switch(_canOpenNodeParameter.canOpenStack->CANmodule->CANerrorStatus)
	{
	case CO_ERROR_NO:
		break;
	case CO_CAN_ERR_WARN_PASSIVE:
		break;
	default:
		break;
	}
}

void CANopenNode::timeHandler()
{
	if(isNodeInitOk())
	{
		canopen_app_interrupt();
	}
}

void CANopenNode::errorHandler()
{
	if(isNodeInitOk())
	{
		if(_canOpenNodeParameter.CANHandle->ErrorCode != HAL_CAN_ERROR_NONE)
		{
			switch(_canOpenNodeParameter.CANHandle->ErrorCode)
			{
			case HAL_CAN_ERROR_EWG:
			case HAL_CAN_ERROR_EPV:
			case HAL_CAN_ERROR_BOF:
			case HAL_CAN_ERROR_STF:
			case HAL_CAN_ERROR_FOR:
			case HAL_CAN_ERROR_ACK:
			case HAL_CAN_ERROR_BR:
			case HAL_CAN_ERROR_BD:
			case HAL_CAN_ERROR_CRC:
			case HAL_CAN_ERROR_RX_FOV0:
			case HAL_CAN_ERROR_RX_FOV1:
			case HAL_CAN_ERROR_TX_ALST0:
			case HAL_CAN_ERROR_TX_TERR0:
			case HAL_CAN_ERROR_TX_ALST1:
			case HAL_CAN_ERROR_TX_TERR1:
			case HAL_CAN_ERROR_TX_ALST2:
			case HAL_CAN_ERROR_TX_TERR2:
			case HAL_CAN_ERROR_TIMEOUT:
			case HAL_CAN_ERROR_NOT_INITIALIZED:
			case HAL_CAN_ERROR_NOT_READY:
			case HAL_CAN_ERROR_NOT_STARTED:
			case HAL_CAN_ERROR_PARAM:
			default:
				break;
			}

			//todo
			//canopen_app_resetCommunication();
		}
	}
}

void CANopenNode::pdoTest()
{
	/*
	 * Object Dictionary anpassen
	 * 0x1400:01 von 0x200 auf 0x400 bis 0x4xx erweitern (0x1400 dementsprechend auch neue Indexe anlegen)
	 * 0x1800:01 von 0x180 auf 0x480 ändern
	 *
	 * momentaner Test (response on change):
	 * Master send		ID: 0x211 Data: 0x05 03 01 00 FF 01
	 * Master receive	ID: 0x191 Data: 0x05 03 01 00 FF 01
	 * */

}

void CANopenNode::triggerPDOsend()
{
	_canOpenNodeParameter.canOpenStack->TPDO[0].sendRequest = 1;
}

bool CANopenNode::isLEDGreenOn()
{
	/*
	 * CANopen green led - run led:
	 * - flickering: 	LSS configuration state is active
	 * - blinking: 		device is in NMT pre-operational state
	 * - single flash: 	device is in NMT stopped state
	 * - triple flash: 	a software download is running in the device
	 * - on: 			device is in NMT operational state
	*/
	if(_canOpenNodeParameter.outStatusLEDGreen != 0)
	{
		return true;
	}
	return false;
}

bool CANopenNode::isLEDRedOn()
{
	/*
	 * CANopen red led - error led:
	 * - off: 			no error
	 * - flickering:	LSS node id is not configured, CANopen is not initialized
	 * - blinking:		invalid configuration, general error
	 * - single flash: 	CAN warning limit reached
	 * - double flash: 	heartbeat consumer - error in remote monitored node
	 * - triple flash: 	sync message reception timeout
	 * - quadruple flash: PDO has not been received before the event timer elapsed
	 * - on: 			CAN bus off
	*/
	if(_canOpenNodeParameter.outStatusLEDRed != 0)
	{
		return true;
	}
	return false;
}

virtualIOMapping_data_t CANopenNode::getODInputFunctionMapping(uint8_t PinNr)
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

virtualIOMapping_data_t CANopenNode::getODOutputFunctionMapping(uint8_t PinNr)
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

virtualIOMapping_data_t* CANopenNode::getAddressODInputFunctionMapping(uint8_t PinNr)
{
	virtualIOMapping_data_t *tmp = nullptr;
	uint8_t subindex = PinNr+1;

	if(PinNr <= OD_CNT_ARR_6100)
	{
		tmp = (virtualIOMapping_data_t*)OD_getPtr(OD_ENTRY_H6100_inputGroup1, subindex, sizeof(virtualIOMapping_data_t), NULL);
	}

	return tmp;
}

virtualIOMapping_data_t* CANopenNode::getAddressODOutputFunctionMapping(uint8_t PinNr)
{
	virtualIOMapping_data_t *tmp = nullptr;
	uint8_t subindex = PinNr+1;

	if(PinNr <= OD_CNT_ARR_6200)
	{
		tmp = (virtualIOMapping_data_t*)OD_getPtr(OD_ENTRY_H6200_outputGroup1, subindex, sizeof(virtualIOMapping_data_t), NULL);
	}

	return tmp;
}

void CANopenNode::sendInputs()
{
	virtualIOMapping_data_t data;
	while(fifo_sendFunctionMapping.read(data))
	{
		if(OD_set_value(OD_ENTRY_H6010_virtualInputMapping, 0, &data, sizeof(virtualIOMapping_data_t), true) == ODR_OK)
		{
			triggerPDOsend();
		}
	}
}

void CANopenNode::pollRecvOutputs()
{
	virtualIOMapping_data_t data;
//	while(fifo_recvFunctionMapping.read(data))
//	{
	if(OD_get_value(OD_ENTRY_H6011_virtualOutputMapping, 0, &data, sizeof(virtualIOMapping_data_t), true) == ODR_OK)
	{
		test =data;
		adoptVirtOMapData(data);

	}
}

void CANopenNode::static_callbackPdoVirtOMapData(void *object)
{
	CANopenNode::instance().callbackPdoVirtOMapData(object);
}

void CANopenNode::static_callbackSdoVirtOMapData(void *object)
{
	CANopenNode::instance().callbackSdoVirtOMapData(object);
}

void CANopenNode::callbackPdoVirtOMapData(void *object)
{
	assert(object != nullptr);

	//callback Function is called before data is copied to object
	//to do
	//RPDO->CANrxNew[0 oder 1] , 1 bei z.B. sync
	adoptVirtOMapData(*reinterpret_cast<virtualIOMapping_data_t *>(_canOpenNodeParameter.canOpenStack->RPDO->CANrxData));
}

void CANopenNode::callbackSdoVirtOMapData(void *object)
{
	assert(object != nullptr);

	adoptVirtOMapData(*reinterpret_cast<virtualIOMapping_data_t *>(_canOpenNodeParameter.canOpenStack->SDOserver->CANrxData));
}

void CANopenNode::adoptVirtOMapData(virtualIOMapping_data_t &data)
{
	_virtOMapData.set_virtualIOMapping(data);

	if(_virtOMapData != _oldVirtOMapData
		&& _CiA417Gateway.isLiftValid(_virtOMapData.get_virtualIOMapping().lift)
		&& _CiA417Gateway.isDoorValid(_virtOMapData.get_virtualIOMapping().door)
		&& _CiA417Gateway.isFloorValid(_virtOMapData.get_virtualIOMapping().floor)
	)
	{
		fifo_recvFunctionMapping.write(data);
		_oldVirtOMapData = _virtOMapData;
	}
}

/*
 * EOF
 */
