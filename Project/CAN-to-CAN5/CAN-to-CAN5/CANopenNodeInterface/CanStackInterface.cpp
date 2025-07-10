/*
 * CanStackInterface.cpp
 *
 *  Created on: Sep 19, 2023
 *      Author: michael.grathwohl
 */

#include "CanStackInterface.h"
#include "OD.h"


CanStackInterface::CanStackInterface():
	_canOpenNode(nullptr),
	CanStackEnabled(false),
	_masterState(CANopenMasterStates::CANopenMaster_Init)
{

}
void CanStackInterface::set_CanStack(CANopenNodeSTM32 &canOpenNode)
{
	if(canopen_app_init(&canOpenNode) == 0)
	{
		_canOpenNode = &canOpenNode;
		CanStackEnabled = true;

		if(_canOpenNode->desiredNodeID != _canOpenNode->activeNodeID)
		{
			//fail ?
		}
	}
}

CANopenNodeSTM32* CanStackInterface::get_CanStack()
{
	return _canOpenNode;
}

bool CanStackInterface::isCanStackInitialized()
{
	return CanStackEnabled;
}

void CanStackInterface::irqTimerHandler()
{
	if(isCanStackInitialized())
	{
		canopen_app_interrupt();
		//_canOpenStack->outStatusLEDGreen;
		//_canOpenStack->outStatusLEDRed;
	}
}

void CanStackInterface::irqErrorHandler()
{
	if(isCanStackInitialized())
	{

	}
}

void CanStackInterface::process()
{
	canopen_app_process();

	//uint8_t brightness;
	//OD_get_u8(OD_ENTRY_H4400_displayParameters, 3, &brightness, true);

	switch(get_CanMasterState())
	{
	case CANopenMasterStates::CANopenMaster_Init:
		set_CanMasterState(CANopenMasterStates::CANopenMaster_ResetNodes);

		break;
	case CANopenMasterStates::CANopenMaster_ResetNodes:
		//CO_NMT_sendCommand(_canOpenNode->canOpenStack->NMT, CO_NMT_RESET_COMMUNICATION, 0); //Address all nodes
		//CO_NMT_sendCommand(_canOpenNode->canOpenStack->NMT, CO_NMT_ENTER_PRE_OPERATIONAL, _canOpenNode->canOpenStack->NMT->nodeId);
		set_CanMasterState(CANopenMasterStates::CANopenMaster_PreOp);
		_waitTime.startTime(500);

		break;
	case CANopenMasterStates::CANopenMaster_PreOp:
		if(_waitTime.isTimeExpired())
		{
			for(uint8_t i=0; i<get_MaxCountNodes(); i++)
			{
				if(_canOpenNode->canOpenStack->HBcons->monitoredNodes[i].nodeId != 0)
				{
					_nodes[i].set_CanOpenStack(*_canOpenNode->canOpenStack);
					_nodes[i].set_NmtPos(i);
				}
			}

			/*
			 * todo: Pruefen ob CAN Master in Operational gehen darf
			 */
			set_CanMasterState(CANopenMasterStates::CANopenMaster_StartNodes);
			_waitTime.startTime(10);
		}

		break;
	case CANopenMasterStates::CANopenMaster_StartNodes:
		if(_waitTime.isTimeExpired())
		{
			//Set Master Operational
			//CO_NMT_sendCommand(_canOpenNode->canOpenStack->NMT, CO_NMT_ENTER_OPERATIONAL, _canOpenNode->canOpenStack->NMT->nodeId);
			//_canOpenNode->canOpenStack->NMT->internalCommand = CO_NMT_ENTER_OPERATIONAL;
			set_CanMasterState(CANopenMasterStates::CANopenMaster_CheckOp);
		}
		break;
	case CANopenMasterStates::CANopenMaster_CheckOp:
		if(_canOpenNode->canOpenStack->NMT->operatingState == CO_NMT_OPERATIONAL)
		{
			set_CanMasterState(CANopenMasterStates::CANopenMaster_Op);
		}
		break;
	case CANopenMasterStates::CANopenMaster_Op:
		/*
		 * check state of CAN Stack:
		 * in OD.c muss x1016_consumerHeartbeatTime gesetzt sein damit überwachung im Master funktioniert
		 * Bsp.: 0x001007D0 -> SlaveNodeId=0x10, HeartbeatTime=0x07D0
		 */
		if(_canOpenNode->canOpenStack->NMT->operatingState == CO_NMT_OPERATIONAL)
		{
			for(uint8_t i=0; i<get_MaxCountNodes(); i++)
			{
				switch(_canOpenNode->canOpenStack->HBconsMonitoredNodes[i].NMTstate)
				{
				case CO_NMT_INITIALIZING:
				case CO_NMT_PRE_OPERATIONAL:
					if(_nodes[i].get_NodeId() == 0)
					{
						_nodes[i].set_NmtPos(i);
					}
					break;
				case CO_NMT_OPERATIONAL:
					_nodes[i].process();
					break;
				case CO_NMT_STOPPED:
					break;
				default://CO_NMT_UNKNOWN
					break;
				}
			}

			//uint8_t weight;
			//OD_set_u8(OD_ENTRY_H4405_LiftdataWeight, 1, weight, true);
		}
		else
		{
			set_CanMasterState(CANopenMasterStates::CANopenMaster_Stop);
			//CO_NMT_sendCommand(_canOpenNode->canOpenStack->NMT, CO_NMT_ENTER_STOPPED, _canOpenNode->canOpenStack->NMT->nodeId);
			if(_canOpenNode->canOpenStack->CANmodule->CANerrorStatus != CO_EM_NO_ERROR)
			{
				//if(_canOpenNode->canOpenStack->CANmodule->CANerrorStatus == CO_CAN_ERR_WARN_PASSIVE)
				//if(_canOpenNode->canOpenStack->NMT->em->errorRegister)
				//_canOpenNode->canOpenStack->em->errorStatusBits
			}
		}

		break;
	case CANopenMasterStates::CANopenMaster_Stop:
		//todo: error Handling, start master again
		//setCanMasterState(CANopenMasterStates::CANopenMaster_PreOp);

		break;
	case CANopenMasterStates::CANopenMaster_Error:
		//setCanMasterState(CANopenMasterStates::CANopenMaster_ResetNodes);
		break;
	default:
		set_CanMasterState(CANopenMasterStates::CANopenMaster_Stop);

		break;
	}
}


CanStackInterface::CANopenMasterStates & CanStackInterface::get_CanMasterState()
{
	return _masterState;
}

void CanStackInterface::set_CanMasterState(CANopenMasterStates state)
{
	_masterState = state;
}

uint8_t CanStackInterface::get_MaxCountNodes()
{
	uint8_t retval = _canOpenNode->canOpenStack->HBcons->numberOfMonitoredNodes;
	if(retval >= _maxNodes)
	{
		retval = _maxNodes;
	}
	return retval;
}
