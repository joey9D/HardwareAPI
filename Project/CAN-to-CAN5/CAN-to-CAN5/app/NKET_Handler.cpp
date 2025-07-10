#include "NKET_Handler.h"

NKET_Handler::NKET_Handler(HardwareInterface* hardware) 
    : hardware(hardware) 
{
    // Constructor initializes the NKET_Handler with a CANopenNode and CANopenMaster
}

bool NKET_Handler::initCAN() 
{   // Initialize the CAN2.0 Handle function with specified baudrate // default 250 and set the filters for incoming CAN messages
    int err = 0;
    if (hardware) // Check if hardware interface is available
    {
        err = hardware->initandSetFilters(proto.getIncomingCANMessageIDs()); // Initialize hardware and set CAN filters using the proto object
    }

   if (err != 0) 
    {
       setLastError(1); // Set error state if initialization fails
       setinitState(0); // Set initialization state to 0 (failed)
    }
    else 
    {
         setinitState(1); // Set initialization state to 1 (success)
    }
    return isCANInitOk(); // Check if CAN initialization is successful
}

bool NKET_Handler::isCANInitOk() 
{
    // Check if CAN initialization is successful
    if (initState == 0) 
    {
        return false; // Initialization failed
    } 
    else 
    {
        return true; // Initialization successful
    }
}

void NKET_Handler::initNKETStack() 
{
    // Initialize the NKET stack by initializing the CANopenNode
    if (!initCAN()) 
    {
        hardware->CANerrorHandler(); // Handle error if CAN initialization fails
    }
    CANInterruptCallback cb;
    cb.set<NKET_Handler, &NKET_Handler::handleIncomingCANMessage>(*this);
    // Register the callback for handling incoming CAN messages
    hardware->RegisterCANInterruptCallback(cb); // Map the callback function with the hardware interface
}

void NKET_Handler::handleIncomingCANMessage(const uint8_t* data, uint32_t canId) 
{
    // Handle the incoming CAN message based on the canId
    switch (static_cast<CANMsgID>(canId)) 
    {
        case CANMsgID::ElevatorStatusMastertoLOP0: // ElevatorStatusMastertoLOP0
            {    ElevatorStatusMastertoLOP0 statusData0 = proto.parseElevatorStatuslandData0(data);
                
                // Process ElevatorStatusMastertoLOP0
                break;
            }

        case CANMsgID::ElevatorStatusMastertoLOP1: // ElevatorStatusMastertoLOP1
            {    ElevatorStatusMastertoLOP1 statusData1 = proto.parseElevatorStatuslandData1(data);
                // Process ElevatorStatusMastertoLOP1
                break;
            }
        case CANMsgID::ElevatorStatusMastertoLOP2: // ElevatorStatusMastertoLOP2
            {    ElevatorStatusMastertoLOP2 statusData2 = proto.parseElevatorStatuslandData2(data);
                // Process ElevatorStatusMastertoLOP2
                break;
            }
        case CANMsgID::ElevatorStatusMastertoLOP3: // ElevatorStatusMastertoLOP3
            {    ElevatorStatusMastertoLOP3 statusData3 = proto.parseElevatorStatuslandData3(data);
                // Process ElevatorStatusMastertoLOP3
                break;
            }
        case CANMsgID::MastertoLOPHallupCallDisp_FS: // HallUpCallDisplayFrontSide
            {   FloorBitfield hallUpCallFront = proto.parseFloorBitfield(data);
                // Process HallUpCallDisplayFrontSide
                break;
            }
        case CANMsgID::MastertoLOPHalldownCallDisp_FS: // HallDownCallDisplayFrontSide
            {    FloorBitfield hallDownCallFront = proto.parseFloorBitfield(data);
                // Process HallDownCallDisplayFrontSide
                break;
            }
        case CANMsgID::MastertoLOPHallupCallDisp_RS: // HallUpCallDisplayRearSide
            {    FloorBitfield hallUpCallRear = proto.parseFloorBitfield(data);
                // Process HallUpCallDisplayRearSide
                break;
            }
        case CANMsgID::MastertoLOPHalldownCallDisp_RS: // HallDownCallDisplayRearSide
            {    FloorBitfield hallDownCallRear = proto.parseFloorBitfield(data);
                // Process HallDownCallDisplayRearSide
                break;
            }
        case CANMsgID::ElevatorStatusMastertoCOP0: // ElevatorStatusCar0
            {    ElevatorStatusMastertoCOP0 statusCarData0 = proto.parseElevatorStatusCarData0(data);
                // Process ElevatorStatusCar0
                break;
            }
        case CANMsgID::ElevatorStatusMastertoCOP1: // ElevatorStatusCar1
            {   ElevatorStatusMastertoCOP1 statusCarData1 = proto.parseElevatorStatusCarData1(data);
                // Process ElevatorStatusCar1
                break;
            }
        case CANMsgID::ElevatorStatusMastertoCOP2: // ElevatorStatusCar2
            {   ElevatorStatusMastertoCOP2 statusCarData2 = proto.parseElevatorStatusCarData2(data);
                // Process ElevatorStatusCar2
                break;
            }
        case CANMsgID::MastertoCOPFrontDoorButtonLights: // FrontDoorButtonLight
            {    FloorBitfield frontDoorButtonLight = proto.parseFloorBitfield(data);
                // Process FrontDoorButtonLight
                break;
            }
        case CANMsgID::MastertoCOPRearDoorButtonLights: // RearDoorButtonLight
            {    FloorBitfield rearDoorButtonLight = proto.parseFloorBitfield(data);
                // Process RearDoorButtonLight
                break;
            }
        default:
            // Handle unknown message ID
            break;
    }
}

void NKET_Handler::handleIncomingCiA417Message(const virtualIOMapping_data_t& msg)// Handle incoming CiA417 messages
{


    // Process the CiA417 message
    // This function would typically extract relevant information from the msg parameter
    // and take appropriate action based on the message contents
    uint64_t* stateTable = nullptr;
    bool isFloorBased = false;

    switch (msg.basicFunction) 
    {
        case libCOL_if_hallStandard ||libCOL_if_hallLowPriority || libCOL_if_hallHighPriority:
            isFloorBased = true;
            break;
        case libCOL_if_carCallStandard || libCOL_if_carCallLowPriority || libCOL_if_carCallHighPriority:
            //stateTable = &lastHallDownCalls;
            isFloorBased = true;
            break;
        case libCOL_if_specialFunction:
        {
            bool isFs = isSubFunctionInTable(msg.subFunction, mapCOPtoMasterCallspecialfunction_FS1, sizeof(mapCOPtoMasterCallspecialfunction_FS1) / sizeof(BitfieldMapping));  
            if (isFs)
                isFloorBased = true;
            break;

        }
        // ... other floor-based cases ...
        case libCOL_specialFunction: // Example for special function
            mapSpecialFunctionCOPtoMasterFS(msg);
            return;
        case libCOL_specialFunctionRear:
            mapSpecialFunctionCOPtoMasterRS(msg);
            return;
        // ... other non-floor-based cases ...
        default:
            return;
    }

    // Only process floor-based calls/cancels
    if (isFloorBased && stateTable) 
    {
        uint8_t floor = msg.floor;
        if (floor < 1 || floor > 64) return;

        uint64_t mask = (1ULL << (floor - 1));
        bool wasSet = (*stateTable & mask) != 0;
        bool isSet = msg.functionData != 0;

        if (isSet && !wasSet) {
            // New call
            mapCOPtoMasterFloorCall(msg);
        } else if (!isSet && wasSet) {
            // Cancellation
            mapCOPtoMasterFloorCallCancel(msg);
        }
        // Update state
        if (isSet)
            *stateTable |= mask;
        else
            *stateTable &= ~mask;
    }


}


void NKET_Handler::sendCANMessage(const uint8_t* data, uint32_t canId) 
{

    
    // Send the CAN message with the given data and canId
    // This function would typically interface with the CAN hardware to transmit the message
    // For example:
    // HAL_CAN_AddTxMessage(&hcan, &txHeader, data, &txMailbox);
}



// Implementation must match the declaration in the header file.
// Please ensure the parameter type and name match exactly as in the header.
// For example, if the header declares: void ElevatorStatusMastertoLOP0(const ElevatorStatusMastertoLOP0& statusCarData0);
void NKET_Handler::mapMastertoLOP0(const ElevatorStatusMastertoLOP0& msg)
{

     // TODO : How would this be turned off when the signal comes again does
        //the function data go to zero or it has to be sent by the master?
    // if (msg.ElevatorDataMastertoLOP0 & static_cast<uint8_t>(ElevatorDataMastertoLOP0::FireService)) 
    // {
    //     virtualIOMapping_data_t ioMap{};
    //     ioMap.basicFunction = libCOL_of_specialIndication;
    //     ioMap.subFunction = libCOL_of_specialIndication_FireService;
    //     ioMap.floor =msg.Floor;
    //     ioMap.door = 0; // Assuming door is not used in this context , default what to do here ?
    //     ioMap.functionData = 1;
    //     // Send this message as TPDO
        
    // }
  
    // if (msg.ElevatorDataMastertoLOP0 & static_cast<uint8_t>(ElevatorDataMastertoLOP0::LiftLock))
    // {
    //     virtualIOMapping_data_t ioMap{};
    //     ioMap.basicFunction = libCOL_of_specialIndication;
    //     ioMap.subFunction = libCOL_special_keyLock1_ack;
    //     ioMap.floor = msg.Floor;
    //     ioMap.door = 0; // Assuming door is not used in this context , default what to do here ?
    //     ioMap.functionData = 1;
    //     // Send this message as TPDO 
       
    // }

    // if (msg.ElevatorDataMastertoLOP0 & static_cast<uint8_t>(ElevatorDataMastertoLOP0::Fault))
    // {
    //     virtualIOMapping_data_t ioMap{};
    //     ioMap.basicFunction = libCOL_of_specialIndication;
    //     ioMap.subFunction = libCOL_specialIndication_outOfOrder;
    //     ioMap.floor = msg.Floor;
    //     ioMap.door = 0; // Assuming door is not used in this context , default what to do here ?
    //     ioMap.functionData = 1;
    //     // Send this message as TPDO
    // }

    // if (msg.ElevatorDataMastertoLOP0 & static_cast<uint8_t>(ElevatorDataMastertoLOP0::Inspection))
    // {
    //     virtualIOMapping_data_t ioMap{};
    //     ioMap.basicFunction = libCOL_of_specialIndication;
    //     ioMap.subFunction = libCOL_specialIndication_liftInMaintenance;
    //     ioMap.floor = msg.Floor;
    //     ioMap.door = 0; // Assuming door is not used in this context , default what to do here ?
    //     ioMap.functionData = 1;
    //     // Send this message as TPDO
    // }

    // if (msg.ElevatorDataMastertoLOP0 & static_cast<uint8_t>(ElevatorDataMastertoLOP0::Running) 
    //     && msg.ElevatorDataMastertoLOP0 & static_cast<uint8_t>(ElevatorDataMastertoLOP0::RunningUp)) 
    // {
    //     virtualIOMapping_data_t ioMap{};
    //     ioMap.basicFunction = libCOL_of_directionIndication;
    //     ioMap.subFunction = libCOL_directionIndication_MovingUp;
    //     ioMap.floor = msg.Floor;
    //     ioMap.door = 0; // Assuming door is not used in this context , default what to do here ?
    //     ioMap.functionData = 1;
    //     // Send this message as TPDO
    // }
    // if (msg.ElevatorDataMastertoLOP0 & static_cast<uint8_t>(ElevatorDataMastertoLOP0::Running) 
    //     && msg.ElevatorDataMastertoLOP0 & static_cast<uint8_t>(ElevatorDataMastertoLOP0::RunningDown)) 
    // {
    //     virtualIOMapping_data_t ioMap{};
    //     ioMap.basicFunction = libCOL_of_directionIndication;
    //     ioMap.subFunction = libCOL_directionIndication_MovingDown;
    //     ioMap.floor = msg.Floor;
    //     ioMap.door = 0; // Assuming door is not used in this context , default what to do here ?
    //     ioMap.functionData = 1;
    //     // Send this message as TPDO
    // }
    // if (msg.ElevatorDataMastertoLOP0 & static_cast<uint8_t>(ElevatorDataMastertoLOP0::Running) 
    //     && msg.ElevatorDataMastertoLOP0 & static_cast<uint8_t>(ElevatorDataMastertoLOP0::RunningUp)) 
    // {
    //     virtualIOMapping_data_t ioMap{};
    //     ioMap.basicFunction = libCOL_of_directionIndication;
    //     ioMap.subFunction = libCOL_directionIndication_MovingUp;
    //     ioMap.floor = msg.Floor;
    //     ioMap.door = 0; // Assuming door is not used in this context , default what to do here ?
    //     ioMap.functionData = 1;
    //     // Send this message as TPDO
    // }
    // if (msg.ElevatorDataMastertoLOP0 & static_cast<uint8_t>(ElevatorDataMastertoLOP0::RunningDown)) 
    // {
    //     virtualIOMapping_data_t ioMap{};
    //     ioMap.basicFunction = libCOL_of_directionIndication;
    //     ioMap.subFunction = libCOL_directionIndication_Down;
    //     ioMap.floor = msg.Floor;
    //     ioMap.door = 0; // Assuming door is not used in this context , default what to do here ?
    //     ioMap.functionData = 1;
    //     // Send this message as TPDO
    // }
    // if (msg.ElevatorDataMastertoLOP0 & static_cast<uint8_t>(ElevatorDataMastertoLOP0::RunningUp)) 
    // {
    //     virtualIOMapping_data_t ioMap{};
    //     ioMap.basicFunction = libCOL_of_directionIndication;
    //     ioMap.subFunction = libCOL_directionIndication_Up;
    //     ioMap.floor = msg.Floor;
    //     ioMap.door = 0; // Assuming door is not used in this context , default what to do here ?
    //     ioMap.functionData = 1;
    //     // Send this message as TPDO
    // }
    for (const BitfieldMapping& mapping : bitmapMastertoLOP0) 
    {
        if (msg.ElevatorDataMastertoLOP0 & mapping.bitmask) 
        {
            virtualIOMapping_data_t ioMap{};
            ioMap.basicFunction = mapping.basicFunction;
            ioMap.subFunction = mapping.subFunction;
            ioMap.floor = msg.currentFloor;
            ioMap.door = 0; // Assuming door is not used in this context, default what to do here?
            ioMap.functionData = 1;
            // Send this message as TPDO
        }
    }



    // Special case of Moving Arrow handled here 
    
    if (msg.ElevatorDataMastertoLOP0 & static_cast<uint8_t>(ElevatorDataMastertoLOP0::Running) 
        && msg.ElevatorDataMastertoLOP0 & static_cast<uint8_t>(ElevatorDataMastertoLOP0::RunningUp)) 
    {
        virtualIOMapping_data_t ioMap{};
        ioMap.basicFunction = libCOL_of_directionIndication;
        ioMap.subFunction = libCOL_directionIndication_MovingUp;
        ioMap.floor = msg.currentFloor;
        ioMap.door = 0; // Assuming door is not used in this context , default what to do here ?
        ioMap.functionData = 1;
        // Send this message as TPDO
    }
    if (msg.ElevatorDataMastertoLOP0 & static_cast<uint8_t>(ElevatorDataMastertoLOP0::Running) 
        && msg.ElevatorDataMastertoLOP0 & static_cast<uint8_t>(ElevatorDataMastertoLOP0::RunningDown)) 
    {
        virtualIOMapping_data_t ioMap{};
        ioMap.basicFunction = libCOL_of_directionIndication;
        ioMap.subFunction = libCOL_directionIndication_MovingDown;
        ioMap.floor = msg.currentFloor;
        ioMap.door = 0; // Assuming door is not used in this context , default what to do here ?
        ioMap.functionData = 1;
        // Send this message as TPDO
    }

    // Handling Attendant Data
    for (const BitfieldMapping& mapping : attendantDataMapMastertoLOP0) 
    {
        if (msg.AttendantDataMastertoLOP0 & mapping.bitmask) 
        {
            virtualIOMapping_data_t ioMap{};
            ioMap.basicFunction = mapping.basicFunction;
            ioMap.subFunction = mapping.subFunction;
            ioMap.floor = msg.currentFloor;
            ioMap.door = 0; // Assuming door is not used in this context, default what to do here?
            ioMap.functionData = 1;
            // Send this message as TPDO
        }
    }

    // Handling Load Data
    for (const BitfieldMapping& mapping : loadDataMapMastertoLOP0) 
    {
        if (msg.LoadDataMastertoLOP0 & mapping.bitmask) 
        {
            virtualIOMapping_data_t ioMap{};
            ioMap.basicFunction = mapping.basicFunction;
            ioMap.subFunction = mapping.subFunction;
            ioMap.floor = msg.currentFloor;
            ioMap.door = 0; // Assuming door is not used in this context, default what to do here?
            ioMap.functionData = 1;
            // Send this message as TPDO
        }
    }
    

  
}

void NKET_Handler::mapMastertoLOP1(const ElevatorStatusMastertoLOP1& msg) 
{
    // TODO : How would this be turned off when the signal comes again does
    //the function data go to zero or it has to be sent by the master?
    for (const BitfieldMapping& mapping : mapSpecialAccessMastertoLOP1) 
    {
        if (msg.ElevatorSpecialAccessMastertoLOP1 & mapping.bitmask) 
        {
            virtualIOMapping_data_t ioMap{};
            ioMap.basicFunction = mapping.basicFunction;
            ioMap.subFunction = mapping.subFunction;
            //ioMap.floor = msg.currentFloor; // How to handle currentFloor here? 
            ioMap.floor = 0; // Assuming currentFloor is not used in this context, default what to do here?
            ioMap.door = 0; // Assuming door is not used in this context, default what to do here?
            ioMap.functionData = 1;
            // Send this message as TPDO
        }
    }

    for (const BitfieldMapping& mapping : mapSpecialIndicationMastertoLOP1) 
    {
        if (msg.ElevatorSpecialIndicationMastertoLOP1 & mapping.bitmask) 
        {
            virtualIOMapping_data_t ioMap{};
            ioMap.basicFunction = mapping.basicFunction;
            ioMap.subFunction = mapping.subFunction;
            //ioMap.floor = msg.currentFloor; // How to handle currentFloor here? 
            ioMap.floor = 0; // Assuming currentFloor is not used in this context, default what to do here?
            ioMap.door = 0; // Assuming door is not used in this context, default what to do here?
            ioMap.functionData = 1;
            // Send this message as TPDO
        }
    }

    for  (const BitfieldMapping& mapping : mapElevatorStateMastertoLOP1) 
    {
        if (msg.ElevatorStateMastertoLOP1 & mapping.bitmask) 
        {
            virtualIOMapping_data_t ioMap{};
            ioMap.basicFunction = mapping.basicFunction;
            ioMap.subFunction = mapping.subFunction;
            //ioMap.floor = msg.currentFloor; // How to handle currentFloor here? 
            ioMap.floor = 0; // Assuming currentFloor is not used in this context, default what to do here?
            ioMap.door = 0; // Assuming door is not used in this context, default what to do here?
            ioMap.functionData = 1;
            // Send this message as TPDO
        }
    }
}

void NKET_Handler::mapMastertoLOP2(const ElevatorStatusMastertoLOP2& msg) 
{
    // TODO : How would this be turned off when the signal comes again does
    //the function data go to zero or it has to be sent by the master?
    // for (const BitfieldMapping& mapping : mapSpecialIndicationMastertoLOP2) 
    // {
    //     if (msg.ElevatorSpecialIndicationMastertoLOP2 & mapping.bitmask) 
    //     {
    //         virtualIOMapping_data_t ioMap{};
    //         ioMap.basicFunction = mapping.basicFunction;
    //         ioMap.subFunction = mapping.subFunction;
    //         //ioMap.floor = msg.currentFloor; // How to handle currentFloor here? 
    //         ioMap.floor = 0; // Assuming currentFloor is not used in this context, default what to do here?
    //         ioMap.door = 0; // Assuming door is not used in this context, default what to do here?
    //         ioMap.functionData = 1;
    //         // Send this message as TPDO
    //     }
    // }
}

void NKET_Handler::mapMastertoLOP3(const ElevatorStatusMastertoLOP3& msg) 
{
    // TODO : How would this be turned off when the signal comes again does
    //the function data go to zero or it has to be sent by the master?
    for (const BitfieldMapping& mapping : mapElevatorDataMastertoLOP3) 
    {
        if (msg.ElevatorStateMastertoLOP3 & mapping.bitmask) 
        {
            virtualIOMapping_data_t ioMap{};
            ioMap.basicFunction = mapping.basicFunction;
            ioMap.subFunction = mapping.subFunction;
            //ioMap.floor = msg.currentFloor; // How to handle currentFloor here? 
            ioMap.floor = 0; // Assuming currentFloor is not used in this context, default what to do here?
            ioMap.door = 0; // Assuming door is not used in this context, default what to do here?
            ioMap.functionData = 1;
            // Send this message as TPDO
        }
    }
}

void NKET_Handler::mapMastertoCOP0(const ElevatorStatusMastertoCOP0& msg) 
{
    // TODO : How would this be turned off when the signal comes again does
    //the function data go to zero or it has to be sent by the master?
    for (const BitfieldMapping& mapping : mapStatusDataMastertoCOP0) 
    {
        if (msg.ElevatorStatusDataMastertoCOP0 & mapping.bitmask) 
        {
            virtualIOMapping_data_t ioMap{};
            ioMap.basicFunction = mapping.basicFunction;
            ioMap.subFunction = mapping.subFunction;
            //ioMap.floor = msg.currentFloor; // How to handle currentFloor here? 
            ioMap.floor = 0; // Assuming currentFloor is not used in this context, default what to do here?
            ioMap.door = 0; // Assuming door is not used in this context, default what to do here?
            ioMap.functionData = 1;
            // Send this message as TPDO
        }
    }

    for (const BitfieldMapping& mapping : mapAttendantFlagsMastertoCOP0) 
    {
        if (msg.AttendantFlagsMastertoCOP0 & mapping.bitmask) 
        {
            virtualIOMapping_data_t ioMap{};
            ioMap.basicFunction = mapping.basicFunction;
            ioMap.subFunction = mapping.subFunction;
            //ioMap.floor = msg.currentFloor; // How to handle currentFloor here? 
            ioMap.floor = 0; // Assuming currentFloor is not used in this context, default what to do here?
            ioMap.door = 0; // Assuming door is not used in this context, default what to do here?
            ioMap.functionData = 1;
            // Send this message as TPDO
        }
    }

    for (const BitfieldMapping& mapping : mapLoadDataMastertoCOP0) 
    {
        if (msg.LoadCarFlagsMastertoCOP0 & mapping.bitmask) 
        {
            virtualIOMapping_data_t ioMap{};
            ioMap.basicFunction = mapping.basicFunction;
            ioMap.subFunction = mapping.subFunction;
            //ioMap.floor = msg.currentFloor; // How to handle currentFloor here? 
            ioMap.floor = 0; // Assuming currentFloor is not used in this context, default what to do here?
            ioMap.door = 0; // Assuming door is not used in this context, default what to do here?
            ioMap.functionData = 1;
            // Send this message as TPDO
        }
    }
    
}

void NKET_Handler::mapMastertoCOP1(const ElevatorStatusMastertoCOP1& msg) 
{
    // TODO : How would this be turned off when the signal comes again does
    //the function data go to zero or it has to be sent by the master?
    for (const BitfieldMapping& mapping : mapSpecialIndicationMastertoCOP1) 
    {
        if (msg.ElevatorDataMastertoCOP1 & mapping.bitmask) 
        {
            virtualIOMapping_data_t ioMap{};
            ioMap.basicFunction = mapping.basicFunction;
            ioMap.subFunction = mapping.subFunction;
            //ioMap.floor = msg.currentFloor; // How to handle currentFloor here? 
            ioMap.floor = 0; // Assuming currentFloor is not used in this context, default what to do here?
            ioMap.door = 0; // Assuming door is not used in this context, default what to do here?
            ioMap.functionData = 1;
            // Send this message as TPDO
        }
    }
    for (const BitfieldMapping& mapping : mapSoundFlagsMastertoCOP1) 
    {
        if (msg.SoundFlagsMastertoCOP1 & mapping.bitmask) 
        {
            virtualIOMapping_data_t ioMap{};
            ioMap.basicFunction = mapping.basicFunction;
            ioMap.subFunction = mapping.subFunction;
            //ioMap.floor = msg.currentFloor; // How to handle currentFloor here? 
            ioMap.floor = 0; // Assuming currentFloor is not used in this context, default what to do here?
            ioMap.door = 0; // Assuming door is not used in this context, default what to do here?
            ioMap.functionData = 1;
            // Send this message as TPDO
        }
    }

    for (const BitfieldMapping& mapping : mapLightsFlagsMastertoCOP1) 
    {
        if (msg.ElevatorDataMastertoCOP1 & mapping.bitmask) 
        {
            virtualIOMapping_data_t ioMap{};
            ioMap.basicFunction = mapping.basicFunction;
            ioMap.subFunction = mapping.subFunction;
            //ioMap.floor = msg.currentFloor; // How to handle currentFloor here? 
            ioMap.floor = 0; // Assuming currentFloor is not used in this context, default what to do here?
            ioMap.door = 0; // Assuming door is not used in this context, default what to do here?
            ioMap.functionData = 1;
            // Send this message as TPDO
        }
    }

}
void NKET_Handler::mapMastertoCOP2(const ElevatorStatusMastertoCOP2& msg)
{
    for (const BitfieldMapping& mapping : mapElevatorStatusMastertoCOP2) 
    {
        if (msg.ElevatorDataMastertoCOP2 & mapping.bitmask) 
        {
            virtualIOMapping_data_t ioMap{};
            ioMap.basicFunction = mapping.basicFunction;
            ioMap.subFunction = mapping.subFunction;
            //ioMap.floor = msg.currentFloor; // How to handle currentFloor here? 
            ioMap.floor = 0; // Assuming currentFloor is not used in this context, default what to do here?
            ioMap.door = 0; // Assuming door is not used in this context, default what to do here?
            ioMap.functionData = 1;
            // Send this message as TPDO
        }
    }
}

void NKET_Handler::mapMastertoCOPButtonLights_FS(const FloorBitfield& msg) 
{
    // Convert incoming FloorBitfield to a format for CAN2.0 Send
    uint8_t canData[8] = {0};

    // Set the bit for the selected floor
    if (msg.floor >= 1 && msg.floor <= 64) 
    {
        uint8_t byteIndex = (msg.floor - 1) / 8;      // 0 for floors 1-8, 1 for 9-16, etc.
        uint8_t bitIndex  = (msg.floor - 1) % 8;      // 0 for floor 1, 1 for floor 2, etc.
        if (msg.functionData) 
        {
            canData[byteIndex] |= (1 << bitIndex);    // Set the bit for this floor
        } 
        else 
        {
            canData[byteIndex] &= ~(1 << bitIndex);   // Clear the bit for this floor (if needed)
        }
    }

    sendCANMessage(canData, static_cast<uint32_t>(CANMsgID::MastertoCOPFrontDoorButtonLights));
}




void NKET_Handler::mapSpecialFunctionCOPtoMasterFS(const virtualIOMapping_data_t& msg) 
{

    // Convert incoming virtualIOMapping to a format for CAN2.0 Send 
    uint8_t canData[8] = {0};

    // FS1 (byte 0)
    for (const BitfieldMapping& mapping : mapCOPtoMasterCallspecialfunction_FS1) 
    {
        if (msg.basicFunction == mapping.basicFunction &&
            msg.subFunction == mapping.subFunction) 
        {
            if (msg.functionData)
                canData[mapping.byteIndex] |= mapping.bitmask;
            else
                canData[mapping.byteIndex] &= ~mapping.bitmask;
        }
    }

    // FS2 (byte 1)
    for (const BitfieldMapping& mapping : mapSpecialFunctionCOPtoMasterFS2) 
    {
        if (msg.basicFunction == mapping.basicFunction &&
            msg.subFunction == mapping.subFunction) 
        {
            if (msg.functionData)
                canData[mapping.byteIndex] |= mapping.bitmask;
            else
                canData[mapping.byteIndex] &= ~mapping.bitmask;
        }
    }

    sendCANMessage(canData, static_cast<uint32_t>(CANMsgID::COPtoMasterCallspecialfunction_FS));
}
void NKET_Handler::mapSpecialFunctionCOPtoMasterRS(const virtualIOMapping_data_t& msg) 
{
    // Convert incoming virtualIOMapping to a format for CAN2.0 Send
    uint8_t canData[8] = {0};

    // RS1 (byte 0)
    for (const BitfieldMapping& mapping : mapCOPtoMasterCallspecialfunction_RS1) 
    {
        if (msg.basicFunction == mapping.basicFunction &&
            msg.subFunction == mapping.subFunction) 
        {
            if (msg.functionData)
                canData[mapping.byteIndex] |= mapping.bitmask;
            else
                canData[mapping.byteIndex] &= ~mapping.bitmask;
        }
    }

    // RS2 (byte 1)
    for (const BitfieldMapping& mapping : mapSpecialFunctionCOPtoMasterRS2) 
    {
        if (msg.basicFunction == mapping.basicFunction &&
            msg.subFunction == mapping.subFunction) 
        {
            if (msg.functionData)
                canData[mapping.byteIndex] |= mapping.bitmask;
            else
                canData[mapping.byteIndex] &= ~mapping.bitmask;
        }
    }

    sendCANMessage(canData, static_cast<uint32_t>(CANMsgID::COPtoMasterCallspecialfunction_RS));


    // //the function data go to zero or it has to be sent by the master?
    // for (const BitfieldMapping& mapping : mapRearDoorButtonLights) 
    // {
    //     if (msg & mapping.bitmask) 
    //     {
    //         virtualIOMapping_data_t ioMap{};
    //         ioMap.basicFunction = mapping.basicFunction;
    //         ioMap.subFunction = mapping.subFunction;
    //         //ioMap.floor = msg.currentFloor; // How to handle currentFloor here? 
    //         ioMap.floor = 0; // Assuming currentFloor is not used in this context, default what to do here?
    //         ioMap.door = 0; // Assuming door is not used in this context, default what to do here?
    //         ioMap.functionData = 1;
    //         // Send this message as TPDO
    //     }
    // }
}


void NKET_Handler::mapCOPtoMasterFloorCall(const virtualIOMapping_data_t& msg) 
{
    // Convert incoming FloorBitfield to a format for CAN2.0 Send
    FloorBitfield bitfield{};

    // Set the bit for the selected floor
    if (msg.floor >= 1 && msg.floor <= 64) 
    {
        if (msg.functionData)
        {
            bitfield.setFloor(msg.floor); // Set the bit for this floor
        }
        else
        {
            bitfield.clearFloor(msg.floor); // Clear the bit for this floor
        }
    }
    if (msg.door == 0) 
    {
       sendCANMessage(bitfield.data, static_cast<uint32_t>(CANMsgID::COPtoMasterCallregistration_FS));
        // Handle the case where the door is closed
    }
    else  
    {
       sendCANMessage(bitfield.data, static_cast<uint32_t>(CANMsgID::COPtoMasterCallregistration_RS));
        // Handle the case where the door is open
    }
    
    // Send the CAN message to the master

}


void NKET_Handler::mapCOPtoMasterFloorCallCancel(const virtualIOMapping_data_t& msg) 
{
    // Convert incoming FloorBitfield to a format for CAN2.0 Send
    FloorBitfield bitfield{};

    // Set the bit for the selected floor
    if (msg.floor >= 1 && msg.floor <= 64) 
    {
       bitfield.clearFloor(msg.floor); // Clear the bit for this floor
    }

    if (msg.door == 0) 
    {
       sendCANMessage(bitfield.data, static_cast<uint32_t>(CANMsgID::COPtoMasterCallderegistration_FS));
        // Handle the case where the door is closed
    }
    else  
    {
       sendCANMessage(bitfield.data, static_cast<uint32_t>(CANMsgID::COPtoMasterCallderegistration_RS));
        // Handle the case where the door is open
    }
    
}


bool isSubFunctionInTable(uint8_t subFunction, const BitfieldMapping* table, size_t tableSize) {
    for (size_t i = 0; i < tableSize; ++i) {
        if (table[i].subFunction == subFunction) {
            return true;
        }
    }
    return false;
}


