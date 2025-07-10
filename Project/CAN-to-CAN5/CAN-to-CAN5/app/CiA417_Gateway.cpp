/*
 * CiA417Verifier.cpp
 *
 *  Created on: Jan 29, 2024
 *      Author: michael.grathwohl
 */

#include "CiA417_Gateway.h"
#include "CANopen.h"
#include "OD.h"
#include "CiA417_LiftTypes.h"

CiA417_Gateway::CiA417_Gateway()
{
	// TODO Auto-generated constructor stub

}

CiA417_Gateway::~CiA417_Gateway()
{
	// TODO Auto-generated destructor stub
}

bool CiA417_Gateway::isOutputBfValid(const uint8_t &Bf)
{
	bool retval = false;

	switch(Bf)
	{
	case libCOL_of_callControllerCommand:
	case libCOL_of_genericOutput:
	case libCOL_of_hallCallAcknowledgement:
	case libCOL_of_lowPriorityHallCallAcknowledgement:
	case libCOL_of_highPriorityHallCallAcknowledgement:
	case libCOL_of_carCallAcknowledgement:
	case libCOL_of_lowPriorityCarCallAcknowledgement:
	case libCOL_of_highPriorityCarCallAcknowledgement:
	case libCOL_of_destinationCallAcknowledgement:
	case libCOL_of_lowPriorityDestinationCallAcknowledgement:
	case libCOL_of_highPriorityDestinationCallAcknowledgement:
	case libCOL_of_destinationFloorAcknowledgement:
	case libCOL_of_lowPriorityDestinationFloorAcknowledgement:
	case libCOL_of_highPriorityDestinationFloorAcknowledgement:
	case libCOL_of_specialFunctionAcknowledgement:
	case libCOL_of_accessCodeUploadAcknowledgement:
	case libCOL_of_speechConnectionAcknowledgement:
	case libCOL_of_areaMonitoringConnectionAcknowledgement:
	case libCOL_of_guestCallAcknowledgement:
	case libCOL_of_liftLightsAcknowledgement:
	case libCOL_of_positionIndication:
	case libCOL_of_hallLantern:
	case libCOL_of_directionIndication:
	case libCOL_of_specialIndication:
	case libCOL_of_arrivalIndication:
	case libCOL_of_vocalFloorsAnnouncement:
	case libCOL_of_vocalUserMessage:
	case libCOL_of_musicPlayback:
	case libCOL_of_miscellaneousOutputs:
	case libCOL_of_singleFaultIndication:
	case libCOL_of_nextStop:
	case libCOL_of_positionIndicationBinary:
	case libCOL_of_positionIndicationGray:
	case libCOL_of_positionIndication7Segment:
	case libCOL_of_vocalFloorsAnnouncementBinary:
	case libCOL_of_vocalFloorsAnnouncementGray:
		retval = true;
		break;
	default:
		break;
	}

	return retval;
}

bool CiA417_Gateway::isOutputSfValid(const uint8_t &Bf, const uint8_t &Sf)
{
	bool retval = false;

	return retval;
}

bool CiA417_Gateway::isInputBfValid(const uint8_t &Bf)
{
	bool retval = false;

	switch(Bf)
	{
	case libCOL_if_Lift_status_information_request:
	case libCOL_if_generic:
	case libCOL_if_hallStandard:
	case libCOL_if_hallLowPriority:
	case libCOL_if_hallHighPriority:
	case libCOL_if_carCallStandard:
	case libCOL_if_carCallLowPriority:
	case libCOL_if_carCallHighPriority:
	case libCOL_if_destinationCallStandard:
	case libCOL_if_destinationCallLowPriority:
	case libCOL_if_destinationCallHighPriority:
	case libCOL_if_destinationFloorCallStandard:
	case libCOL_if_destinationFloorCallLowPriority:
	case libCOL_if_destinationFloorCallHighPriority:
	case libCOL_if_specialFunction:
	case libCOL_if_accessCodeUpload:
	case libCOL_if_speechConnectionRequest:
	case libCOL_if_areaMonitoringConnectionRequest:
	case libCOL_if_fireDetector:
	case libCOL_if_inspectionControlCar:
	case libCOL_if_floorSelector:
	case libCOL_if_statusSafetyCircuitries:
	case libCOL_if_guestCall:
	case libCOL_if_liftLights:
		retval = true;
		break;
	default:
		break;
	}

	return retval;
}

bool CiA417_Gateway::isInputSfValid(const uint8_t &Bf, const uint8_t &Sf)
{
	bool retval = false;

	return retval;
}

bool CiA417_Gateway::isLiftValid(const uint8_t &Lift)
{
	bool retval = false;
	uint8_t *p_Lift = (uint8_t*)OD_getPtr(OD_ENTRY_H6001_liftNumber, 0, sizeof(uint8_t), NULL);
	assert(p_Lift != nullptr);
	//libCOL_LiftBits_t

	if((Lift & *p_Lift) != 0)
	{
		retval = true;
	}

	return retval;
}

bool CiA417_Gateway::isFloorValid(const uint8_t &Floor)
{
	bool retval = false;
	uint8_t *p_Floor = (uint8_t*)OD_getPtr(OD_ENTRY_H6002_floorNumber, 0, sizeof(uint8_t), NULL);
	assert(p_Floor != nullptr);

	switch(*p_Floor)
	{
	case libCOL_Floor_CarPanels:
		retval = true;
		break;
	case libCOL_Floor_NotUsed:
		retval = true;
		break;
	default:
		if(Floor == *p_Floor)
		{
			retval = true;
		}
		break;
	}

	return retval;
}

bool CiA417_Gateway::isDoorValid(const uint8_t &Door)
{
	bool retval = false;
	uint8_t *p_Door = (uint8_t*)OD_getPtr(OD_ENTRY_H6003_carDoorNumber, 0, sizeof(uint8_t), NULL);
	assert(p_Door != nullptr);

	//Bit 0: Door 1
	//Bit 1: Door 2
	//Bit 2: Door 3
	//Bit 3: Door 4
	//Bit 4-7: reserved
	if((Door & *p_Door) != 0)
	{
		retval = true;
	}

	return retval;
}
