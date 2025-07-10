/*
 * CANNode.cpp
 *
 *  Created on: Dec 6, 2023
 *      Author: michael.grathwohl
 */

#include "CANopenNode.h"
#include "OD.h"
#include "CiA417_LiftTypes.h"
#include "CiA417_VirtualIOMapping.h"
#include "globals.h"


static virtualIOMapping_data_t test;
CANopenNode::CANopenNode(HardwareInterface* hardware)
	: hardware(hardware) // Initialize the hardware interface
{

}
	

bool CANopenNode::initNode()
{
	
	// Initialize the CANopenNodeSTM32 structure with default values
	assert(hardware != nullptr); // Ensure hardware interface is not null
	hardware->setHandles(17); // Set the hardware handles for CANopenNode , default ID is set to 17, can be changed later , can also be passed here.
	int16_t error = hardware->CANopen_Init(); // Initialize the CANopenNode
	if(error != CO_ERROR_NO || hardware->isIdValid() == false)
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

void CANopenNode::InitNodeStack()

{

	if(!initNode())
	{
		errorloop();
	}

}

void CANopenNode::errorloop()
{
	bool endless = true;
	while(endless)
	{//Eval Board zum test
		__NOP();
	}
	hardware->System_Reset(); // Reset the system if initialization fails
}

bool CANopenNode::isNodeInitOk()
{
	if(_initState == 0)
	{
		hardware->getstate(_initState);
		return false;
	}
	else
	{
		hardware->getstate(_initState);
		return true;
	}
}



HardwareInterface* CANopenNode::getHardwareInterface() 
{
    return hardware;
}

CiA417_CmdHandler& CANopenNode::getCiA417_CmdHandler()
{
	return _CmdHandlers;
}

void CANopenNode::initialize() 
{

	// static GPIOHandler gpioHandlerInstance; // Use a static instance to avoid dynamic allocation
    // _gpioHandler = &gpioHandlerInstance;

    // static PDO_SDO pdoSdoInstance;
    // _pdoSdo = &pdoSdoInstance;

    // static NMT_LED nmtLedInstance;
    // _nmtLed = &nmtLedInstance;
  
}

// PDO_SDO& CANopenNode::getPDO_SDO() {
//     return *_pdoSdo;
// }

// GPIOHandler& CANopenNode::getGPIOHandler() {
//     return *_gpioHandler;
// }

// NMT_LED& CANopenNode::getNMT_LED() {
//     return *_nmtLed;
// }


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

// CAN_HandleTypeDef* CANopenNode::getCANHandler() // remove and add to the abstraction layer
// {
// 	return _hardware->get;
// }

// TIM_HandleTypeDef* CANopenNode::getTimerHandler() // remove and add to the abstraction layer
// {
// 	return _canOpenNodeParameter.timerHandle;
// }

void CANopenNode::setCallbackFunctions()
{
	//CO_RPDO_initCallbackPre(_canOpenNodeParameter.canOpenStack->RPDO, OD_ENTRY_H6011_virtualOutputMapping, static_callbackPdoVirtOMapData);
	//CO_SDOserver_initCallbackPre(_canOpenNodeParameter.canOpenStack->SDOserver, OD_ENTRY_H6011_virtualOutputMapping, static_callbackSdoVirtOMapData);

	uint8_t tmp = libCOL_lift1;
	OD_set_value(OD_ENTRY_H6001_liftNumber, 0, &tmp, sizeof(uint8_t), true);
	tmp = libCOL_Floor_NotUsed;
	OD_set_value(OD_ENTRY_H6002_floorNumber, 0, &tmp, sizeof(uint8_t), true);
	tmp = libCOL_door1 | libCOL_door2 | libCOL_door3 | libCOL_door4;
	OD_set_value(OD_ENTRY_H6003_carDoorNumber, 0, &tmp, sizeof(uint8_t), true);
}

void CANopenNode::process()
{
	hardware->CANopen_Process();

	//  TODO Add error Handling
}

void CANopenNode::timeHandler()
{
	if(isNodeInitOk())
	{
		hardware->CANopen_Interrupt();
	}
}

void CANopenNode::errorHandler()
{
	if(isNodeInitOk())
	{
		hardware->errorHandler();
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
	if(hardware->getLedgreenstate() != 0)
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
	if(hardware->getLedredstate() != 0)
	{
		return true;
	}
	return false;
}

