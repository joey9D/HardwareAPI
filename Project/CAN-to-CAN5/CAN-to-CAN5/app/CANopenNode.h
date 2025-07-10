/*
 * CANNode.h
 *
 *  Created on: Dec 6, 2023
 *      Author: michael.grathwohl
 */

#ifndef CANOPENNODE_H_
#define CANOPENNODE_H_

#include "../basic/singleton.h"
#include "CiA417_VirtualIOMapping.h"
#include "FunctionMapping.h"
#include "../basic/stack_fifo.h"
#include "CiA417_Gateway.h"
#include "Hardware_Factory.h"
#include "CiA417_CmdHandler.h"


class CANopenNode
{
	// Macro to declare the singleton pattern for the CANopenNode class.
	// Ensures that only one instance of this class exists throughout the application.
	//SINGLETON_DECLARE(CANopenNode)

public:
	CANopenNode(HardwareInterface* hardware);

	void initialize(); // Initialize dependent objects
	// PDO_SDO& getPDO_SDO();
	// GPIOHandler& getGPIOHandler();
	// NMT_LED& getNMT_LED();
	
	bool initNode();
	bool isNodeInitOk();
	void errorloop();
	uint32_t getLastError();
	
	void InitNodeStack();

	void setCallbackFunctions();

	void process();
	void timeHandler();
	void errorHandler();

	bool isLEDGreenOn();
	bool isLEDRedOn();

	// virtualIOMapping_data_t getODInputFunctionMapping(uint8_t PinNr);
	// virtualIOMapping_data_t getODOutputFunctionMapping(uint8_t PinNr);
	// virtualIOMapping_data_t* getAddressODInputFunctionMapping(uint8_t PinNr);
	// virtualIOMapping_data_t* getAddressODOutputFunctionMapping(uint8_t PinNr);

	// void writeInputMappingToOD(uint8_t index, const libCOL_input_t& input);
	// void handleRPDO(const virtualIOMapping_data_t& mapping);

	// static void static_callbackPdoVirtOMapData(void *object);
	// static void static_callbackSdoVirtOMapData(void *object);
	// void triggerPDOsend();
	// void sendInputs();

	// static CANopenNodeSTM32* getCANopenNodeSTM32();
    HardwareInterface* getHardwareInterface();
	CiA417_CmdHandler& getCiA417_CmdHandler();
	// CO_t* CO; // CANopenNode object pointer



private:

	Stack_Fifo<virtualIOMapping_data_t, 10> fifo_sendFunctionMapping; 
	Stack_Fifo<virtualIOMapping_data_t, 10> fifo_recvFunctionMapping;
	// CANopenNodeSTM32 _canOpenNodeParameter;
	HardwareInterface* hardware = nullptr;           // Static pointer to HardwareInterface
	CiA417_CmdHandler _CmdHandlers;
	uint8_t _initState = 0;
	uint32_t _error = 0;
	CiA417_Gateway _CiA417Gateway;
	CiA417_virtualIOMapping _virtOMapData;
	CiA417_virtualIOMapping _oldVirtOMapData;
	// PDO_SDO _pdoSdo = nullptr;
    // GPIOHandler _gpioHandler;
    // NMT_LED* _nmtLed = nullptr;
	void setinitState(uint8_t val);
	void setLastError(uint32_t val);
	void pollRecvOutputs();
	void callbackPdoVirtOMapData(void *object);
	void callbackSdoVirtOMapData(void *object);
	void adoptVirtOMapData(virtualIOMapping_data_t &data);


	void pdoTest();
};

#endif /* CANOPENNODE_H_ */
