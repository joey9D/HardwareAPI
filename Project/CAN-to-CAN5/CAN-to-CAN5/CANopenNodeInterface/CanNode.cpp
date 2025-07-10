/*
 * CanNode.cpp
 *
 *  Created on: Sep 27, 2023
 *      Author: michael.grathwohl
 */

#include <CanNode.h>



//CanNode::CanNode()
CanNode::CanNode()
{
	// TODO Auto-generated constructor stub

}

CanNode::~CanNode()
{
	// TODO Auto-generated destructor stub
}

void CanNode::set_NmtPos(uint8_t pos)
{
	_nmtPos = pos;
	_id = _canOpenStack->HBcons->monitoredNodes[_nmtPos].nodeId;
}

void CanNode::clearNmtPos()
{
	_nmtPos = 0xFF;
	_id = 0;
}

uint8_t & CanNode::get_NmtPos()
{
	return _nmtPos;
}

uint8_t & CanNode::get_NodeId()
{
	return _id;
}

void CanNode::set_CanOpenStack(CO_t &stack)
{
	_canOpenStack = &stack;
}

void CanNode::process()
{
	if(_id == 0 || _nmtPos == 0xFF)
	{
		return;
	}

	switch(_canOpenStack->HBconsMonitoredNodes[_nmtPos].NMTstate)
	{
	case CO_NMT_INITIALIZING:
		break;
	case CO_NMT_PRE_OPERATIONAL:
		if(_sendStatusChange == false)
		{
			//CO_NMT_sendCommand(_canOpenStack->NMT, CO_NMT_ENTER_OPERATIONAL, _id);
			_waitTime.startTime(_waitTimeStatusChange);
			_sendStatusChange = true;
		}

		if(_waitTime.isTimeExpired())
		{//send command again
			_sendStatusChange = false;
		}

		break;
	case CO_NMT_OPERATIONAL:
		if(_canOpenStack->HBcons->monitoredNodes[_nmtPos].HBstate == CO_HBconsumer_TIMEOUT)
		{//todo: handling if Slave is not available any more

		}
		else
		{//todo: logic
			//uint8_t brightness;
			//OD_get_u8(OD_ENTRY_H4400_displayParameters, 3, &brightness, true);
		}

		break;
	case CO_NMT_STOPPED:
		break;
	default://CO_NMT_UNKNOWN
		break;
	}
}

