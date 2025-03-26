/*
 * CanStackInterface.h
 *
 *  Created on: Sep 19, 2023
 *      Author: michael.grathwohl
 */

#ifndef CANSTACKINTERFACE_H_
#define CANSTACKINTERFACE_H_

#include "../basic/singleton.h"
#include "../basic/Timer.h"
#include "CO_app_STM32.h"
#include "CanNode.h"

class CanStackInterface
{
//	SINGLETON(CanStackInterface)
	SINGLETON(CanStackInterface)
public:
	enum CANopenMasterStates : uint8_t
	{
		CANopenMaster_Init	= 0x00,
		CANopenMaster_ResetNodes,
		CANopenMaster_PreOp,
		CANopenMaster_StartNodes,
		CANopenMaster_CheckOp,
		CANopenMaster_Op,
		CANopenMaster_Stop,
		CANopenMaster_Error,
		CANopenMaster_Unknown
	};

	void set_CanStack(CANopenNodeSTM32 &canOpenNode);
	CANopenNodeSTM32* get_CanStack();

	bool isCanStackInitialized();

	void irqTimerHandler();
	void irqErrorHandler();

	void process();

	CANopenMasterStates & get_CanMasterState();
	void set_CanMasterState(CANopenMasterStates state);

private:
    CanStackInterface();
	CANopenNodeSTM32 *_canOpenNode;
	bool CanStackEnabled;
	CANopenMasterStates _masterState;
	Timer _waitTime;
	static const uint8_t _maxNodes = 10;
	CanNode _nodes[_maxNodes];

	uint8_t get_MaxCountNodes();
};

#endif /* CANSTACKINTERFACE_H_ */
