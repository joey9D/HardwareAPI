/*
 * CiA417_CmdHandler.cpp
 *
 *  Created on: Jan 30, 2024
 *      Author: michael.grathwohl
 */

#include "CiA417_CmdHandler.h"
#include "CiA417_LiftTypes.h"

void CiA417_CmdHandler::switchCmdToAlternative(virtualIOMapping_data_t &mapData)
{
	/*
	mapping table ?
	or
	for(loop alternate list)
	{
		if(mapData.virt_ioMapping.basicFunction in alternate list
			|| mapData.virt_ioMapping.subFunction in alternate list)
		{
			mapData.virt_ioMapping.basicFunction = alternate_bf;
			mapData.virt_ioMapping.subFunction = alternate_sf;
		}
	}
	*/
}

// -----------------------------------------------------------------------------------
// Output functions for Object 0x6200
// -----------------------------------------------------------------------------------

void CiA417_CmdHandler::execBf_callControllerCommand(const virtualIOMapping_data_t &mapData)
{
	switch(mapData.subFunction)
	{
	case libCOL_outputSubFunction_tag::libCOL_requestAll:
		break;
	case libCOL_outputSubFunction_tag::libCOL_requestHallCalls:
	case libCOL_outputSubFunction_tag::libCOL_requestSpecialInputs:
	case libCOL_outputSubFunction_tag::libCOL_requestAllInputsExceptCalls:
		break;
	default:
		break;
	}
}

void CiA417_CmdHandler::execBf_genericOutput(const virtualIOMapping_data_t &mapData)
{
	//mapData.virt_ioMapping.subFunction
}

void CiA417_CmdHandler::execBf_hallCallAcknowledgement(const virtualIOMapping_data_t &mapData)
{
	switch(mapData.subFunction)
	{
	case libCOL_outputSubFunction_tag::libCOL_hall_up_ack:
	case libCOL_outputSubFunction_tag::libCOL_hall_down_ack:
	case libCOL_outputSubFunction_tag::libCOL_hall_ack:
	case libCOL_outputSubFunction_tag::libCOL_hall_extraUp_ack:
	case libCOL_outputSubFunction_tag::libCOL_hall_extraDown_ack:
	case libCOL_outputSubFunction_tag::libCOL_hall_extra_ack:
	default:
		break;
	}
}

void CiA417_CmdHandler::execBf_lowPriorityHallCallAcknowledgement(const virtualIOMapping_data_t &mapData)
{
	switch(mapData.subFunction)
	{
	case libCOL_outputSubFunction_tag::libCOL_hall_up_ack:
	case libCOL_outputSubFunction_tag::libCOL_hall_down_ack:
	case libCOL_outputSubFunction_tag::libCOL_hall_ack:
	case libCOL_outputSubFunction_tag::libCOL_hall_extraUp_ack:
	case libCOL_outputSubFunction_tag::libCOL_hall_extraDown_ack:
	case libCOL_outputSubFunction_tag::libCOL_hall_extra_ack:
	default:
		break;
	}
}

void CiA417_CmdHandler::execBf_highPriorityHallCallAcknowledgement(const virtualIOMapping_data_t &mapData)
{
	switch(mapData.subFunction)
	{
	case libCOL_outputSubFunction_tag::libCOL_hall_up_ack:
	case libCOL_outputSubFunction_tag::libCOL_hall_down_ack:
	case libCOL_outputSubFunction_tag::libCOL_hall_ack:
	case libCOL_outputSubFunction_tag::libCOL_hall_extraUp_ack:
	case libCOL_outputSubFunction_tag::libCOL_hall_extraDown_ack:
	case libCOL_outputSubFunction_tag::libCOL_hall_extra_ack:
	default:
		break;
	}
}

void CiA417_CmdHandler::execBf_carCallAcknowledgement(const virtualIOMapping_data_t &mapData)
{
	switch(mapData.subFunction)
	{
	case 0x00:
		break;
	case 0xFF:
		break;
	default://0x01-0xFE
		break;
	}
}

void CiA417_CmdHandler::execBf_lowPriorityCarCallAcknowledgement(const virtualIOMapping_data_t &mapData)
{
	switch(mapData.subFunction)
	{
	case 0x00:
		break;
	case 0xFF:
		break;
	default://0x01-0xFE
		break;
	}
}

void CiA417_CmdHandler::execBf_highPriorityCarCallAcknowledgement(const virtualIOMapping_data_t &mapData)
{
	switch(mapData.subFunction)
	{
	case 0x00:
		break;
	case 0xFF:
		break;
	default://0x01-0xFE
		break;
	}
}

void CiA417_CmdHandler::execBf_destinationCallAcknowledgement(const virtualIOMapping_data_t &mapData)
{
	switch(mapData.subFunction)
	{
	case 0x00:
		break;
	case 0xFF:
		break;
	default://0x01-0xFE
		break;
	}
}

void CiA417_CmdHandler::execBf_lowPriorityDestinationCallAcknowledgement(const virtualIOMapping_data_t &mapData)
{
	switch(mapData.subFunction)
	{
	case 0x00:
		break;
	case 0xFF:
		break;
	default://0x01-0xFE
		break;
	}
}

void CiA417_CmdHandler::execBf_highPriorityDestinationCallAcknowledgement(const virtualIOMapping_data_t &mapData)
{
	switch(mapData.subFunction)
	{
	case 0x00:
		break;
	case 0xFF:
		break;
	default://0x01-0xFE
		break;
	}
}

void CiA417_CmdHandler::execBf_destinationFloorAcknowledgement(const virtualIOMapping_data_t &mapData)
{
	switch(mapData.subFunction)
	{
	case 0x00:
		break;
	case 0xFF:
		break;
	default://0x01-0xFE
		break;
	}
}

void CiA417_CmdHandler::execBf_lowPriorityDestinationFloorAcknowledgement(const virtualIOMapping_data_t &mapData)
{
	switch(mapData.subFunction)
	{
	case 0x00:
		break;
	case 0xFF:
		break;
	default://0x01-0xFE
		break;
	}
}

void CiA417_CmdHandler::execBf_highPriorityDestinationFloorAcknowledgement(const virtualIOMapping_data_t &mapData)
{
	switch(mapData.subFunction)
	{
	case 0x00:
		break;
	case 0xFF:
		break;
	default://0x01-0xFE
		break;
	}
}

void CiA417_CmdHandler::execBf_specialFunctionAcknowledgement(const virtualIOMapping_data_t &mapData)
{
	switch(mapData.subFunction)
	{
	case libCOL_outputSubFunction_tag::libCOL_special_requestFan1_ack:
	case libCOL_outputSubFunction_tag::libCOL_special_requestFan2_ack:
	case libCOL_outputSubFunction_tag::libCOL_special_requestLoadTime1_ack:
	case libCOL_outputSubFunction_tag::libCOL_special_requestLoadTime2_ack:
	case libCOL_outputSubFunction_tag::libCOL_special_keyLock1_ack:
	case libCOL_outputSubFunction_tag::libCOL_special_keyLock2_ack:
	case libCOL_outputSubFunction_tag::libCOL_special_keyLock3_ack:
	case libCOL_outputSubFunction_tag::libCOL_special_keyLock4_ack:
	case libCOL_outputSubFunction_tag::libCOL_special_requestDoorOpen_ack:
	case libCOL_outputSubFunction_tag::libCOL_special_requestDoorClose_ack:
	case libCOL_outputSubFunction_tag::libCOL_special_fireRecall_ack:
	case libCOL_outputSubFunction_tag::libCOL_special_fireService_ack:
	case libCOL_outputSubFunction_tag::libCOL_special_hallCallDisable_ack:
	case libCOL_outputSubFunction_tag::libCOL_special_attendantService_ack:
	case libCOL_outputSubFunction_tag::libCOL_special_vipService_ack:
	case libCOL_outputSubFunction_tag::libCOL_special_outOfOrder_ack:
	case libCOL_outputSubFunction_tag::libCOL_special_bedPassengerService_ack:
	case libCOL_outputSubFunction_tag::libCOL_special_specialService_ack:
	case libCOL_outputSubFunction_tag::libCOL_special_serviceRun_ack:
	case libCOL_outputSubFunction_tag::libCOL_special_dockingServiceEnable_ack:
	case libCOL_outputSubFunction_tag::libCOL_special_dockungServiceUp_ack:
	case libCOL_outputSubFunction_tag::libCOL_special_dockingServiceDown_ack:
	case libCOL_outputSubFunction_tag::libCOL_special_fireAlarm_ack:
	case libCOL_outputSubFunction_tag::libCOL_special_providePriority_ack:
	case libCOL_outputSubFunction_tag::libCOL_special_liftAttendantStartButton_ack:
	case libCOL_outputSubFunction_tag::libCOL_special_liftAttendantDriveThroughButton_ack:
	case libCOL_outputSubFunction_tag::libCOL_special_securityRun_ack:
	case libCOL_outputSubFunction_tag::libCOL_special_secondCallPanel_ack:
	case libCOL_outputSubFunction_tag::libCOL_special_doorEnable_ack:
	case libCOL_outputSubFunction_tag::libCOL_special_callCancelButtonFireOperation_ack:
	case libCOL_outputSubFunction_tag::libCOL_special_fireAlarmReset_ack:
	case libCOL_outputSubFunction_tag::libCOL_special_bodyDetector_ack:
	case libCOL_outputSubFunction_tag::libCOL_special_earthquakeDetector_ack:
	case libCOL_outputSubFunction_tag::libCOL_special_cleaningTravel_ack:
	case libCOL_outputSubFunction_tag::libCOL_special_EmergencyAlarmReady_ack:
	case libCOL_outputSubFunction_tag::libCOL_special_EmergencyAlarmGreen_ack:
	case libCOL_outputSubFunction_tag::libCOL_special_EmergencyAlarmYellow_ack:
	case libCOL_outputSubFunction_tag::libCOL_special_EmergencyAlarmButtonPressed_ack:
	default:
		break;
	}
}

void CiA417_CmdHandler::execBf_accessCodeUploadAcknowledgement(const virtualIOMapping_data_t &mapData)
{
	switch(mapData.subFunction)
	{
	case 0x00:
	case 0xFF:
		break;
	default://0x01-0xFE
		break;
	}
}

void CiA417_CmdHandler::execBf_speechConnectionAcknowledgement(const virtualIOMapping_data_t &mapData)
{
	//mapData.virt_ioMapping.subFunction
}

void CiA417_CmdHandler::execBf_areaMonitoringConnectionAcknowledgement(const virtualIOMapping_data_t &mapData)
{
	//mapData.virt_ioMapping.subFunction
}

void CiA417_CmdHandler::execBf_guestCallAcknowledgement(const virtualIOMapping_data_t &mapData)
{
	switch(mapData.subFunction)
	{
	case 0x00:
	case 0xFF:
		break;
	default://0x01-0xFE
		break;
	}
}

void CiA417_CmdHandler::execBf_liftLightsAcknowledgement(const virtualIOMapping_data_t &mapData)
{
	switch(mapData.subFunction)
	{
	case libCOL_outputSubFunction_tag::libCOL_liftLightsMainLight_On_ack:
	case libCOL_outputSubFunction_tag::libCOL_liftLightMainLight_Off_ack:
	case libCOL_outputSubFunction_tag::libCOL_liftLightSecondaryLight_On_ack:
	case libCOL_outputSubFunction_tag::libCOL_liftLightSecondaryLight_Off_ack:
	case libCOL_outputSubFunction_tag::libCOL_liftLightEmergencyLight_On_ack:
	case libCOL_outputSubFunction_tag::libCOL_liftLightEmergencyLight_Off_ack:
	case libCOL_outputSubFunction_tag::libCOL_liftLightAmbientLight_On_ack:
	case libCOL_outputSubFunction_tag::libCOL_liftLightAmbientLight_Off_ack:
	case libCOL_outputSubFunction_tag::libCOL_liftLightPanelLight_On_ack:
	case libCOL_outputSubFunction_tag::libCOL_liftLightPanelLight_Off_ack:
	case libCOL_outputSubFunction_tag::libCOL_liftLightFloorLight_On_ack:
	case libCOL_outputSubFunction_tag::libCOL_liftLightFloorLight_Off_ack:
	case libCOL_outputSubFunction_tag::libCOL_liftLightShaftLight_On_ack:
	case libCOL_outputSubFunction_tag::libCOL_liftLightShaftLight_Off_ack:
	default:
		break;
	}
}

void CiA417_CmdHandler::execBf_positionIndication(const virtualIOMapping_data_t &mapData)
{
	switch(mapData.subFunction)
	{
	case 0x00:
	case 0xFF:
		break;
	default://0x01-0xFE
		break;
	}
}

void CiA417_CmdHandler::execBf_hallLantern(const virtualIOMapping_data_t &mapData)
{
	// Bit encoded
	switch(mapData.subFunction)
	{
	case libCOL_outputSubFunction_tag::libCOL_hallLantern_Up:
	case libCOL_outputSubFunction_tag::libCOL_hallLantern_Down:
	default:
		break;
	}
}

void CiA417_CmdHandler::execBf_directionIndication(const virtualIOMapping_data_t &mapData)
{
	// Bit encoded
	// Bit 0:	up
	// Bit 1:	down
	// Bit 2-3:	reserved
	// Bit 4:	moving up
	// Bit 5:	moving down
	// Bit 6-7:	reserved
	switch(mapData.subFunction)
	{
	case libCOL_outputSubFunction_tag::libCOL_directionIndication_Up:
	case libCOL_outputSubFunction_tag::libCOL_directionIndication_Down:
	case libCOL_outputSubFunction_tag::libCOL_directionIndication_MovingUp:
	case libCOL_outputSubFunction_tag::libCOL_directionIndication_MovingDown:
	default:
		break;
	}
}

void CiA417_CmdHandler::execBf_specialIndication(const virtualIOMapping_data_t &mapData)
{
	switch(mapData.subFunction)
	{
	case libCOL_outputSubFunction_tag::libCOL_specialIndication_clear:
	case libCOL_outputSubFunction_tag::libCOL_specialIndication_noLoad:
	case libCOL_outputSubFunction_tag::libCOL_specialIndication_fullLoad:
	case libCOL_outputSubFunction_tag::libCOL_specialIndication_overLoad:
	case libCOL_outputSubFunction_tag::libCOL_specialIndication_fireRecall:
	case libCOL_outputSubFunction_tag::libCOL_specialIndication_fireService:
	case libCOL_outputSubFunction_tag::libCOL_specialIndication_helpIsComing:
	case libCOL_outputSubFunction_tag::libCOL_specialIndication_specialService:
	case libCOL_outputSubFunction_tag::libCOL_specialIndication_loadTime:
	case libCOL_outputSubFunction_tag::libCOL_specialIndication_occupied:
	case libCOL_outputSubFunction_tag::libCOL_specialIndication_outOfOrder:
	case libCOL_outputSubFunction_tag::libCOL_specialIndication_closeDoor:
	case libCOL_outputSubFunction_tag::libCOL_specialIndication_fireAlarm:
	case libCOL_outputSubFunction_tag::libCOL_specialIndication_hallCallDisable:
	case libCOL_outputSubFunction_tag::libCOL_specialIndication_travelToFireAlarmFloor:
	case libCOL_outputSubFunction_tag::libCOL_specialIndication_travelToFireRecallFloor:
	case libCOL_outputSubFunction_tag::libCOL_specialIndication_liftInMaintenance:
	case libCOL_outputSubFunction_tag::libCOL_specialIndication_vipTransport:
	case libCOL_outputSubFunction_tag::libCOL_specialIndication_guestCall:
	case libCOL_outputSubFunction_tag::libCOL_specialIndication_medicalEmergencyTransport:
	case libCOL_outputSubFunction_tag::libCOL_specialIndication_chemicalTransport:
	case libCOL_outputSubFunction_tag::libCOL_specialIndication_bedTransport:
	case libCOL_outputSubFunction_tag::libCOL_specialIndication_testTravel:
	case libCOL_outputSubFunction_tag::libCOL_specialIndication_lowPriorityCallTransport:
	case libCOL_outputSubFunction_tag::libCOL_specialIndication_highPriorityCallTransport:
	case libCOL_outputSubFunction_tag::libCOL_specialIndication_stepWarningIndication:
	case libCOL_outputSubFunction_tag::libCOL_specialIndication_liftAttendantService:
	case libCOL_outputSubFunction_tag::libCOL_specialIndication_rescueOperation:
	case libCOL_outputSubFunction_tag::libCOL_specialIndication_emergencyPowerOperation:
	case libCOL_outputSubFunction_tag::libCOL_specialIndication_personTrapped:
	case libCOL_outputSubFunction_tag::libCOL_specialIndication_liftIsTravelling:
	case libCOL_outputSubFunction_tag::libCOL_specialIndication_Userdef1:
	case libCOL_outputSubFunction_tag::libCOL_specialIndication_Userdef2:
	case libCOL_outputSubFunction_tag::libCOL_specialIndication_Userdef3:
	case libCOL_outputSubFunction_tag::libCOL_specialIndication_Userdef4:
	case libCOL_outputSubFunction_tag::libCOL_specialIndication_Userdef5:
	case libCOL_outputSubFunction_tag::libCOL_specialIndication_Userdef6:
	case libCOL_outputSubFunction_tag::libCOL_specialIndication_Userdef7:
	case libCOL_outputSubFunction_tag::libCOL_specialIndication_Userdef8:
	case libCOL_outputSubFunction_tag::libCOL_specialIndication_Userdef9:
	case libCOL_outputSubFunction_tag::libCOL_specialIndication_Userdef10:
	default:
		break;
	}
}

void CiA417_CmdHandler::execBf_arrivalIndication(const virtualIOMapping_data_t &mapData)
{
	switch(mapData.subFunction)
	{
	case libCOL_outputSubFunction_tag::libCOL_arrivalIndication_Up:
	case libCOL_outputSubFunction_tag::libCOL_arrivalIndication_Down:
	case libCOL_outputSubFunction_tag::libCOL_arrivalIndication_NoDirection:
	default:
		break;
	}
}

void CiA417_CmdHandler::execBf_vocalFloorsAnnouncement(const virtualIOMapping_data_t &mapData)
{
	switch(mapData.subFunction)
	{
	case 0x00://Switch off vocal floors announcement
	case 0xFF://current Floor
	default://0x01-0xFE
		break;
	}
}

void CiA417_CmdHandler::execBf_vocalUserMessage(const virtualIOMapping_data_t &mapData)
{
	switch(mapData.subFunction)
	{
	case libCOL_outputSubFunction_tag::libCOL_switchOffAnnouncements:
	case libCOL_outputSubFunction_tag::libCOL_doorOpening:
	case libCOL_outputSubFunction_tag::libCOL_doorClosing:
	case libCOL_outputSubFunction_tag::libCOL_liftGoingUp:
	case libCOL_outputSubFunction_tag::libCOL_liftGoingDown:
	case libCOL_outputSubFunction_tag::libCOL_liftIsReserved:
	case libCOL_outputSubFunction_tag::libCOL_liftIsAvailable:
	case libCOL_outputSubFunction_tag::libCOL_liftOverload:
	case libCOL_outputSubFunction_tag::libCOL_liftOutOutOrder:
	case libCOL_outputSubFunction_tag::libCOL_liftInMaintenance:
	case libCOL_outputSubFunction_tag::libCOL_liftInEmergencyOperation:
	case libCOL_outputSubFunction_tag::libCOL_liftOnFiremenService:
	case libCOL_outputSubFunction_tag::libCOL_stayAwayFromDoors:
	case libCOL_outputSubFunction_tag::libCOL_levelAccessProtected:
	case libCOL_outputSubFunction_tag::libCOL_mindTheStep:
	case libCOL_outputSubFunction_tag::libCOL_leaveTheCar:
	case libCOL_outputSubFunction_tag::libCOL_selectDestination:
	case libCOL_outputSubFunction_tag::libCOL_doNotUseThisLift:
	case libCOL_outputSubFunction_tag::libCOL_waitForRescueService:
	case libCOL_outputSubFunction_tag::libCOL_useEmergencyPhone:
	case libCOL_outputSubFunction_tag::libCOL_emergencyCallInProgress:
	case libCOL_outputSubFunction_tag::libCOL_emergencyCallEstablished:
	case libCOL_outputSubFunction_tag::libCOL_stopCurrentAnnouncement:
	default://0x16-0xFE
		break;
	}
}

void CiA417_CmdHandler::execBf_musicPlayback(const virtualIOMapping_data_t &mapData)
{
	switch(mapData.subFunction)
	{
	case libCOL_outputSubFunction_tag::libCOL_switchOffMusic:
	case libCOL_outputSubFunction_tag::libCOL_pauseMusic:
	case libCOL_outputSubFunction_tag::libCOL_resumeMusic:
	case libCOL_outputSubFunction_tag::libCOL_reservedMusic1:
	case libCOL_outputSubFunction_tag::libCOL_reservedMusic2:
	default://0x01-0xFA play music xy
		break;
	}
}

void CiA417_CmdHandler::execBf_miscellaneousOutputs(const virtualIOMapping_data_t &mapData)
{
	switch(mapData.subFunction)
	{
	default:
		break;
	}
}

void CiA417_CmdHandler::execBf_singleFaultIndication(const virtualIOMapping_data_t &mapData)
{
	switch(mapData.subFunction)
	{
	default:
		break;
	}
}

void CiA417_CmdHandler::execBf_nextStop(const virtualIOMapping_data_t &mapData)
{
	switch(mapData.subFunction)
	{
	default:
		break;
	}
}

void CiA417_CmdHandler::execBf_positionIndicationBinary(const virtualIOMapping_data_t &mapData)
{
	switch(mapData.subFunction)
	{
	default:
		break;
	}
}

void CiA417_CmdHandler::execBf_positionIndicationGray(const virtualIOMapping_data_t &mapData)
{
	switch(mapData.subFunction)
	{
	default:
		break;
	}
}

void CiA417_CmdHandler::execBf_positionIndication7Segment(const virtualIOMapping_data_t &mapData)
{
	switch(mapData.subFunction)
	{
	default:
		break;
	}
}

void CiA417_CmdHandler::execBf_vocalFloorsAnnouncementBinary(const virtualIOMapping_data_t &mapData)
{
	switch(mapData.subFunction)
	{
	default:
		break;
	}
}

void CiA417_CmdHandler::execBf_vocalFloorsAnnouncementGray(const virtualIOMapping_data_t &mapData)
{
	switch(mapData.subFunction)
	{
	default:
		break;
	}
}

void CiA417_CmdHandler::execOutputCmd(const virtualIOMapping_data_t &mapData)
{
	switch(mapData.basicFunction)
	{
	case libCOL_of_callControllerCommand:
		execBf_callControllerCommand(mapData);
		break;
	case libCOL_of_genericOutput:
		execBf_genericOutput(mapData);
		break;
	case libCOL_of_hallCallAcknowledgement:
		execBf_hallCallAcknowledgement(mapData);
		break;
	case libCOL_of_lowPriorityHallCallAcknowledgement:
		execBf_lowPriorityHallCallAcknowledgement(mapData);
		break;
	case libCOL_of_highPriorityHallCallAcknowledgement:
		execBf_highPriorityHallCallAcknowledgement(mapData);
		break;
	case libCOL_of_carCallAcknowledgement:
		execBf_carCallAcknowledgement(mapData);
		break;
	case libCOL_of_lowPriorityCarCallAcknowledgement:
		execBf_lowPriorityCarCallAcknowledgement(mapData);
		break;
	case libCOL_of_highPriorityCarCallAcknowledgement:
		execBf_highPriorityCarCallAcknowledgement(mapData);
		break;
	case libCOL_of_destinationCallAcknowledgement:
		execBf_destinationCallAcknowledgement(mapData);
		break;
	case libCOL_of_lowPriorityDestinationCallAcknowledgement:
		execBf_lowPriorityDestinationCallAcknowledgement(mapData);
		break;
	case libCOL_of_highPriorityDestinationCallAcknowledgement:
		execBf_highPriorityDestinationCallAcknowledgement(mapData);
		break;
	case libCOL_of_destinationFloorAcknowledgement:
		execBf_destinationFloorAcknowledgement(mapData);
		break;
	case libCOL_of_lowPriorityDestinationFloorAcknowledgement:
		execBf_lowPriorityDestinationFloorAcknowledgement(mapData);
		break;
	case libCOL_of_highPriorityDestinationFloorAcknowledgement:
		execBf_highPriorityDestinationFloorAcknowledgement(mapData);
		break;
	case libCOL_of_specialFunctionAcknowledgement:
		execBf_specialFunctionAcknowledgement(mapData);
		break;
	case libCOL_of_accessCodeUploadAcknowledgement:
		execBf_accessCodeUploadAcknowledgement(mapData);
		break;
	case libCOL_of_speechConnectionAcknowledgement:
		execBf_speechConnectionAcknowledgement(mapData);
		break;
	case libCOL_of_areaMonitoringConnectionAcknowledgement:
		execBf_areaMonitoringConnectionAcknowledgement(mapData);
		break;
	case libCOL_of_guestCallAcknowledgement:
		execBf_guestCallAcknowledgement(mapData);
		break;
	case libCOL_of_liftLightsAcknowledgement:
		execBf_liftLightsAcknowledgement(mapData);
		break;
	case libCOL_of_positionIndication:
		execBf_positionIndication(mapData);
		break;
	case libCOL_of_hallLantern:
		execBf_hallLantern(mapData);
		break;
	case libCOL_of_directionIndication:
		execBf_directionIndication(mapData);
		break;
	case libCOL_of_specialIndication:
		execBf_specialIndication(mapData);
		break;
	case libCOL_of_arrivalIndication:
		execBf_arrivalIndication(mapData);
		break;
	case libCOL_of_vocalFloorsAnnouncement:
		execBf_vocalFloorsAnnouncement(mapData);
		break;
	case libCOL_of_vocalUserMessage:
		execBf_vocalUserMessage(mapData);
		break;
	case libCOL_of_musicPlayback:
		execBf_musicPlayback(mapData);
		break;
	case libCOL_of_miscellaneousOutputs:
		execBf_miscellaneousOutputs(mapData);
		break;
	case libCOL_of_singleFaultIndication:
		execBf_singleFaultIndication(mapData);
		break;
	case libCOL_of_nextStop:
		execBf_nextStop(mapData);
		break;
	case libCOL_of_positionIndicationBinary:
		execBf_positionIndicationBinary(mapData);
		break;
	case libCOL_of_positionIndicationGray:
		execBf_positionIndicationGray(mapData);
		break;
	case libCOL_of_positionIndication7Segment:
		execBf_positionIndication7Segment(mapData);
		break;
	case libCOL_of_vocalFloorsAnnouncementBinary:
		execBf_vocalFloorsAnnouncementBinary(mapData);
		break;
	case libCOL_of_vocalFloorsAnnouncementGray:
		execBf_vocalFloorsAnnouncementGray(mapData);
		break;
	default:
		break;
	}
}

// -----------------------------------------------------------------------------------
// Input functions for Object 0x6100
// -----------------------------------------------------------------------------------

void CiA417_CmdHandler::execBf_LiftStatusInformationRequest(virtualIOMapping_data_t &mapData)
{

}

void CiA417_CmdHandler::execBf_generic(virtualIOMapping_data_t &mapData)
{

}

void CiA417_CmdHandler::execBf_hallStandard(virtualIOMapping_data_t &mapData)
{

}

void CiA417_CmdHandler::execBf_hallLowPriority(virtualIOMapping_data_t &mapData)
{

}

void CiA417_CmdHandler::execBf_hallHighPriority(virtualIOMapping_data_t &mapData)
{

}

void CiA417_CmdHandler::execBf_carCallStandard(virtualIOMapping_data_t &mapData)
{

}

void CiA417_CmdHandler::execBf_carCallLowPriority(virtualIOMapping_data_t &mapData)
{

}

void CiA417_CmdHandler::execBf_carCallHighPriority(virtualIOMapping_data_t &mapData)
{

}

void CiA417_CmdHandler::execBf_destinationCallStandard(virtualIOMapping_data_t &mapData)
{

}

void CiA417_CmdHandler::execBf_destinationCallLowPriority(virtualIOMapping_data_t &mapData)
{

}

void CiA417_CmdHandler::execBf_destinationCallHighPriority(virtualIOMapping_data_t &mapData)
{

}

void CiA417_CmdHandler::execBf_destinationFloorCallStandard(virtualIOMapping_data_t &mapData)
{

}

void CiA417_CmdHandler::execBf_destinationFloorCallLowPriority(virtualIOMapping_data_t &mapData)
{

}

void CiA417_CmdHandler::execBf_destinationFloorCallHighPriority(virtualIOMapping_data_t &mapData)
{

}

void CiA417_CmdHandler::execBf_specialFunction(virtualIOMapping_data_t &mapData)
{

}

void CiA417_CmdHandler::execBf_accessCodeUpload(virtualIOMapping_data_t &mapData)
{

}

void CiA417_CmdHandler::execBf_speechConnectionRequest(virtualIOMapping_data_t &mapData)
{

}

void CiA417_CmdHandler::execBf_areaMonitoringConnectionRequest(virtualIOMapping_data_t &mapData)
{

}

void CiA417_CmdHandler::execBf_fireDetector(virtualIOMapping_data_t &mapData)
{

}

void CiA417_CmdHandler::execBf_inspectionControlCar(virtualIOMapping_data_t &mapData)
{

}

void CiA417_CmdHandler::execBf_floorSelector(virtualIOMapping_data_t &mapData)
{

}

void CiA417_CmdHandler::execBf_statusSafetyCircuitries(virtualIOMapping_data_t &mapData)
{

}

void CiA417_CmdHandler::execBf_guestCall(virtualIOMapping_data_t &mapData)
{

}

void CiA417_CmdHandler::execBf_liftLights(virtualIOMapping_data_t &mapData)
{

}

void CiA417_CmdHandler::execInputCmd(virtualIOMapping_data_t &mapData)
{
	switch(mapData.basicFunction)
	{
	case libCOL_if_Lift_status_information_request:
		execBf_LiftStatusInformationRequest(mapData);
		break;
	case libCOL_if_generic:
		execBf_generic(mapData);
		break;
	case libCOL_if_hallStandard:
		execBf_hallStandard(mapData);
		break;
	case libCOL_if_hallLowPriority:
		execBf_hallLowPriority(mapData);
		break;
	case libCOL_if_hallHighPriority:
		execBf_hallHighPriority(mapData);
		break;
	case libCOL_if_carCallStandard:
		execBf_carCallStandard(mapData);
		break;
	case libCOL_if_carCallLowPriority:
		execBf_carCallLowPriority(mapData);
		break;
	case libCOL_if_carCallHighPriority:
		execBf_carCallHighPriority(mapData);
		break;
	case libCOL_if_destinationCallStandard:
		execBf_destinationCallStandard(mapData);
		break;
	case libCOL_if_destinationCallLowPriority:
		execBf_destinationCallLowPriority(mapData);
		break;
	case libCOL_if_destinationCallHighPriority:
		execBf_destinationCallHighPriority(mapData);
		break;
	case libCOL_if_destinationFloorCallStandard:
		execBf_destinationFloorCallStandard(mapData);
		break;
	case libCOL_if_destinationFloorCallLowPriority:
		execBf_destinationFloorCallLowPriority(mapData);
		break;
	case libCOL_if_destinationFloorCallHighPriority:
		execBf_destinationFloorCallHighPriority(mapData);
		break;
	case libCOL_if_specialFunction:
		execBf_specialFunction(mapData);
		break;
	case libCOL_if_accessCodeUpload:
		execBf_accessCodeUpload(mapData);
		break;
	case libCOL_if_speechConnectionRequest:
		execBf_speechConnectionRequest(mapData);
		break;
	case libCOL_if_areaMonitoringConnectionRequest:
		execBf_areaMonitoringConnectionRequest(mapData);
		break;
	case libCOL_if_fireDetector:
		execBf_fireDetector(mapData);
		break;
	case libCOL_if_inspectionControlCar:
		execBf_inspectionControlCar(mapData);
		break;
	case libCOL_if_floorSelector:
		execBf_floorSelector(mapData);
		break;
	case libCOL_if_statusSafetyCircuitries:
		execBf_statusSafetyCircuitries(mapData);
		break;
	case libCOL_if_guestCall:
		execBf_guestCall(mapData);
		break;
	case libCOL_if_liftLights:
		execBf_liftLights(mapData);
		break;
	default:
		break;
	}
}


