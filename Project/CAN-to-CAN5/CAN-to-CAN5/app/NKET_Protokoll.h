#ifndef NKET_PROTOKOLL_H
#define NKET_PROTOKOLL_H


#include <cstdint>
#include <array>
// #include "CANopenNode.h"

/* 

Created by : K. Singh 23.06.2025

This file contains all protocol definitions and function declarations for the NKET project. 
All the magic numbers in the form of bits are stored here as enums and then connected to the corresponding functions and variables. 

*/

// CAN message IDs as named enums
enum class CANMsgID : uint32_t 
{
    /*********************************************************************
     * NKET CAN Protocol Message IDs */
    // Here Master is used for the Controller or Steuerung of the Lift.
    // Master to LOP call 
    ElevatorStatusMastertoLOP0                      = 0x0001FF00,
    ElevatorStatusMastertoLOP1                      = 0x0001FF01,
    ElevatorStatusMastertoLOP2                      = 0x0001FF0B,
    ElevatorStatusMastertoLOP3                      = 0x00010312,
    MastertoLOPHallupCallDisp_FS                    = 0x00010303,     // Master to LOP Hall Call up Display on Front Side. // Handled by Door Selection and A or B ? then execBf_hallCallAcknowledgement //libCOL_hall_up_ack
    MastertoLOPHalldownCallDisp_FS                  = 0x00010304,     // Master to LOP Hall Call down Display on Front Side. // Handled by Door Selection and A or B ? then execBf_hallCallAcknowledgement //libCOL_hall_down_ack
    MastertoLOPHallupCallDisp_RS                    = 0x00010305,     // Master to LOP Hall Call up Display on the Back / Rear Side. // // Handled by Door Selection and A or B ? then execBf_hallCallAcknowledgement //libCOL_hall_up_ack
    MastertoLOPHalldownCallDisp_RS                  = 0x00010306,     // Master to LOP Hall Call down Display on the Back/ Rear Side. // // // Handled by Door Selection and A or B ? then execBf_hallCallAcknowledgement //libCOL_hall_down_ack

    // LOP to Master
    LOPtoMasterHallupCall                           = 0x00030120,
    LOPtoMasterHalldownCall                         = 0x00030121,
    LOPtoMasterLiftLockActivate                     = 0x00030124,
    LOPtoMasterLiftLockDeactivate                   = 0x00030125,
    LOPtoMasterFireOn                               = 0x00030126,
    LOPtoMasterFireOff                              = 0x00030127,

    // Master to COP Call
    ElevatorStatusMastertoCOP0                      = 0x0001FFF0,    // 
    ElevatorStatusMastertoCOP1                      = 0x0001FFF1,
    ElevatorStatusMastertoCOP2                      = 0x0001FFFA,
    MastertoCOPFrontDoorButtonLights                = 0x00010402,    // Floor button lights are illuminated based upon request of master on the Front Door.
    MastertoCOPRearDoorButtonLights                 = 0x00010502,    // Floor button lights are illuminated based upon request of master on the back/rear Door.

    // COP Call to Master
    COPtoMasterCallspecialfunction_FS               = 0x00040101,
    COPtoMasterCallspecialfunction_RS               = 0x00050101,  
    COPtoMasterCallregistration_FS                  = 0x00040102,  // Floor Selection on Front Side.
    COPtoMasterCallregistration_RS                  = 0x00050102,  // Floor Selection on the back/ rear Side.
    COPtoMasterCallderegistration_FS                = 0x00040103,  // Floor deregistration Front Side , Double click to deregister
    COPtoMasterCallderegistration_RS                = 0x00050103,  // Floor deregistration Back / Rear Side ,Double click to deregister
    
    
    // ... add all others here as needed
};
constexpr std::array<CANMsgID, 13> IncomingCANMessages = 
{
    CANMsgID::ElevatorStatusMastertoLOP0,
    CANMsgID::ElevatorStatusMastertoLOP1,
    CANMsgID::ElevatorStatusMastertoLOP2,
    CANMsgID::ElevatorStatusMastertoLOP3,
    CANMsgID::MastertoLOPHallupCallDisp_FS,
    CANMsgID::MastertoLOPHalldownCallDisp_FS,
    CANMsgID::MastertoLOPHallupCallDisp_RS,
    CANMsgID::MastertoLOPHalldownCallDisp_RS,
    CANMsgID::ElevatorStatusMastertoCOP0,
    CANMsgID::ElevatorStatusMastertoCOP1,
    CANMsgID::ElevatorStatusMastertoCOP2,
    CANMsgID::MastertoCOPFrontDoorButtonLights,
    CANMsgID::MastertoCOPRearDoorButtonLights
};




constexpr std::array<CANMsgID, 12> OutgoingCANMessages = 
{
    CANMsgID::LOPtoMasterHallupCall,
    CANMsgID::LOPtoMasterHalldownCall,
    CANMsgID::LOPtoMasterLiftLockActivate,
    CANMsgID::LOPtoMasterLiftLockDeactivate,
    CANMsgID::LOPtoMasterFireOn,
    CANMsgID::LOPtoMasterFireOff,
    CANMsgID::COPtoMasterCallspecialfunction_FS,
    CANMsgID::COPtoMasterCallspecialfunction_RS,
    CANMsgID::COPtoMasterCallregistration_FS,
    CANMsgID::COPtoMasterCallregistration_RS,
    CANMsgID::COPtoMasterCallderegistration_FS,
    CANMsgID::COPtoMasterCallderegistration_RS
};

/*******************ElevatorStatusMastertoLOP0 Data Field ********************************************************/


// Enums for status flags in Byte 2
enum class ElevatorDataMastertoLOP0 : uint8_t 
{
    FireService   = 1 << 7,     // Handled by execBf_specialIndication and libCOL_specialIndication_fireService
    LiftLock      = 1 << 6,      // Handled by execBf_specialFunctionAcknowledgement and libCOL_special_keyLock1_ack , 2,3,4. ???
    Fault         = 1 << 5,      // Handled by execBf_specialIndication and libCOL_specialIndication_outOfOrder
    Inspection    = 1 << 3,      // Handled by execBf_specialIndication and libCOL_specialIndication_liftInMaintenance
    Running       = 1 << 2,      // Handled by execBf_directionIndication
    RunningDown   = 1 << 1,      // Handled by execBf_directionIndication
    RunningUp     = 1 << 0       // Handled by execBf_directionIndication
};

// Enums for attendant status in Byte 5
enum class AttendantDataMastertoLOP0 : uint8_t 
{
    AttendantBypass  = 1 << 1,      // Notfound maybe ? libCOL_special_liftAttendantDriveThroughButton_ack.
    AttendantService = 1 << 0       // libCOL_specialIndication_liftAttendantService.
};

// Enums for load status in Byte 6
enum class LoadDataMastertoLOP0 : uint8_t 
{
    Overload     = 1 << 3,   // Handled by execBf_specialIndication and libCOL_specialIndication_overLoad.
    FullyLoaded  = 1 << 2    // Handled by execBf_specialIndication and libCOL_specialIndication_fullLoad.
};

// Struct for the elevator status message0
struct ElevatorStatusMastertoLOP0 
{
    uint8_t  reserved0;       // Byte 0 (unused here)
    uint8_t  currentFloor;    // Byte 1
    uint8_t  ElevatorDataMastertoLOP0;     // Byte 2 (bit field)
    uint8_t  reserved3;       // Byte 3
    uint8_t  reserved4;       // Byte 4
    uint8_t  AttendantDataMastertoLOP0;  // Byte 5 (bit field)
    uint8_t  LoadDataMastertoLOP0;       // Byte 6 (bit field)
    uint8_t  runningSpeed;    // Byte 7 (0~8)
};


/*******************ElevatorStatusMastertoLOP1 Data Field ********************************************************/


// Enums for status flags1 in Byte 1
enum class ElevatorSpecialAccessMastertoLOP1 : uint8_t 
{
    VIP     = 1 << 4       // Handled by execBf_specialIndication and libCOL_specialIndication_vipTransport as well as execBf_specialFunctionAcknowledgement and libCOL_special_vipService_ack
};
    
// Enums for status flags1 in Byte 2
enum class ElevatorSpecialIndicationMastertoLOP1 : uint8_t 
{
    UPS            = 1 << 3,   // Handled by execBf_specialIndication and libCOL_specialIndication_emergencyPowerOperation
    Earthquake2    = 1 << 1,   // 
    Earthquake1    = 1 << 0
};

// Enum for the elevator state flags in Byte 5
enum class ElevatorStateMastertoLOP1 : uint8_t
{
    Decelerating         = 1 << 5    // No idea How to translate this to mabe user defined libCOL_specialIndication_Userdef7 self define a type.
};


// Struct for the elevator status message1
struct ElevatorStatusMastertoLOP1 
{
    uint8_t  reserved0;            // Byte 0 (unused here)
    uint8_t  ElevatorSpecialAccessMastertoLOP1;  // Byte 1
    uint8_t  ElevatorSpecialIndicationMastertoLOP1;   // Byte 2 (bit field)
    uint8_t  reserved3;            // Byte 3
    uint8_t  reserved4;            // Byte 4
    uint8_t  ElevatorStateMastertoLOP1; // Byte 5 (bit field)
};

/*******************ElevatorStatusMastertoLOP2 Data Field ********************************************************/


struct ElevatorStatusMastertoLOP2 
{
    uint8_t  FloorAscL;            // Byte 0 (ASCII code low-order display) //  Handled by 0x62B0 or directly sent as message value in the execBf_positionIndicationBinary , execBf_positionIndicationGray, execBf_positionIndication7Segment
    uint8_t  FloorAscM;            // Byte 1 (ASCII code mid-digit display) // Handled by 0x62B0 or directly sent as message value in the execBf_positionIndicationBinary , execBf_positionIndicationGray, execBf_positionIndication7Segment
    uint8_t  FloorAscH;            // Byte 2 (ASCII code high-digit display) /  Handled by 0x62B0 or directly sent as message value in the execBf_positionIndicationBinary , execBf_positionIndicationGray, execBf_positionIndication7Segment
};


/*******************ElevatorStatusMastertoLOP3 Data Field ********************************************************/
// Byte 0: Elevator State 4

enum class ElevatorStateMastertoLOP3 : uint8_t 
{
    UpLantern       = 1 << 2,        // Handled by execBf_hallLantern libCOL_hallLantern_Up
    DownLantern     = 1 << 1,        // Handled by execBf_hallLantern libCOL_hallLantern_Down
    ArrivalGong     = 1 << 0         // Handled by execBf_arrivalIndication libCOL_arrivalIndication_NoDirection ??
};


struct ElevatorStatusMastertoLOP3 
{
    uint8_t  ElevatorStateMastertoLOP3;            // Byte 0 (used here)
};

/******************************************************************************************************************
 * *********************************************Commonly Used with both Car and Panel Calls*/

// 64 bits for 64 floors
struct FloorBitfield 
{
    uint8_t data[8]; // 8 bytes x 8 bits = 64 floors

    // Helper: check if a particular floor is set (1-based floor index)
    bool isFloorSet(uint8_t floor) const 
    {
        if (floor < 1 || floor > 64) return false;
        uint8_t byteIdx = (floor - 1) / 8;
        uint8_t bitIdx = (floor - 1) % 8;
        return (data[byteIdx] & (1 << bitIdx)) != 0;
    }

    // Helper: set a floor
    void setFloor(uint8_t floor) 
    {
        if (floor < 1 || floor > 64) return;
        uint8_t byteIdx = (floor - 1) / 8;
        uint8_t bitIdx = (floor - 1) % 8;
        data[byteIdx] |= (1 << bitIdx);
    }

    // Helper: clear a floor
    void clearFloor(uint8_t floor) 
    {
        if (floor < 1 || floor > 64) return;
        uint8_t byteIdx = (floor - 1) / 8;
        uint8_t bitIdx = (floor - 1) % 8;
        data[byteIdx] &= ~(1 << bitIdx);
    }
};


struct FloorMessage 
{
    uint8_t floor;      // Byte1
};


/***********************************************  Master to COP Call Data Structure************************* 
***************************************************************************************************/

/*************************************ElevatorStatusMastertoCOP0****************************/

// Byte 2: Elevator Status Car 0
enum class ElevatorStatusDataMastertoCOP0 : uint8_t 
{
    FireService                = 1 << 7,
    LiftLock                   = 1 << 6,
    Fault_OutofService         = 1 << 5,
    Inspection                 = 1 << 3,
    Running                    = 1 << 2,
    RunningDown                = 1 << 1,
    RunningUp                  = 1 << 0
};

// Byte 5 Elevator Status Car 0

enum class AttendantFlagsMastertoCOP0 : uint8_t 
{
    AttendantBypass            = 1 << 1,
    AttendantService           = 1 << 0
};

// Byte 6 Elevator Status Car 0
enum class LoadCarFlagsMastertoCOP0 : uint8_t 
{
    Overload                   = 1 << 3,
    FullyLoaded                = 1 << 2
};

struct ElevatorStatusMastertoCOP0 
{
    uint8_t  reserved0;       // Byte 0 (unused here)
    uint8_t  currentFloor;    // Byte 1
    uint8_t  ElevatorStatusDataMastertoCOP0;     // Byte 2 (bit field)
    uint8_t  reserved3;       // Byte 3
    uint8_t  reserved4;       // Byte 4
    uint8_t  AttendantFlagsMastertoCOP0;  // Byte 5 (bit field)
    uint8_t  LoadCarFlagsMastertoCOP0;       // Byte 6 (bit field)
    uint8_t  runningSpeed;    // Byte 7 (0~8)
};


/*************************************ElevatorStatusMastertoCOP1****************************/



// Byte 2 : Car Status Indication

enum class ElevatorDataMastertoCOP1 : uint8_t 
{
    dooropeningdelay        = 1 << 6,      // Door opening delay --How to translate this to maybe user defined type ?. 
    ARD                     = 1 << 3      // Automatic Rescue Device --How to translate this to maybe user defined type ?.
};

// Byte 6 : Car Status Indication 2

enum class SoundFlagsMastertoCOP1 : uint8_t 
{
    FrontDoorBuzzerSignal   = 1 << 4,     // To be Found , meanwhile handled by execBf_specialIndication and libCOL_specialIndication_doorOpeningBuzzer
    FrontDooropeninglightOutput = 1 << 1, // To be Found , meanwhile handled by execBf_specialIndication and libCOL_specialIndication_doorOpeningLight
    FrontDoorclosinglightOutput = 1 << 0  // To be Found , meanwhile handled by execBf_specialIndication and libCOL_specialIndication_doorClosingLight
};


// Byte 7 : Car Status Indication 3
enum class LightFlagsMastertoCOP1 : uint8_t
{
    RearDooropeninglightOutput = 1 << 5,
    RearDoorclosinglightOutput = 1 << 4
};


struct ElevatorStatusMastertoCOP1 
{
    uint8_t  reserved0;               // Byte 0 (unused here)
    uint8_t  reserved1;               // Byte 1
    uint8_t  ElevatorDataMastertoCOP1;            // Byte 2 (bit field)
    uint8_t  reserved3;               // Byte 3
    uint8_t  reserved4;               // Byte 4
    uint8_t  SoundFlagsMastertoCOP1; // Byte 5 (bit field)
    uint8_t  reserved6;               // Byte 6 (bit field)
    uint8_t  LightFlagsMastertoCOP1;            // Byte 7 (0~8)
}; 
/*************************************ElevatorStatusMastertoCOP2****************************/

// Byte 0: Elevator Status Car 2
enum class ElevatorDataMastertoCOP2 : uint8_t 
{
    RearDoorBuzzerSignal   = 1 << 0
};

struct ElevatorStatusMastertoCOP2 
{
    uint8_t ElevatorDataMastertoCOP2; // Byte 0 (used here)
};


/***********************************************  COP to Master Call Data Structure*************************
***************************************************************************************************/


/*************************************COPtoMasterCallspecialfunction_FS****************************/

enum class SpecialFunctionCOPtoMasterFS1 : uint8_t 
{
    AttendantBypassSignal          = 1<< 7,
    VIPSignal                      = 1 << 6,
    AttendantServiceSignal         = 1 << 5,
    DoorHoldbutton                 = 1 << 2,
    DoorClosebutton                = 1 << 1,
    DoorOpenbutton                 = 1 << 0

};

// Byte 1 : SwitchSignals
enum class SpecialFunctionCOPtoMasterFS2 : uint8_t 
{
    Firefighterswitchsignal        = 1 << 2,
    Fanswitchsignal                = 1 << 1,
    lightingswitchsignal           = 1 << 0
};


struct COPtoMasterDataspecialfunction_FS
{
    uint8_t SpecialFunctionCOPtoMasterFS1; // Byte 0 (used here)
    uint8_t SpecialFunctionCOPtoMasterFS2; // Byte 1 (used here)
};


/*************************************COPtoMasterCallspecialfunction_RS****************************/

enum class SpecialFunctionCOPtoMasterRS1 : uint8_t 
{
    AttendantBypassSignal          = 1<< 7,
    VIPSignal                      = 1 << 6,
    AttendantServiceSignal         = 1 << 5,
    DoorHoldbutton                 = 1 << 2,
    DoorClosebutton                = 1 << 1,
    DoorOpenbutton                 = 1 << 0

};

// Byte 1 : SwitchSignals
enum class SpecialFunctionCOPtoMasterRS2 : uint8_t 
{
    Firefighterswitchsignal        = 1 << 2,
    Fanswitchsignal                = 1 << 1,
    lightingswitchsignal           = 1 << 0
};


struct COPtoMasterDataspecialfunction_RS
{
    uint8_t SpecialFunctionCOPtoMasterRS1; // Byte 0 (used here)
    uint8_t SpecialFunctionCOPtoMasterRS2; // Byte 1 (used here)
};



class NKET_Protokoll 
{
public:
    NKET_Protokoll() // Constructor
    {
        // Initialize filterIDs from IncomingCANMessages
        //CANopenNode::instance().getHardwareInterface()->registerCANIDFilters(filterIDs);
    }

    // Function declarations for parsing CAN messages Land Call
    ElevatorStatusMastertoLOP0 parseElevatorStatuslandData0(const uint8_t* data); // CAN ID : 0x0001FF00
    ElevatorStatusMastertoLOP1 parseElevatorStatuslandData1(const uint8_t* data); // CAN ID : 0x0001FF01
    ElevatorStatusMastertoLOP2 parseElevatorStatuslandData2(const uint8_t* data); // CAN ID : 0x0001FF0B
    ElevatorStatusMastertoLOP3 parseElevatorStatuslandData3(const uint8_t* data); // CAN ID : 0x00010312

    // Function declarations for parsing CAN messages Land Call

    FloorBitfield parseFloorBitfield(const uint8_t* data); // Use for 0x00010303, 0x00010304, 0x00010305, 0x00010306 , 0x00010402, 0x00010502 , 0x00040102, 0x00050102 , 0x00050102.
    FloorMessage parseFloorMessage(const uint8_t* data); // Use for 0x00030120, 0x00030121 , 0x00030124, 0x00030125, 0x00030126, 0x00030127
    
    // Function declarations for parsing CAN messages Car Call

    ElevatorStatusMastertoCOP0 parseElevatorStatusCarData0(const uint8_t* data); // CAN ID : 0x0001FFF0
    ElevatorStatusMastertoCOP1 parseElevatorStatusCarData1(const uint8_t* data); // CAN ID : 0x0001FFF1
    ElevatorStatusMastertoCOP2 parseElevatorStatusCarData2(const uint8_t* data); // CAN ID : 0x0001FFFA
    COPtoMasterDataspecialfunction_FS parseCarCallSpecialFunctionData_FS(const uint8_t* data); // Use for 0x00040101, 0x00050101
    COPtoMasterDataspecialfunction_RS parseCarCallSpecialFunctionData_RS(const uint8_t* data); // Use for 0x00040101, 0x00050101
    std::array<uint32_t, 13> getIncomingCANMessageIDs() const ;
   

    private:


};





















#endif // NKET_PROTOKOLL_H
