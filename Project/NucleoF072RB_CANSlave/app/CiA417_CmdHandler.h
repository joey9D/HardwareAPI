/*
 * CiA417_CmdHandler.h
 *
 *  Created on: Jan 30, 2024
 *      Author: michael.grathwohl
 */

#ifndef CIA417_CMDHANDLER_H_
#define CIA417_CMDHANDLER_H_

#include "CiA417_VirtualIOMapping.h"

class CiA417_CmdHandler
{
public:
	CiA417_CmdHandler() = default;
	virtual ~CiA417_CmdHandler() = default;

	void switchCmdToAlternative(virtualIOMapping_data_t &mapData);
	void execOutputCmd(const virtualIOMapping_data_t &mapData);
	void execInputCmd(virtualIOMapping_data_t &mapData);

private:

	// -----------------------------------------------------------------------------------
	// Output functions for Object 0x6200
	// -----------------------------------------------------------------------------------
	void execBf_callControllerCommand(const virtualIOMapping_data_t &mapData);
	void execBf_genericOutput(const virtualIOMapping_data_t &mapData);
	void execBf_hallCallAcknowledgement(const virtualIOMapping_data_t &mapData);
	void execBf_lowPriorityHallCallAcknowledgement(const virtualIOMapping_data_t &mapData);
	void execBf_highPriorityHallCallAcknowledgement(const virtualIOMapping_data_t &mapData);
	void execBf_carCallAcknowledgement(const virtualIOMapping_data_t &mapData);
	void execBf_lowPriorityCarCallAcknowledgement(const virtualIOMapping_data_t &mapData);
	void execBf_highPriorityCarCallAcknowledgement(const virtualIOMapping_data_t &mapData);
	void execBf_destinationCallAcknowledgement(const virtualIOMapping_data_t &mapData);
	void execBf_lowPriorityDestinationCallAcknowledgement(const virtualIOMapping_data_t &mapData);
	void execBf_highPriorityDestinationCallAcknowledgement(const virtualIOMapping_data_t &mapData);
	void execBf_destinationFloorAcknowledgement(const virtualIOMapping_data_t &mapData);
	void execBf_lowPriorityDestinationFloorAcknowledgement(const virtualIOMapping_data_t &mapData);
	void execBf_highPriorityDestinationFloorAcknowledgement(const virtualIOMapping_data_t &mapData);
	void execBf_specialFunctionAcknowledgement(const virtualIOMapping_data_t &mapData);
	void execBf_accessCodeUploadAcknowledgement(const virtualIOMapping_data_t &mapData);
	void execBf_speechConnectionAcknowledgement(const virtualIOMapping_data_t &mapData);
	void execBf_areaMonitoringConnectionAcknowledgement(const virtualIOMapping_data_t &mapData);
	void execBf_guestCallAcknowledgement(const virtualIOMapping_data_t &mapData);
	void execBf_liftLightsAcknowledgement(const virtualIOMapping_data_t &mapData);
	void execBf_positionIndication(const virtualIOMapping_data_t &mapData);
	void execBf_hallLantern(const virtualIOMapping_data_t &mapData);
	void execBf_directionIndication(const virtualIOMapping_data_t &mapData);
	void execBf_specialIndication(const virtualIOMapping_data_t &mapData);
	void execBf_arrivalIndication(const virtualIOMapping_data_t &mapData);
	void execBf_vocalFloorsAnnouncement(const virtualIOMapping_data_t &mapData);
	void execBf_vocalUserMessage(const virtualIOMapping_data_t &mapData);
	void execBf_musicPlayback(const virtualIOMapping_data_t &mapData);
	void execBf_miscellaneousOutputs(const virtualIOMapping_data_t &mapData);
	void execBf_singleFaultIndication(const virtualIOMapping_data_t &mapData);
	void execBf_nextStop(const virtualIOMapping_data_t &mapData);
	void execBf_positionIndicationBinary(const virtualIOMapping_data_t &mapData);
	void execBf_positionIndicationGray(const virtualIOMapping_data_t &mapData);
	void execBf_positionIndication7Segment(const virtualIOMapping_data_t &mapData);
	void execBf_vocalFloorsAnnouncementBinary(const virtualIOMapping_data_t &mapData);
	void execBf_vocalFloorsAnnouncementGray(const virtualIOMapping_data_t &mapData);
	// -----------------------------------------------------------------------------------
	// Input functions for Object 0x6100
	// -----------------------------------------------------------------------------------
	void execBf_LiftStatusInformationRequest(virtualIOMapping_data_t &mapData);
	void execBf_generic(virtualIOMapping_data_t &mapData);
	void execBf_hallStandard(virtualIOMapping_data_t &mapData);
	void execBf_hallLowPriority(virtualIOMapping_data_t &mapData);
	void execBf_hallHighPriority(virtualIOMapping_data_t &mapData);
	void execBf_carCallStandard(virtualIOMapping_data_t &mapData);
	void execBf_carCallLowPriority(virtualIOMapping_data_t &mapData);
	void execBf_carCallHighPriority(virtualIOMapping_data_t &mapData);
	void execBf_destinationCallStandard(virtualIOMapping_data_t &mapData);
	void execBf_destinationCallLowPriority(virtualIOMapping_data_t &mapData);
	void execBf_destinationCallHighPriority(virtualIOMapping_data_t &mapData);
	void execBf_destinationFloorCallStandard(virtualIOMapping_data_t &mapData);
	void execBf_destinationFloorCallLowPriority(virtualIOMapping_data_t &mapData);
	void execBf_destinationFloorCallHighPriority(virtualIOMapping_data_t &mapData);
	void execBf_specialFunction(virtualIOMapping_data_t &mapData);
	void execBf_accessCodeUpload(virtualIOMapping_data_t &mapData);
	void execBf_speechConnectionRequest(virtualIOMapping_data_t &mapData);
	void execBf_areaMonitoringConnectionRequest(virtualIOMapping_data_t &mapData);
	void execBf_fireDetector(virtualIOMapping_data_t &mapData);
	void execBf_inspectionControlCar(virtualIOMapping_data_t &mapData);
	void execBf_floorSelector(virtualIOMapping_data_t &mapData);
	void execBf_statusSafetyCircuitries(virtualIOMapping_data_t &mapData);
	void execBf_guestCall(virtualIOMapping_data_t &mapData);
	void execBf_liftLights(virtualIOMapping_data_t &mapData);
};

#endif /* CIA417_CMDHANDLER_H_ */
