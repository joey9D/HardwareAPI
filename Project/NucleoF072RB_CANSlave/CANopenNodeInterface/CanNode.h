/*
 * CanNode.h
 *
 *  Created on: Sep 27, 2023
 *      Author: michael.grathwohl
 */

#ifndef CANNODE_H_
#define CANNODE_H_

#include "CO_app_STM32.h"
#include "OD.h"
#include "../basic/Timer.h"


class CanNode
{
public:
	//CanNode();
	CanNode();
	virtual ~CanNode();

	void set_NmtPos(uint8_t pos);
	void clearNmtPos();
	uint8_t & get_NmtPos();
	uint8_t & get_NodeId();
	void set_CanOpenStack(CO_t &stack);

	void process();

private:
	uint8_t _id = 0;
	uint8_t _nmtPos = 0xFF;
	CO_t* _canOpenStack = nullptr;
	bool _sendStatusChange = false;
	uint16_t _waitTimeStatusChange = 2000;

	Timer _waitTime;
};

#endif /* CANNODE_H_ */
