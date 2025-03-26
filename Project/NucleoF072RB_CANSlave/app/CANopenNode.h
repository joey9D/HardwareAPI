/*
 * CANNode.h
 *
 *  Created on: Dec 6, 2023
 *      Author: michael.grathwohl
 */

#ifndef CANOPENNODE_H_
#define CANOPENNODE_H_

#include "../basic/singleton.h"
#include "CO_app_STM32.h"
#include "CiA417_VirtualIOMapping.h"
#include "FunctionMapping.h"
#include "../basic/stack_fifo.h"
#include "CiA417_Gateway.h"

class CANopenNode
{
	SINGLETON_DECLARE(CANopenNode)

public:

	Stack_Fifo<virtualIOMapping_data_t, 10> fifo_sendFunctionMapping;
	Stack_Fifo<virtualIOMapping_data_t, 10> fifo_recvFunctionMapping;

	void setCANNodeParameter(CAN_HandleTypeDef *hcan, TIM_HandleTypeDef* htim, void (*CANhwInit)(uint16_t baud));
	bool initNode();
	bool isNodeInitOk();
	uint32_t getLastError();
	CAN_HandleTypeDef* getCANHandler();
	TIM_HandleTypeDef* getTimerHandler();

	void setCallbackFunctions();

	void process();
	void timeHandler();
	void errorHandler();

	bool isLEDGreenOn();
	bool isLEDRedOn();

	virtualIOMapping_data_t getODInputFunctionMapping(uint8_t PinNr);
	virtualIOMapping_data_t getODOutputFunctionMapping(uint8_t PinNr);
	virtualIOMapping_data_t* getAddressODInputFunctionMapping(uint8_t PinNr);
	virtualIOMapping_data_t* getAddressODOutputFunctionMapping(uint8_t PinNr);

	static void static_callbackPdoVirtOMapData(void *object);
	static void static_callbackSdoVirtOMapData(void *object);
	void sendInputs();

	void triggerPDOsend();


private:
	CANopenNodeSTM32 _canOpenNodeParameter;
	uint8_t _initState = 0;
	uint32_t _error = 0;
	CiA417_Gateway _CiA417Gateway;

	CiA417_virtualIOMapping _virtOMapData;
	CiA417_virtualIOMapping _oldVirtOMapData;

	//CANopenNode();
	void setinitState(uint8_t val);
	void setLastError(uint32_t val);
	//void triggerPDOsend();
	void pollRecvOutputs();
	void callbackPdoVirtOMapData(void *object);
	void callbackSdoVirtOMapData(void *object);
	void adoptVirtOMapData(virtualIOMapping_data_t &data);

	// zum testen
	//virtualIOMapping dataSlaveToMaster;
	//virtualIOMapping dataMasterToSlave;
	void pdoTest();
};

#endif /* CANOPENNODE_H_ */
