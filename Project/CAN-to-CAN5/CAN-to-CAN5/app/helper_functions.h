#ifndef HELPER_FUNCTIONS_H
#define HELPER_FUNCTIONS_H

#include <cstdint>
#include "CiA417_Gateway.h"
#include "CiA417_VirtualIOMapping.h"
#include "FunctionMapping.h"
#include "CANopen.h"
// #include "CANopenNode.h"





class HelperFunctions 
{
    public:

    virtualIOMapping_data_t getODInputFunctionMapping(uint8_t PinNr);
	virtualIOMapping_data_t getODOutputFunctionMapping(uint8_t PinNr);
	virtualIOMapping_data_t* getAddressODInputFunctionMapping(uint8_t PinNr);
	virtualIOMapping_data_t* getAddressODOutputFunctionMapping(uint8_t PinNr);

	void writeInputMappingToOD(uint8_t index, const libCOL_input_t& input);
	void handleRPDO(const virtualIOMapping_data_t& mapping);

	static void static_callbackPdoVirtOMapData(void *object);
	static void static_callbackSdoVirtOMapData(void *object);
	void triggerPDOsend();
	void sendInputs();
    CO_t* CO; // CANopenNode object pointer


    private:
    void pollRecvOutputs();
	void callbackPdoVirtOMapData(void *object);
	void callbackSdoVirtOMapData(void *object);
	void adoptVirtOMapData(virtualIOMapping_data_t &data);
    CiA417_Gateway _CiA417Gateway;
	CiA417_virtualIOMapping _virtOMapData;
	CiA417_virtualIOMapping _oldVirtOMapData;
    static virtualIOMapping_data_t test;
    Stack_Fifo<virtualIOMapping_data_t, 10> fifo_sendFunctionMapping; 
	Stack_Fifo<virtualIOMapping_data_t, 10> fifo_recvFunctionMapping;
    // CANopenNode node; // Instance of the CANopenNode class to manage CANopen functionalities
};

#endif // HELPER_FUNCTIONS_H
