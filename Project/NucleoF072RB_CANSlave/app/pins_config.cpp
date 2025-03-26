#include "pins_config.h"


bool pins_config::getSevenSegmentState(uint8_t subData, uint8_t subMask)
{
    //TODO: Check where the values are from, what is actually done in this function and update code and documentation accordingly
    //Currently mostly copied from old firmware
    uint8_t displayIndex, displayValue, segmentNumber;
    uint8_t rest, div, higherDiv;

    rest = subData;
    for(uint8_t displayIndex = 3; displayIndex > 0; displayIndex--)
    {
        div = seven_segment_pos[displayIndex - 1]; //Place value
        higherDiv = seven_segment_pos[displayIndex]; //Next place value

        //Calculate display value
        displayValue = rest / div;

        if((displayValue >= 0) && (displayValue <= 9)) //Display value is between 0 and 9 (decimal digits)
        {
            rest = rest % div;

            segmentNumber = subMask - (8 * (displayIndex - 1)); //Check if current output is assigned to the current place value
            if((segmentNumber >= 1) && (segmentNumber <= 7)) //Segment a = 1, b = 2, ...., g = 7
            {
                if((1 << (segmentNumber - 1)) & seven_segment_table[displayValue]) //Compare with reference table
                {
                    return ((displayValue != 0) || (subData >= higherDiv));
                }
            }
            else if(segmentNumber == 8)
            {
                //Dot -> no definition for dot until CiA417 V2.0.2
            }
            else
            {
                //Invalid value
            }
        }
    }
    return false;
}


bool pins_config::getInputCycled(libCOL_inputBasicFunction_t baseFunc, libCOL_inputSubfunction_t subFunc)
{
    //Fire Alarms need to be broadcasted regularly
    switch(baseFunc) {
        case libCOL_if_specialFunction: // 0x0E
            return ((subFunc.special == 0x0B) || (subFunc.special == 0x0C) || (subFunc.special == 0x17));
        case libCOL_if_fireDetector: // 0x12
            return true;
        case libCOL_if_generic: // 0x01
        case libCOL_if_hallStandard: // 0x02
        case libCOL_if_hallLowPriority: // 0x03
        case libCOL_if_hallHighPriority: // 0x04
        case libCOL_if_carCallStandard: // 0x05
        case libCOL_if_carCallLowPriority: // 0x06
        case libCOL_if_carCallHighPriority: // 0x07
        case libCOL_if_destinationCallStandard: // 0x08
        case libCOL_if_destinationCallLowPriority: // 0x09
        case libCOL_if_destinationCallHighPriority: // 0x0A
        case libCOL_if_destinationFloorCallStandard: // 0x0B
        case libCOL_if_destinationFloorCallLowPriority: // 0x0C
        case libCOL_if_destinationFloorCallHighPriority: // 0x0D
        case libCOL_if_accessCodeUpload: // 0x0F
        case libCOL_if_speechConnectionRequest: // 0x10
        case libCOL_if_areaMonitoringConnectionRequest: // 0x11
        case libCOL_if_inspectionControlCar: // 0x13
        case libCOL_if_floorSelector: // 0x15
        case libCOL_if_statusSafetyCircuitries: // 0x16
        case libCOL_if_guestCall: // 0x20
        case libCOL_if_liftLights: // 0x3F
                return false;
            default:
                return false;
    }

}


bool pins_config::getInputCall(libCOL_inputBasicFunction_t baseFunc)
{
    switch(baseFunc) {
        case libCOL_if_hallStandard: // 0x02
        case libCOL_if_hallLowPriority: // 0x03
        case libCOL_if_hallHighPriority: // 0x04
        case libCOL_if_carCallStandard: // 0x05
        case libCOL_if_carCallLowPriority: // 0x06
        case libCOL_if_carCallHighPriority: // 0x07
        case libCOL_if_destinationCallStandard: // 0x08
        case libCOL_if_destinationCallLowPriority: // 0x09
        case libCOL_if_destinationCallHighPriority: // 0x0A
        case libCOL_if_destinationFloorCallStandard: // 0x0B
        case libCOL_if_destinationFloorCallLowPriority: // 0x0C
        case libCOL_if_destinationFloorCallHighPriority: // 0x0D
            return true;
        case libCOL_if_generic: // 0x01
        case libCOL_if_specialFunction: // 0x0E
        case libCOL_if_accessCodeUpload: // 0x0F
        case libCOL_if_speechConnectionRequest: // 0x10
        case libCOL_if_areaMonitoringConnectionRequest: // 0x11
        case libCOL_if_fireDetector: // 0x12
        case libCOL_if_inspectionControlCar: // 0x13
        case libCOL_if_floorSelector: // 0x15
        case libCOL_if_statusSafetyCircuitries: // 0x16
        case libCOL_if_guestCall: // 0x20
        case libCOL_if_liftLights: // 0x3F
                return false;
            default:
                return false;
    }


}

bool pins_config::getOutputLiftMatch(libCOL_outputBasicFunction_t baseFunc, libCOL_outputLift_t localLift, libCOL_outputLift_t lift, libCOL_outputSubFunction_t subFunc)
{
    switch(baseFunc) {
        case libCOL_of_genericOutput:  //0x1
        case libCOL_of_hallCallAcknowledgement: //0x2
        case libCOL_of_lowPriorityHallCallAcknowledgement: //0x3
        case libCOL_of_highPriorityHallCallAcknowledgement: //0x4
        case libCOL_of_carCallAcknowledgement: //0x5
        case libCOL_of_lowPriorityCarCallAcknowledgement: //0x6
        case libCOL_of_highPriorityCarCallAcknowledgement: //0x7
        case libCOL_of_destinationCallAcknowledgement: //0x8
        case libCOL_of_lowPriorityDestinationCallAcknowledgement: //0x9
        case libCOL_of_highPriorityDestinationCallAcknowledgement: //0xA
        case libCOL_of_destinationFloorAcknowledgement: //0xB
        case libCOL_of_lowPriorityDestinationFloorAcknowledgement: //0xC
        case libCOL_of_highPriorityDestinationFloorAcknowledgement: //0xD
        case libCOL_of_specialFunctionAcknowledgement: //0xE
        case libCOL_of_accessCodeUploadAcknowledgement: //0xF
        case libCOL_of_speechConnectionAcknowledgement: //0x10
        case libCOL_of_areaMonitoringConnectionAcknowledgement: //0x11
        case libCOL_of_guestCallAcknowledgement: //0x20
        case libCOL_of_liftLightsAcknowledgement: //0x3F
        case libCOL_of_hallLantern: //0x41
        case libCOL_of_directionIndication: //0x42
        case libCOL_of_specialIndication: //0x43
        case libCOL_of_arrivalIndication: //0x44
        case libCOL_of_vocalUserMessage: //0x48
        case libCOL_of_musicPlayback: //0x49
        case libCOL_of_miscellaneousOutputs: //0x4A
        case libCOL_of_singleFaultIndication: //0x4B
        case libCOL_of_nextStop: //0x4C
            return (localLift.raw & lift.raw) > 0;
        case libCOL_of_positionIndication: //0x40
        case libCOL_of_positionIndicationBinary: // 0x80
        case libCOL_of_positionIndicationGray: // 0x81
        case libCOL_of_positionIndication7Segment: // 0x83
            return (localLift.raw == lift.raw);
        case libCOL_of_vocalFloorsAnnouncement: //0x47
        case libCOL_of_vocalFloorsAnnouncementBinary: // 0x86
        case libCOL_of_vocalFloorsAnnouncementGray: // 0x87
            if (subFunc.raw == 0xFF) {
                return (localLift.raw & lift.raw) > 0;
            } else {
                return (localLift.raw == lift.raw);
            }
        case libCOL_of_callControllerCommand: //0x0
        default:
            return (localLift.raw & lift.raw) > 0;
    }

}

bool pins_config::getOutputFloorMatch(libCOL_outputBasicFunction_t baseFunc, uint8_t localFloor, uint8_t floor, libCOL_outputSubFunction_t subFunc)
{
    switch(baseFunc) {
        case libCOL_of_genericOutput:  //0x1
        case libCOL_of_hallCallAcknowledgement: //0x2
        	return ((localFloor == floor) || floor == 0xFF || localFloor == 0xFF);
        case libCOL_of_lowPriorityHallCallAcknowledgement: //0x3
        case libCOL_of_highPriorityHallCallAcknowledgement: //0x4
        case libCOL_of_carCallAcknowledgement: //0x5
        	return ((localFloor == floor) || floor == 0xFF || localFloor == 0xFF);
        case libCOL_of_lowPriorityCarCallAcknowledgement: //0x6
        case libCOL_of_highPriorityCarCallAcknowledgement: //0x7
        case libCOL_of_destinationCallAcknowledgement: //0x8
        case libCOL_of_lowPriorityDestinationCallAcknowledgement: //0x9
        case libCOL_of_highPriorityDestinationCallAcknowledgement: //0xA
        case libCOL_of_destinationFloorAcknowledgement: //0xB
        case libCOL_of_lowPriorityDestinationFloorAcknowledgement: //0xC
        case libCOL_of_highPriorityDestinationFloorAcknowledgement: //0xD
        case libCOL_of_specialFunctionAcknowledgement: //0xE
        	return ((localFloor == floor) || floor == 0xFF || localFloor == 0xFF);
        case libCOL_of_accessCodeUploadAcknowledgement: //0xF
        case libCOL_of_speechConnectionAcknowledgement: //0x10
        case libCOL_of_areaMonitoringConnectionAcknowledgement: //0x11
        case libCOL_of_guestCallAcknowledgement: //0x20
        case libCOL_of_liftLightsAcknowledgement: //0x3F
        case libCOL_of_hallLantern: //0x41
        	return ((localFloor == floor) || floor == 0xFF || localFloor == 0xFF);
        case libCOL_of_directionIndication: //0x42
        	return ((localFloor == floor) || floor == 0xFF || localFloor == 0xFF);
        case libCOL_of_specialIndication: //0x43
        case libCOL_of_vocalUserMessage: //0x48
        case libCOL_of_musicPlayback: //0x49
        case libCOL_of_miscellaneousOutputs: //0x4A
        case libCOL_of_singleFaultIndication: //0x4B
        case libCOL_of_nextStop: //0x4C
            //return ((localFloor == floor) || floor == 0xFF || localFloor == 0xFF);
        	/* RSC: The rule shall be: The floor might be a match or the configured floor is 'all floors' and the
        	 *      lift sends 'any floor' but not the car (floor==0) or the configured floor is any floor but not
        	 *      the car and the controller transmits 'all floors'. */
        	return (((localFloor == floor) || ((floor == 0xFF) && (localFloor)) || ((floor) && (localFloor == 0xFF))) ? 1 : 0);
        case libCOL_of_arrivalIndication: //0x44
            //return ((localFloor == floor) || localFloor == 0 || localFloor == 0xFF); //TODO: Check this ???
        	/* RSC: The rule shall be: The floor might be a match or the configured floor is 'all floors' and the
        	 *      lift sends 'any floor' but not the car (floor==0) or the configured floor is any floor but not
        	 *      the car and the controller transmits 'all floors'. */
        	return (((localFloor == floor) || ((floor == 0xFF) && (localFloor)) || ((floor) && (localFloor == 0xFF))) ? 1 : 0);
        case libCOL_of_positionIndication: //0x40
        	return ((localFloor == floor) || floor == 0xFF || localFloor == 0xFF);
        case libCOL_of_positionIndicationBinary: // 0x80
        case libCOL_of_positionIndicationGray: // 0x81
        case libCOL_of_positionIndication7Segment: // 0x83
            return true;
        case libCOL_of_vocalFloorsAnnouncement: //0x47
        case libCOL_of_vocalFloorsAnnouncementBinary: // 0x86
        case libCOL_of_vocalFloorsAnnouncementGray: // 0x87
            if (subFunc.raw == 0xFF) {
                return ((localFloor == floor) || floor == 0xFF || localFloor == 0xFF);
            } else {
                return true;
            }
        case libCOL_of_callControllerCommand: //0x0
        default:
            //return ((localFloor == floor) || localFloor == 0 || localFloor == 0xFF); //TODO: Check this ???
        	/* RSC: The rule shall be: The floor might be a match or the configured floor is 'all floors' and the
        	 *      lift sends 'any floor' but not the car (floor==0) or the configured floor is any floor but not
        	 *      the car and the controller transmits 'all floors'. */
        	return (((localFloor == floor) || ((floor == 0xFF) && (localFloor)) || ((floor) && (localFloor == 0xFF))) ? 1 : 0);
    }
}

bool pins_config::getOutputDoorMatch(libCOL_outputBasicFunction_t baseFunc, libCOL_outputDoor_t localDoor, libCOL_outputDoor_t door, uint8_t floor, libCOL_outputSubFunction_t subFunc)
{
    switch(baseFunc) {
        case libCOL_of_genericOutput:  //0x1
        case libCOL_of_hallCallAcknowledgement: //0x2
        case libCOL_of_lowPriorityHallCallAcknowledgement: //0x3
        case libCOL_of_highPriorityHallCallAcknowledgement: //0x4
            return ((localDoor.raw & door.raw) > 0);
        case libCOL_of_carCallAcknowledgement: //0x5
        case libCOL_of_lowPriorityCarCallAcknowledgement: //0x6
        case libCOL_of_highPriorityCarCallAcknowledgement: //0x7
        case libCOL_of_destinationCallAcknowledgement: //0x8
        case libCOL_of_lowPriorityDestinationCallAcknowledgement: //0x9
        case libCOL_of_highPriorityDestinationCallAcknowledgement: //0xA
        case libCOL_of_destinationFloorAcknowledgement: //0xB
        case libCOL_of_lowPriorityDestinationFloorAcknowledgement: //0xC
        case libCOL_of_highPriorityDestinationFloorAcknowledgement: //0xD
            return ((localDoor.raw & door.raw & 0xF) > 0);
        case libCOL_of_specialFunctionAcknowledgement: //0xE
        	return (((localDoor.raw & door.raw) > 0) || door.raw == 0xFF);
        case libCOL_of_accessCodeUploadAcknowledgement: //0xF
        case libCOL_of_speechConnectionAcknowledgement: //0x10
        case libCOL_of_areaMonitoringConnectionAcknowledgement: //0x11
        case libCOL_of_guestCallAcknowledgement: //0x20
        case libCOL_of_liftLightsAcknowledgement: //0x3F
        case libCOL_of_hallLantern: //0x41
        case libCOL_of_directionIndication: //0x42
        case libCOL_of_specialIndication: //0x43
        case libCOL_of_arrivalIndication: //0x44
        case libCOL_of_vocalUserMessage: //0x48
        case libCOL_of_musicPlayback: //0x49
        case libCOL_of_miscellaneousOutputs: //0x4A
        case libCOL_of_singleFaultIndication: //0x4B
            if (floor == 0) {
                return ((localDoor.raw == door.raw) || door.raw == 0xFF);
            } else {
                return (((localDoor.raw & door.raw) > 0) || door.raw == 0xFF);
            }
        case libCOL_of_positionIndication: //0x40
        case libCOL_of_positionIndicationBinary: // 0x80
        case libCOL_of_positionIndicationGray: // 0x81
        case libCOL_of_positionIndication7Segment: // 0x83
            return true;
        case libCOL_of_vocalFloorsAnnouncement: //0x47
        case libCOL_of_vocalFloorsAnnouncementBinary: // 0x86
        case libCOL_of_vocalFloorsAnnouncementGray: // 0x87
            if (subFunc.raw == 0xFF) {
                if (floor == 0) {
                    return ((localDoor.raw == door.raw) || door.raw == 0xFF);
                } else {
                    return (((localDoor.raw & door.raw) > 0) || door.raw == 0xFF);
                }
            } else {
                return true;
            }
        case libCOL_of_callControllerCommand: //0x0
        case libCOL_of_nextStop: //0x4C
        default:
            return ((localDoor.raw & door.raw) > 0);
            //return false;
    }
}

uint8_t pins_config::getOutputSubFunctionData(libCOL_outputBasicFunction_t baseFunc, libCOL_outputFunctionData_t data, uint8_t subData, libCOL_outputSubFunction_t subFunc, libCOL_outputLift_t lift)
{
    switch(baseFunc) {
        case libCOL_of_hallCallAcknowledgement: //0x2
        case libCOL_of_lowPriorityHallCallAcknowledgement: //0x3
        case libCOL_of_highPriorityHallCallAcknowledgement: //0x4
        case libCOL_of_destinationFloorAcknowledgement: //0xB
        case libCOL_of_lowPriorityDestinationFloorAcknowledgement: //0xC
        case libCOL_of_highPriorityDestinationFloorAcknowledgement: //0xD:
        case libCOL_of_specialFunctionAcknowledgement: //0xE
            if (data.generic.status) {
                return (subData | lift.raw);
            } else {
                return (subData & ~lift.raw);
            }
        case libCOL_of_specialIndication: //0x43
            if (subFunc.specialIndication == libCOL_outputSubFunction_t::libCOL_specialIndication_outOfOrder) {
                return subData; //Set by updateLift
            } else {
                if (data.generic.status) {
                    return (subData | lift.raw);
                } else {
                    return (subData & ~lift.raw);
                }
            }
        case libCOL_of_positionIndication: //0x40
        	return subFunc.raw;
        case libCOL_of_vocalFloorsAnnouncement: //0x47
        case libCOL_of_positionIndicationBinary: // 0x80
        	return subFunc.raw;
        case libCOL_of_positionIndicationGray: // 0x81
        	return subFunc.raw;
        case libCOL_of_positionIndication7Segment: // 0x83
        case libCOL_of_vocalFloorsAnnouncementBinary: // 0x86
        case libCOL_of_vocalFloorsAnnouncementGray: // 0x87
            if (data.generic.status) {
                return subFunc.raw;
            } else {
                return 0;
            }
        case libCOL_of_directionIndication: //0x42
            if (data.generic.status) {
                if (((subData | subFunc.raw) == 0x13) | ((subData | subFunc.raw) == 0x10)) {
                    return subData;
                } else {
                    return (subData | subFunc.raw);
                }
            } else {
                subData &= ~subFunc.raw;
                if (subData == 0x10) {
                    return 0;
                } else {
                    return subData;
                }
            }
        case libCOL_of_hallLantern: //0x41
        case libCOL_of_arrivalIndication: //0x44
            if (data.generic.status) {
                return (subData | subFunc.raw);
            } else {
                return (subData & ~subFunc.raw);
            }
        case libCOL_of_genericOutput:  //0x1
        case libCOL_of_carCallAcknowledgement: //0x5
        case libCOL_of_lowPriorityCarCallAcknowledgement: //0x6
        case libCOL_of_highPriorityCarCallAcknowledgement: //0x7
        case libCOL_of_destinationCallAcknowledgement: //0x8
        case libCOL_of_lowPriorityDestinationCallAcknowledgement: //0x9
        case libCOL_of_highPriorityDestinationCallAcknowledgement: //0xA
        case libCOL_of_accessCodeUploadAcknowledgement: //0xF
        case libCOL_of_speechConnectionAcknowledgement: //0x10
        case libCOL_of_areaMonitoringConnectionAcknowledgement: //0x11
        case libCOL_of_vocalUserMessage: //0x48
        case libCOL_of_callControllerCommand: //0x0
        case libCOL_of_guestCallAcknowledgement: //0x20
        case libCOL_of_liftLightsAcknowledgement: //0x3F
        case libCOL_of_musicPlayback: //0x49
        case libCOL_of_miscellaneousOutputs: //0x4A
        case libCOL_of_singleFaultIndication: //0x4B
        case libCOL_of_nextStop: //0x4C
        default:
            return 0;
    }
}

bool pins_config::getOutputSubFunctionMatch(libCOL_outputBasicFunction_t baseFunc, libCOL_outputSubFunction_t localSubFunc, libCOL_outputSubFunction_t subFunc)
{
    switch(baseFunc) {
        case libCOL_of_genericOutput:  //0x1
        case libCOL_of_hallCallAcknowledgement: //0x2
        case libCOL_of_lowPriorityHallCallAcknowledgement: //0x3
        case libCOL_of_highPriorityHallCallAcknowledgement: //0x4
        case libCOL_of_specialFunctionAcknowledgement: //0xE
        case libCOL_of_accessCodeUploadAcknowledgement: //0xF
        case libCOL_of_speechConnectionAcknowledgement: //0x10
        case libCOL_of_areaMonitoringConnectionAcknowledgement: //0x11
        case libCOL_of_guestCallAcknowledgement: //0x20
        case libCOL_of_liftLightsAcknowledgement: //0x3F
        case libCOL_of_vocalUserMessage: //0x48
        case libCOL_of_musicPlayback: //0x49
        case libCOL_of_miscellaneousOutputs: //0x4A
        case libCOL_of_singleFaultIndication: //0x4B
        case libCOL_of_nextStop: //0x4C
            return (localSubFunc.raw == subFunc.raw);
        case libCOL_of_carCallAcknowledgement: //0x5
        case libCOL_of_lowPriorityCarCallAcknowledgement: //0x6
        case libCOL_of_highPriorityCarCallAcknowledgement: //0x7
        case libCOL_of_destinationCallAcknowledgement: //0x8
        case libCOL_of_lowPriorityDestinationCallAcknowledgement: //0x9
        case libCOL_of_highPriorityDestinationCallAcknowledgement: //0xA
        case libCOL_of_destinationFloorAcknowledgement: //0xB
        case libCOL_of_lowPriorityDestinationFloorAcknowledgement: //0xC
        case libCOL_of_highPriorityDestinationFloorAcknowledgement: //0xD
            return ((localSubFunc.raw == subFunc.raw) || (subFunc.raw == 0xFF));
        case libCOL_of_specialIndication: //0x43
            return ((localSubFunc.raw == subFunc.raw) || (subFunc.raw == 0));
        case libCOL_of_positionIndication: //0x40
        case libCOL_of_positionIndicationBinary: // 0x80
        case libCOL_of_positionIndicationGray: // 0x81
        case libCOL_of_positionIndication7Segment: // 0x83
            return true;
        case libCOL_of_vocalFloorsAnnouncement: //0x47
        case libCOL_of_vocalFloorsAnnouncementBinary: // 0x86
        case libCOL_of_vocalFloorsAnnouncementGray: // 0x87
            return (((subFunc.raw != 0xFF) && (localSubFunc.raw != 0xFF)) || ((subFunc.raw == 0xFF) && (localSubFunc.raw == 0xFF)));
        case libCOL_of_hallLantern: //0x41
        case libCOL_of_directionIndication: //0x42
        case libCOL_of_arrivalIndication: //0x44
            return ((localSubFunc.raw & subFunc.raw) > 0);
        case libCOL_of_callControllerCommand: //0x0
        default:
            return (localSubFunc.raw == subFunc.raw);
    }
}



clamp_output_type_t pins_config::getOutputType(libCOL_outputBasicFunction_t baseFunc)
{
    switch(baseFunc) {
        case libCOL_of_callControllerCommand: //0x0
        case libCOL_of_genericOutput:  //0x1
        case libCOL_of_hallCallAcknowledgement: //0x2
        case libCOL_of_lowPriorityHallCallAcknowledgement: //0x3
        case libCOL_of_highPriorityHallCallAcknowledgement: //0x4
        case libCOL_of_carCallAcknowledgement: //0x5
        case libCOL_of_lowPriorityCarCallAcknowledgement: //0x6
        case libCOL_of_highPriorityCarCallAcknowledgement: //0x7
        case libCOL_of_destinationCallAcknowledgement: //0x8
        case libCOL_of_lowPriorityDestinationCallAcknowledgement: //0x9
        case libCOL_of_highPriorityDestinationCallAcknowledgement: //0xA
        case libCOL_of_destinationFloorAcknowledgement: //0xB
        case libCOL_of_lowPriorityDestinationFloorAcknowledgement: //0xC
        case libCOL_of_highPriorityDestinationFloorAcknowledgement: //0xD
        case libCOL_of_specialFunctionAcknowledgement: //0xE
        case libCOL_of_accessCodeUploadAcknowledgement: //0xF
        case libCOL_of_speechConnectionAcknowledgement: //0x10
        case libCOL_of_areaMonitoringConnectionAcknowledgement: //0x11
        case libCOL_of_guestCallAcknowledgement: //0x20
        case libCOL_of_liftLightsAcknowledgement: //0x3F
        case libCOL_of_positionIndication: //0x40
        case libCOL_of_hallLantern: //0x41
        case libCOL_of_directionIndication: //0x42
        case libCOL_of_specialIndication: //0x43
        case libCOL_of_arrivalIndication: //0x44
        case libCOL_of_vocalFloorsAnnouncement: //0x47
        case libCOL_of_vocalUserMessage: //0x48
        case libCOL_of_musicPlayback: //0x49
        case libCOL_of_miscellaneousOutputs: //0x4A
        case libCOL_of_singleFaultIndication: //0x4B
        case libCOL_of_nextStop: //0x4C
            return clamp_output_type_1ofN;
        case libCOL_of_positionIndicationBinary: // 0x80
        case libCOL_of_vocalFloorsAnnouncementBinary: // 0x86
            return clamp_output_type_binary;
        case libCOL_of_positionIndicationGray: // 0x81
        case libCOL_of_vocalFloorsAnnouncementGray: // 0x87
            return clamp_output_type_gray;
        case libCOL_of_positionIndication7Segment: // 0x83
            return clamp_output_type_7segment;
        default:
            return clamp_output_type_1ofN;
    }
}

bool pins_config::getOutputCall(libCOL_outputBasicFunction_t baseFunc)
{
    switch(baseFunc) {
        case libCOL_of_hallCallAcknowledgement: //0x2
        case libCOL_of_lowPriorityHallCallAcknowledgement: //0x3
        case libCOL_of_highPriorityHallCallAcknowledgement: //0x4
        case libCOL_of_carCallAcknowledgement: //0x5
        case libCOL_of_lowPriorityCarCallAcknowledgement: //0x6
        case libCOL_of_highPriorityCarCallAcknowledgement: //0x7
        case libCOL_of_destinationCallAcknowledgement: //0x8
        case libCOL_of_lowPriorityDestinationCallAcknowledgement: //0x9
        case libCOL_of_highPriorityDestinationCallAcknowledgement: //0xA
        case libCOL_of_destinationFloorAcknowledgement: //0xB
        case libCOL_of_lowPriorityDestinationFloorAcknowledgement: //0xC
        case libCOL_of_highPriorityDestinationFloorAcknowledgement: //0xD
            return true;
        case libCOL_of_callControllerCommand: //0x0
        case libCOL_of_genericOutput:  //0x1
        case libCOL_of_specialFunctionAcknowledgement: //0xE
        case libCOL_of_accessCodeUploadAcknowledgement: //0xF
        case libCOL_of_speechConnectionAcknowledgement: //0x10
        case libCOL_of_areaMonitoringConnectionAcknowledgement: //0x11
        case libCOL_of_guestCallAcknowledgement: //0x20
        case libCOL_of_liftLightsAcknowledgement: //0x3F
        case libCOL_of_positionIndication: //0x40
        case libCOL_of_hallLantern: //0x41
        case libCOL_of_directionIndication: //0x42
        case libCOL_of_specialIndication: //0x43
        case libCOL_of_arrivalIndication: //0x44
        case libCOL_of_vocalFloorsAnnouncement: //0x47
        case libCOL_of_vocalUserMessage: //0x48
        case libCOL_of_musicPlayback: //0x49
        case libCOL_of_miscellaneousOutputs: //0x4A
        case libCOL_of_singleFaultIndication: //0x4B
        case libCOL_of_nextStop: //0x4C
        case libCOL_of_positionIndicationBinary: // 0x80
        case libCOL_of_vocalFloorsAnnouncementBinary: // 0x86
        case libCOL_of_positionIndicationGray: // 0x81
        case libCOL_of_vocalFloorsAnnouncementGray: // 0x87
        case libCOL_of_positionIndication7Segment: // 0x83
            return false;
        default:
            return false;
    }
}

bool pins_config::getOutputSpecialFunctionData(libCOL_outputBasicFunction_t baseFunc)
{
    switch(baseFunc) {
        case libCOL_of_destinationCallAcknowledgement: //0x8
        case libCOL_of_lowPriorityDestinationCallAcknowledgement: //0x9
        case libCOL_of_highPriorityDestinationCallAcknowledgement: //0xA
        case libCOL_of_accessCodeUploadAcknowledgement: //0xF
            return true;
        case libCOL_of_callControllerCommand: //0x0
        case libCOL_of_genericOutput:  //0x1
        case libCOL_of_hallCallAcknowledgement: //0x2
        case libCOL_of_lowPriorityHallCallAcknowledgement: //0x3
        case libCOL_of_highPriorityHallCallAcknowledgement: //0x4
        case libCOL_of_carCallAcknowledgement: //0x5
        case libCOL_of_lowPriorityCarCallAcknowledgement: //0x6
        case libCOL_of_highPriorityCarCallAcknowledgement: //0x7
        case libCOL_of_destinationFloorAcknowledgement: //0xB
        case libCOL_of_lowPriorityDestinationFloorAcknowledgement: //0xC
        case libCOL_of_highPriorityDestinationFloorAcknowledgement: //0xD
        case libCOL_of_specialFunctionAcknowledgement: //0xE
        case libCOL_of_speechConnectionAcknowledgement: //0x10
        case libCOL_of_areaMonitoringConnectionAcknowledgement: //0x11
        case libCOL_of_guestCallAcknowledgement: //0x20
        case libCOL_of_liftLightsAcknowledgement: //0x3F
        case libCOL_of_positionIndication: //0x40
        case libCOL_of_hallLantern: //0x41
        case libCOL_of_directionIndication: //0x42
        case libCOL_of_specialIndication: //0x43
        case libCOL_of_arrivalIndication: //0x44
        case libCOL_of_vocalFloorsAnnouncement: //0x47
        case libCOL_of_vocalUserMessage: //0x48
        case libCOL_of_musicPlayback: //0x49
        case libCOL_of_miscellaneousOutputs: //0x4A
        case libCOL_of_singleFaultIndication: //0x4B
        case libCOL_of_nextStop: //0x4C
        case libCOL_of_positionIndicationBinary: // 0x80
        case libCOL_of_vocalFloorsAnnouncementBinary: // 0x86
        case libCOL_of_positionIndicationGray: // 0x81
        case libCOL_of_vocalFloorsAnnouncementGray: // 0x87
        case libCOL_of_positionIndication7Segment: // 0x83
            return false;
        default:
            return false;
    }
}

bool pins_config::getOutputClampState(libCOL_outputFunctionData_t data, libCOL_outputBasicFunction_t baseFunc, uint8_t subData, uint8_t subMask, clamp_output_type_t type, libCOL_outputSubFunction_t subFunc)
{
    switch(baseFunc) {
        case libCOL_of_genericOutput:  //0x1
        case libCOL_of_carCallAcknowledgement: //0x5
        case libCOL_of_lowPriorityCarCallAcknowledgement: //0x6
        case libCOL_of_highPriorityCarCallAcknowledgement: //0x7
        case libCOL_of_destinationCallAcknowledgement: //0x8
        case libCOL_of_lowPriorityDestinationCallAcknowledgement: //0x9
        case libCOL_of_highPriorityDestinationCallAcknowledgement: //0xA
        case libCOL_of_accessCodeUploadAcknowledgement: //0xF
        case libCOL_of_speechConnectionAcknowledgement: //0x10
        case libCOL_of_areaMonitoringConnectionAcknowledgement: //0x11
        case libCOL_of_guestCallAcknowledgement: //0x20
        case libCOL_of_liftLightsAcknowledgement: //0x3F
        case libCOL_of_vocalUserMessage: //0x48
        case libCOL_of_musicPlayback: //0x49
        case libCOL_of_miscellaneousOutputs: //0x4A
        case libCOL_of_singleFaultIndication: //0x4B
        case libCOL_of_nextStop: //0x4C
            return data.generic.status;
        case libCOL_of_hallCallAcknowledgement: //0x2
        case libCOL_of_lowPriorityHallCallAcknowledgement: //0x3
        case libCOL_of_highPriorityHallCallAcknowledgement: //0x4
        case libCOL_of_destinationFloorAcknowledgement: //0xB
        case libCOL_of_lowPriorityDestinationFloorAcknowledgement: //0xC
        case libCOL_of_highPriorityDestinationFloorAcknowledgement: //0xD
        case libCOL_of_specialFunctionAcknowledgement: //0xE
        case libCOL_of_specialIndication: //0x43
            if (data.generic.status) {
                return true;
            } else {
                return (subData != 0);
            }
        case libCOL_of_positionIndication: //0x40
            return ( (subData != 0) && (subFunc.raw == subData));
        case libCOL_of_vocalFloorsAnnouncement: //0x47
            return ((data.generic.status) && (subData != 0) && ((subData == 0xFF) || (subMask == subData)));
        case libCOL_of_positionIndicationBinary: //0x80
            return ((subData != 0)  && (subMask & subData));
        case libCOL_of_vocalFloorsAnnouncementBinary: //0x86
            return ((subData != 0)  && ((subData == 0xFF) || (subMask & subData)));
        case libCOL_of_positionIndicationGray: //0x81
            return ((subData != 0)  && (subMask & (get_gray(subData))));
        case libCOL_of_vocalFloorsAnnouncementGray: //0x87
            return ((subData != 0)  && ((subData == 0xFF) || (subMask & (get_gray(subData)))));
        case libCOL_of_positionIndication7Segment: //0x83
            return getSevenSegmentState(subData, subMask);
        case libCOL_of_directionIndication: //0x42
            return data.generic.status;
        case libCOL_of_hallLantern: //0x41
        case libCOL_of_arrivalIndication: //0x44
            if (data.generic.status) {
                return true;
            } else if (subFunc.raw == 0x03) {
                return (subData != 0);
            } else {
                return false;
            }
        case libCOL_of_callControllerCommand: //0x0
        default:
            return data.generic.status;
    }
}

bool pins_config::getOutputFunctionMatch(libCOL_outputBasicFunction_t localBaseFunc, libCOL_outputBasicFunction_t baseFunc)
{
    switch(baseFunc) {
        case libCOL_of_genericOutput:  //0x1
        case libCOL_of_hallCallAcknowledgement: //0x2
        case libCOL_of_lowPriorityHallCallAcknowledgement: //0x3
        case libCOL_of_highPriorityHallCallAcknowledgement: //0x4
        case libCOL_of_carCallAcknowledgement: //0x5
        case libCOL_of_lowPriorityCarCallAcknowledgement: //0x6
        case libCOL_of_highPriorityCarCallAcknowledgement: //0x7
        case libCOL_of_destinationCallAcknowledgement: //0x8
        case libCOL_of_lowPriorityDestinationCallAcknowledgement: //0x9
        case libCOL_of_highPriorityDestinationCallAcknowledgement: //0xA
        case libCOL_of_destinationFloorAcknowledgement: //0xB
        case libCOL_of_lowPriorityDestinationFloorAcknowledgement: //0xC
        case libCOL_of_highPriorityDestinationFloorAcknowledgement: //0xD
        case libCOL_of_specialFunctionAcknowledgement: //0xE
        case libCOL_of_accessCodeUploadAcknowledgement: //0xF
        case libCOL_of_speechConnectionAcknowledgement: //0x10
        case libCOL_of_areaMonitoringConnectionAcknowledgement: //0x11
        case libCOL_of_guestCallAcknowledgement: //0x20
        case libCOL_of_liftLightsAcknowledgement: //0x3F
        case libCOL_of_hallLantern: //0x41
        case libCOL_of_directionIndication: //0x42
        case libCOL_of_specialIndication: //0x43
        case libCOL_of_arrivalIndication: //0x44
        case libCOL_of_vocalUserMessage: //0x48
        case libCOL_of_musicPlayback: //0x49
        case libCOL_of_miscellaneousOutputs: //0x4A
        case libCOL_of_singleFaultIndication: //0x4B
        case libCOL_of_nextStop: //0x4C
        case libCOL_of_positionIndicationBinary: // 0x80
        case libCOL_of_positionIndicationGray: // 0x81
        case libCOL_of_positionIndication7Segment: // 0x83
        case libCOL_of_vocalFloorsAnnouncementBinary: // 0x86
        case libCOL_of_vocalFloorsAnnouncementGray: // 0x87
            return (localBaseFunc == baseFunc);
        case libCOL_of_positionIndication: //0x40
            return ((localBaseFunc == libCOL_of_positionIndication) || (localBaseFunc == libCOL_of_positionIndicationBinary) || (localBaseFunc == libCOL_of_positionIndicationGray) || (localBaseFunc == libCOL_of_positionIndication7Segment));
        case libCOL_of_vocalFloorsAnnouncement: //0x47
            return ((localBaseFunc == libCOL_of_vocalFloorsAnnouncement) || (localBaseFunc == libCOL_of_vocalFloorsAnnouncementBinary) || (localBaseFunc == libCOL_of_vocalFloorsAnnouncementGray));
        case libCOL_of_callControllerCommand: //0x0
        default:
            return (localBaseFunc == baseFunc);
    }

}


// int pins_config::getClampPin(int clamp, bool output)
// {
//     assert(clamp < NUMBER_OF_CLAMPS);
//     if (output) {
//         switch(clamp) {
//             case 0:
//                 return CLAMP_1_OUTPUT_PIN_NUMBER;
//             case 1:
//                 return CLAMP_2_OUTPUT_PIN_NUMBER;
//             case 2:
//                 return CLAMP_3_OUTPUT_PIN_NUMBER;
//             case 3:
//                 return CLAMP_4_OUTPUT_PIN_NUMBER;
//             case 4:
//                 return CLAMP_5_OUTPUT_PIN_NUMBER;
//             case 5:
//                 return CLAMP_6_OUTPUT_PIN_NUMBER;
//             case 6:
//                 return CLAMP_7_OUTPUT_PIN_NUMBER;
//             case 7:
//                 return CLAMP_8_OUTPUT_PIN_NUMBER;
//     #if NUMBER_OF_CLAMPS > 8
//             case 8:
//                 return CLAMP_9_OUTPUT_PIN_NUMBER;
//             case 9:
//                 return CLAMP_10_OUTPUT_PIN_NUMBER;
//             case 10:
//                 return CLAMP_11_OUTPUT_PIN_NUMBER;
//             case 11:
//                 return CLAMP_12_OUTPUT_PIN_NUMBER;
//             case 12:
//                 return CLAMP_13_OUTPUT_PIN_NUMBER;
//             case 13:
//                 return CLAMP_14_OUTPUT_PIN_NUMBER;
//             case 14:
//                 return CLAMP_15_OUTPUT_PIN_NUMBER;
//             case 15:
//                 return CLAMP_16_OUTPUT_PIN_NUMBER;
//     #endif /* NUMBER_OF_CLAMPS > 8 */
//             default:
//                 return false;
//         }
//     } else {
//         switch(clamp) {
//             case 0:
//                 return CLAMP_1_INPUT_PIN_NUMBER;
//             case 1:
//                 return CLAMP_2_INPUT_PIN_NUMBER;
//             case 2:
//                 return CLAMP_3_INPUT_PIN_NUMBER;
//             case 3:
//                 return CLAMP_4_INPUT_PIN_NUMBER;
//             case 4:
//                 return CLAMP_5_INPUT_PIN_NUMBER;
//             case 5:
//                 return CLAMP_6_INPUT_PIN_NUMBER;
//             case 6:
//                 return CLAMP_7_INPUT_PIN_NUMBER;
//             case 7:
//                 return CLAMP_8_INPUT_PIN_NUMBER;
//     #if NUMBER_OF_CLAMPS > 8
//             case 8:
//                 return CLAMP_9_INPUT_PIN_NUMBER;
//             case 9:
//                 return CLAMP_10_INPUT_PIN_NUMBER;
//             case 10:
//                 return CLAMP_11_INPUT_PIN_NUMBER;
//             case 11:
//                 return CLAMP_12_INPUT_PIN_NUMBER;
//             case 12:
//                 return CLAMP_13_INPUT_PIN_NUMBER;
//             case 13:
//                 return CLAMP_14_INPUT_PIN_NUMBER;
//             case 14:
//                 return CLAMP_15_INPUT_PIN_NUMBER;
//             case 15:
//                 return CLAMP_16_INPUT_PIN_NUMBER;
//     #endif /* NUMBER_OF_CLAMPS > 8 */
//             default:
//                 return false;
//         }
//     }
// }


// bool pins_config::getClampHighCurrent(int clamp)
// {
//     assert(clamp < NUMBER_OF_CLAMPS);
//     switch(clamp) {
//         case 0:
//             return CLAMP_1_OUTPUT_HIGH_CURRENT;
//         case 1:
//             return CLAMP_2_OUTPUT_HIGH_CURRENT;
//         case 2:
//             return CLAMP_3_OUTPUT_HIGH_CURRENT;
//         case 3:
//             return CLAMP_4_OUTPUT_HIGH_CURRENT;
//         case 4:
//             return CLAMP_5_OUTPUT_HIGH_CURRENT;
//         case 5:
//             return CLAMP_6_OUTPUT_HIGH_CURRENT;
//         case 6:
//             return CLAMP_7_OUTPUT_HIGH_CURRENT;
//         case 7:
//             return CLAMP_8_OUTPUT_HIGH_CURRENT;
// #if NUMBER_OF_CLAMPS > 8
//         case 8:
//             return CLAMP_9_OUTPUT_HIGH_CURRENT;
//         case 9:
//             return CLAMP_10_OUTPUT_HIGH_CURRENT;
//         case 10:
//             return CLAMP_11_OUTPUT_HIGH_CURRENT;
//         case 11:
//             return CLAMP_12_OUTPUT_HIGH_CURRENT;
//         case 12:
//             return CLAMP_13_OUTPUT_HIGH_CURRENT;
//         case 13:
//             return CLAMP_14_OUTPUT_HIGH_CURRENT;
//         case 14:
//             return CLAMP_15_OUTPUT_HIGH_CURRENT;
//         case 15:
//             return CLAMP_16_OUTPUT_HIGH_CURRENT;
// #endif /* NUMBER_OF_CLAMPS > 8 */
//         default:
//             return false;
//     }
// }

// int getClampPull(int clamp)
// {
//     assert(clamp < NUMBER_OF_CLAMPS);
//     switch(clamp) {
//         case 0:
//             return CLAMP_1_INPUT_PULL;
//         case 1:
//             return CLAMP_2_INPUT_PULL;
//         case 2:
//             return CLAMP_3_INPUT_PULL;
//         case 3:
//             return CLAMP_4_INPUT_PULL;
//         case 4:
//             return CLAMP_5_INPUT_PULL;
//         case 5:
//             return CLAMP_6_INPUT_PULL;
//         case 6:
//             return CLAMP_7_INPUT_PULL;
//         case 7:
//             return CLAMP_8_INPUT_PULL;
// #if NUMBER_OF_CLAMPS > 8
//         case 8:
//             return CLAMP_9_INPUT_PULL;
//         case 9:
//             return CLAMP_10_INPUT_PULL;
//         case 10:
//             return CLAMP_11_INPUT_PULL;
//         case 11:
//             return CLAMP_12_INPUT_PULL;
//         case 12:
//             return CLAMP_13_INPUT_PULL;
//         case 13:
//             return CLAMP_14_INPUT_PULL;
//         case 14:
//             return CLAMP_15_INPUT_PULL;
//         case 15:
//             return CLAMP_16_INPUT_PULL;
// #endif /* NUMBER_OF_CLAMPS > 8 */
//         default:
//             assert(false);
//             return 0;
//     }
// }

// bool getClampInverted(int clamp, bool output)
// {
//     assert(clamp < NUMBER_OF_CLAMPS);
//     if (output) {
//         switch(clamp) {
//             case 0:
//                 return CLAMP_1_OUTPUT_INVERTED;
//             case 1:
//                 return CLAMP_2_OUTPUT_INVERTED;
//             case 2:
//                 return CLAMP_3_OUTPUT_INVERTED;
//             case 3:
//                 return CLAMP_4_OUTPUT_INVERTED;
//             case 4:
//                 return CLAMP_5_OUTPUT_INVERTED;
//             case 5:
//                 return CLAMP_6_OUTPUT_INVERTED;
//             case 6:
//                 return CLAMP_7_OUTPUT_INVERTED;
//             case 7:
//                 return CLAMP_8_OUTPUT_INVERTED;
//     #if NUMBER_OF_CLAMPS > 8
//             case 8:
//                 return CLAMP_9_OUTPUT_INVERTED;
//             case 9:
//                 return CLAMP_10_OUTPUT_INVERTED;
//             case 10:
//                 return CLAMP_11_OUTPUT_INVERTED;
//             case 11:
//                 return CLAMP_12_OUTPUT_INVERTED;
//             case 12:
//                 return CLAMP_13_OUTPUT_INVERTED;
//             case 13:
//                 return CLAMP_14_OUTPUT_INVERTED;
//             case 14:
//                 return CLAMP_15_OUTPUT_INVERTED;
//             case 15:
//                 return CLAMP_16_OUTPUT_INVERTED;
//     #endif /* NUMBER_OF_CLAMPS > 8 */
//             default:
//                 return false;
//         }
//     } else {
//         switch(clamp) {
//             case 0:
//                 return CLAMP_1_INPUT_INVERTED;
//             case 1:
//                 return CLAMP_2_INPUT_INVERTED;
//             case 2:
//                 return CLAMP_3_INPUT_INVERTED;
//             case 3:
//                 return CLAMP_4_INPUT_INVERTED;
//             case 4:
//                 return CLAMP_5_INPUT_INVERTED;
//             case 5:
//                 return CLAMP_6_INPUT_INVERTED;
//             case 6:
//                 return CLAMP_7_INPUT_INVERTED;
//             case 7:
//                 return CLAMP_8_INPUT_INVERTED;
//     #if NUMBER_OF_CLAMPS > 8
//             case 8:
//                 return CLAMP_9_INPUT_INVERTED;
//             case 9:
//                 return CLAMP_10_INPUT_INVERTED;
//             case 10:
//                 return CLAMP_11_INPUT_INVERTED;
//             case 11:
//                 return CLAMP_12_INPUT_INVERTED;
//             case 12:
//                 return CLAMP_13_INPUT_INVERTED;
//             case 13:
//                 return CLAMP_14_INPUT_INVERTED;
//             case 14:
//                 return CLAMP_15_INPUT_INVERTED;
//             case 15:
//                 return CLAMP_16_INPUT_INVERTED;
//     #endif /* NUMBER_OF_CLAMPS > 8 */
//             default:
//                 return false;
//         }
//     }
// }



