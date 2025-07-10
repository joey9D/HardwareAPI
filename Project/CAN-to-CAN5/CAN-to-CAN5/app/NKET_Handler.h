#ifndef NKET_HANDLER_H
#define NKET_HANDLER_H

#include "NKET_Protokoll.h"
#include "CiA417_CmdHandler.h"
#include "Hardware_Factory.h"


namespace
{

/*******************************************************Output Signal 6200********************************************************************************************************************/
/**************************************************************************************************************************** */
/*** Bitmap for Master to LOP0 *******************************************************/
static const NKET_Handler::BitfieldMapping bitmapMastertoLOP0[] = 
    {
        { static_cast<uint8_t>(ElevatorDataMastertoLOP0::FireService), libCOL_of_specialIndication, libCOL_of_specialIndication_FireService },
        { static_cast<uint8_t>(ElevatorDataMastertoLOP0::LiftLock),    libCOL_of_specialIndication, libCOL_special_keyLock1_ack },
        { static_cast<uint8_t>(ElevatorDataMastertoLOP0::Fault),       libCOL_of_specialIndication, libCOL_specialIndication_outOfOrder },
        { static_cast<uint8_t>(ElevatorDataMastertoLOP0::Inspection),  libCOL_of_specialIndication, libCOL_specialIndication_liftInMaintenance },
        { static_cast<uint8_t>(ElevatorDataMastertoLOP0::RunningUp), libCOL_of_directionIndication, libCOL_directionIndication_Up },
        { static_cast<uint8_t>(ElevatorDataMastertoLOP0::RunningDown), libCOL_of_directionIndication, libCOL_directionIndication_Down }
        // ... add more as needed ...
    };
// AttendantDataMastertoLOP0 mappings
static const  NKET_Handler::BitfieldMapping attendantDataMapMastertoLOP0[] = 
    {
        { static_cast<uint8_t>(AttendantDataMastertoLOP0::AttendantBypass), libCOL_of_specialFunctionAcknowledgement, libCOL_special_liftAttendantDriveThroughButton_ack },
        { static_cast<uint8_t>(AttendantDataMastertoLOP0::AttendantService), libCOL_of_specialIndication, libCOL_specialIndication_liftAttendantService }
        // ... add more as needed ...
    };

// LoadDataMastertoLOP0 mappings
static const NKET_Handler::BitfieldMapping loadDataMapMastertoLOP0[] = 
    {
        { static_cast<uint8_t>(LoadDataMastertoLOP0::Overload), libCOL_of_specialIndication, libCOL_specialIndication_overLoad },
        { static_cast<uint8_t>(LoadDataMastertoLOP0::FullyLoaded), libCOL_of_specialIndication, libCOL_specialIndication_fullLoad }
        // ... add more as needed ...
    };

/*Bitmap for Master to LOP1*******************************************************/

static const NKET_Handler::BitfieldMapping mapSpecialIndicationMastertoLOP1[] = 
    {
        { static_cast<uint8_t>(ElevatorSpecialIndicationMastertoLOP1::UPS), libCOL_of_specialIndication, libCOL_specialIndication_emergencyPowerOperation },
        { static_cast<uint8_t>(ElevatorSpecialIndicationMastertoLOP1::Earthquake2), libCOL_of_specialFunctionAcknowledgement, libCOL_special_earthquakeDetector_ack },
        { static_cast<uint8_t>(ElevatorSpecialIndicationMastertoLOP1::Earthquake1), libCOL_of_specialFunctionAcknowledgement, libCOL_special_earthquakeDetector_ack }
        // ... add more as needed ...
    };

static const NKET_Handler::BitfieldMapping mapSpecialAccessMastertoLOP1[] = 
    {
        { static_cast<uint8_t>(ElevatorSpecialAccessMastertoLOP1::VIP), libCOL_of_specialIndication, libCOL_specialIndication_vipTransport }
        // ... add more as needed ...
    };

static const NKET_Handler::BitfieldMapping mapElevatorStateMastertoLOP1[] = 
    {
        { static_cast<uint8_t>(ElevatorStateMastertoLOP1::Decelerating), libCOL_of_specialIndication, libCOL_specialIndication_Userdef7 }

        // ... add more as needed ...
    };
    

/*** Bitmap for Master to LOP2 *******************************************************/

// static const NKET_Handler::BitfieldMapping mapElevatorDataMastertoLOP2[] = 
//     {
//         { static_cast<uint8_t>(ElevatorDataMastertoLOP2::FireService), libCOL_of_specialIndication, libCOL_of_specialIndication_FireService },
//         { static_cast<uint8_t>(ElevatorDataMastertoLOP2::LiftLock),    libCOL_of_specialIndication, libCOL_special_keyLock1_ack },
//         { static_cast<uint8_t>(ElevatorDataMastertoLOP2::Fault),       libCOL_of_specialIndication, libCOL_specialIndication_outOfOrder }
//         // ... add more as needed ...
//     };

/*** Bitmap for Master to LOP3 *******************************************************/

static const NKET_Handler::BitfieldMapping mapElevatorDataMastertoLOP3[] = 
    {
        { static_cast<uint8_t>(ElevatorStateMastertoLOP3::UpLantern), libCOL_of_hallLantern, libCOL_hallLantern_Up },
        { static_cast<uint8_t>(ElevatorStateMastertoLOP3::DownLantern),    libCOL_of_hallLantern, libCOL_hallLantern_Down },
        { static_cast<uint8_t>(ElevatorStateMastertoLOP3::ArrivalGong),       libCOL_of_arrivalIndication, libCOL_arrivalIndication_NoDirection }
        // ... add more as needed ...
    };


/*** Bitmap for Master to COP0 *******************************************************/

static const NKET_Handler::BitfieldMapping mapStatusDataMastertoCOP0[] = 
    {   
        
        { static_cast<uint8_t>(ElevatorStatusDataMastertoCOP0::FireService), libCOL_of_specialIndication, libCOL_of_specialIndication_FireService },
        { static_cast<uint8_t>(ElevatorStatusDataMastertoCOP0::LiftLock),    libCOL_of_specialIndication, libCOL_special_keyLock1_ack },
        { static_cast<uint8_t>(ElevatorStatusDataMastertoCOP0::Fault_OutofService),       libCOL_of_specialIndication, libCOL_special_indication_outOfOrder },
        { static_cast<uint8_t>(ElevatorStatusDataMastertoCOP0::Inspection),  libCOL_of_specialIndication, libCOL_special_indication_inspection },
        { static_cast<uint8_t>(ElevatorStatusDataMastertoCOP0::RunningUp), libCOL_of_directionIndication, libCOL_directionIndication_Up },
        { static_cast<uint8_t>(ElevatorStatusDataMastertoCOP0::RunningDown), libCOL_of_directionIndication, libCOL_directionIndication_Down }
        // ... add more as needed ...
        // for moving up and down use separate if statements.
    };

static const NKET_Handler::BitfieldMapping mapAttendantFlagsMastertoCOP0[] = 
    {
        { static_cast<uint8_t>(AttendantFlagsMastertoCOP0::AttendantBypass), libCOL_of_specialFunctionAcknowledgement, libCOL_special_liftAttendantDriveThroughButton_ack },
        { static_cast<uint8_t>(AttendantFlagsMastertoCOP0::AttendantService), libCOL_of_specialIndication, libCOL_specialIndication_liftAttendantService }
        // ... add more as needed ...
    };

static const NKET_Handler::BitfieldMapping mapLoadDataMastertoCOP0[] = 
    {
        { static_cast<uint8_t>(LoadCarFlagsMastertoCOP0::Overload), libCOL_of_specialIndication, libCOL_specialIndication_overLoad },
        { static_cast<uint8_t>(LoadCarFlagsMastertoCOP0::FullyLoaded), libCOL_of_specialIndication, libCOL_specialIndication_fullLoad }
        // ... add more as needed ...
    };


/*** Bitmap for Master to COP1 *******************************************************/

static const NKET_Handler::BitfieldMapping mapSpecialIndicationMastertoCOP1[] = 
    {
        { static_cast<uint8_t>(ElevatorDataMastertoCOP1::dooropeningdelay), libCOL_of_specialIndication, libCOL_specialIndication_Userdef8 },
        { static_cast<uint8_t>(ElevatorDataMastertoCOP1::ARD), libCOL_of_specialIndication, libCOL_specialIndication_Userdef9 }        // ... add more as needed ...
    };  

static const NKET_Handler::BitfieldMapping mapSoundFlagsMastertoCOP1[] = 
    {
        { static_cast<uint8_t>(SoundFlagsMastertoCOP1::FrontDoorBuzzerSignal), libCOL_of_specialIndication, libCOL_specialIndication_Userdef10 },
        { static_cast<uint8_t>(SoundFlagsMastertoCOP1::FrontDooropeninglightOutput), libCOL_of_liftLightsAcknowledgement, libCOL_liftLightsMainLight_On_ack },
        { static_cast<uint8_t>(SoundFlagsMastertoCOP1::FrontDoorclosinglightOutput), libCOL_of_liftLightsAcknowledgement, libCOL_liftLightMainLight_Off_ack }
        // ... add more as needed ...
    };

static const NKET_Handler::BitfieldMapping mapLightsFlagsMastertoCOP1[] = 
    {
        { static_cast<uint8_t>(LightFlagsMastertoCOP1::RearDooropeninglightOutput), libCOL_of_liftLightsAcknowledgement, libCOL_liftLightSecondaryLight_On_ack },
        { static_cast<uint8_t>(LightFlagsMastertoCOP1::RearDoorclosinglightOutput), libCOL_of_liftLightsAcknowledgement, libCOL_liftLightSecondaryLight_Off_ack }
        // ... add more as needed ...
    };
/*****************************ElevatorStatusMastertoCOP2************************************************************************************/

static const NKET_Handler::BitfieldMapping mapElevatorStatusMastertoCOP2[] = 
    {
        { static_cast<uint8_t>(ElevatorDataMastertoCOP2::RearDoorBuzzerSignal), libCOL_of_specialIndication, libCOL_specialIndication_Userdef11 }
        // ... add more as needed ...
    };


/*********************************************************Input Signals for 6100 *******************************************************************************************************/    
/********************************************************************************************************************************************************* */
/***********************************COPtoMasterCallspecialfunction_FS*******************************************************************/

static const NKET_Handler::BitfieldMapping mapCOPtoMasterCallspecialfunction_FS1[] = 
    {
        { static_cast<uint8_t>(SpecialFunctionCOPtoMasterFS1::AttendantBypassSignal), libCOL_if_specialFunction, libCOL_special_liftAttendantDriveThroughButton ,0 },
        { static_cast<uint8_t>(SpecialFunctionCOPtoMasterFS1::VIPSignal), libCOL_if_specialFunction, libCOL_special_vipService ,0 },
        { static_cast<uint8_t>(SpecialFunctionCOPtoMasterFS1::AttendantServiceSignal), libCOL_if_specialFunction, libCOL_special_attendantService ,0 },
        { static_cast<uint8_t>(SpecialFunctionCOPtoMasterFS1::DoorHoldbutton), libCOL_if_specialFunction, libCOL_special_requestDoorOpen ,0 }, 
        { static_cast<uint8_t>(SpecialFunctionCOPtoMasterFS1::DoorClosebutton), libCOL_if_specialFunction, libCOL_special_requestDoorClose ,0 },
        { static_cast<uint8_t>(SpecialFunctionCOPtoMasterFS1::DoorOpenbutton), libCOL_if_specialFunction, libCOL_special_requestDoorOpen ,0 }        // ... add more as needed ...
    };
static const NKET_Handler::BitfieldMapping mapSpecialFunctionCOPtoMasterFS2[] = 
    {
        { static_cast<uint8_t>(SpecialFunctionCOPtoMasterFS2::Firefighterswitchsignal), libCOL_if_specialFunction, libCOL_special_fireService ,1 },
        { static_cast<uint8_t>(SpecialFunctionCOPtoMasterFS2::Fanswitchsignal), libCOL_if_specialFunction, libCOL_special_requestFan1 ,1 },
        { static_cast<uint8_t>(SpecialFunctionCOPtoMasterFS2::lightingswitchsignal), libCOL_if_liftLights, libCOL_light_mainCarLightOnRequest ,1 }        // ... add more as needed ...
    };

/***********************************COPtoMasterCallspecialfunction_RS*******************************************************************/

static const NKET_Handler::BitfieldMapping mapCOPtoMasterCallspecialfunction_RS1[] = 
    {
        { static_cast<uint8_t>(SpecialFunctionCOPtoMasterRS1::AttendantBypassSignal), libCOL_if_specialFunction, libCOL_special_liftAttendantDriveThroughButton ,0 },
        { static_cast<uint8_t>(SpecialFunctionCOPtoMasterRS1::VIPSignal), libCOL_if_specialFunction, libCOL_special_vipService ,0 },
        { static_cast<uint8_t>(SpecialFunctionCOPtoMasterRS1::AttendantServiceSignal), libCOL_if_specialFunction, libCOL_special_attendantService ,0 },
        { static_cast<uint8_t>(SpecialFunctionCOPtoMasterRS1::DoorHoldbutton), libCOL_if_specialFunction, libCOL_special_requestDoorOpen ,0 }, 
        { static_cast<uint8_t>(SpecialFunctionCOPtoMasterRS1::DoorClosebutton), libCOL_if_specialFunction, libCOL_special_requestDoorClose ,0 },
        { static_cast<uint8_t>(SpecialFunctionCOPtoMasterRS1::DoorOpenbutton), libCOL_if_specialFunction, libCOL_special_requestDoorOpen ,0 }        // ... add more as needed ...
    };
static const NKET_Handler::BitfieldMapping mapSpecialFunctionCOPtoMasterRS2[] = 
    {
        { static_cast<uint8_t>(SpecialFunctionCOPtoMasterRS2::Firefighterswitchsignal), libCOL_if_specialFunction, libCOL_special_fireService ,1 },
        { static_cast<uint8_t>(SpecialFunctionCOPtoMasterRS2::Fanswitchsignal), libCOL_if_specialFunction, libCOL_special_requestFan1 ,1 },
        { static_cast<uint8_t>(SpecialFunctionCOPtoMasterRS2::lightingswitchsignal), libCOL_if_liftLights, libCOL_light_mainCarLightOnRequest ,1 }        // ... add more as needed ...
    };

}; // namespace



class NKET_Handler
{

public:
	NKET_Handler(HardwareInterface* hardware); // Constructor to initialize the NKET_Handler instance with a HardwareInterface pointer
    bool initCAN(); // Initialize the NKET handler
    void initNKETStack(); // Initialize the CAN interface for NKET
    void start(); // Start the NKET handler
    void stop(); // Stop the NKET handler
    void process(); // Process incoming CAN messages and handle them accordingly
    void errorHandler(); // Handle errors in the NKET handler
    void reset(); // Reset the NKET handler state
    void send(); // Send CAN messages
    bool isCANInitOk();


    // Function to handle incoming CAN2.0 messages
    void handleIncomingCANMessage(const uint8_t* data, uint32_t canId);
    void handleIncomingCiA417Message(const virtualIOMapping_data_t& msg); // Handle incoming CiA417 messages

     // Function to send CANOpen messages
    void sendCANMessage(const uint8_t* data, uint32_t canId);

    /* Function to map messages from Master to LOP0, LOP1, LOP2, LOP3, COP0, COP1, and COP2 as well as 
    LOP to Master and COP to Master*/
    void mapMastertoLOP0(const ElevatorStatusMastertoLOP0& msg); // Handle ElevatorStatusMastertoLOP0 message
    void mapMastertoLOP1(const ElevatorStatusMastertoLOP1& msg); // Handle ElevatorStatusMastertoLOP1 message
    void mapMastertoLOP2(const ElevatorStatusMastertoLOP2& msg); // Handle ElevatorStatusMastertoLOP2 message
    void mapMastertoLOP3(const ElevatorStatusMastertoLOP3& msg); // Handle ElevatorStatusMastertoLOP3 message
    void mapMastertoLOPHallCallUp_FS(const FloorBitfield& msg); // Handle FloorUp message
    void mapMastertoLOPHallCallDown_FS(const FloorBitfield& msg); // Handle FloorDown message
    void mapMastertoLOPHallCallUp_RS(const FloorBitfield& msg); // Handle FloorUp message
    void mapMastertoLOPHallCallDown_RS(const FloorBitfield& msg); // Handle FloorDown message
    void mapLOPtoMasterHallCallFS(const virtualIOMapping_data_t& msg); // Handle SpecialFunctionLOPtoMasterFS1 message
    void mapLOPtoMasterHallCallRS(const virtualIOMapping_data_t& msg); // Handle SpecialFunctionLOPtoMasterRS1 message
    void mapLOPtoMasterLiftLock_Activate(const virtualIOMapping_data_t& msg); // Handle SpecialFunctionLOPtoMasterFS1 message
    void mapLOPtoMasterLiftLock_Deactivate(const virtualIOMapping_data_t& msg); // Handle SpecialFunctionLOPtoMasterFS1 message
    void mapLOPtoMasterLiftLock_Activate(const virtualIOMapping_data_t& msg); // Handle SpecialFunctionLOPtoMasterFS1 message
    void mapLOPtoMasterLiftLock_Activate(const virtualIOMapping_data_t& msg); // Handle SpecialFunctionLOPtoMasterFS1 message
    void mapMastertoCOP0(const ElevatorStatusMastertoCOP0& msg); // Handle ElevatorStatusMastertoCOP0 message
    void mapMastertoCOP1(const ElevatorStatusMastertoCOP1& msg); // Handle ElevatorStatusMastertoCOP1 message
    void mapMastertoCOP2(const ElevatorStatusMastertoCOP2& msg); // Handle ElevatorStatusMastertoCOP2 message
    void mapMastertoCOPButtonLights_FS(const FloorBitfield& msg); // Handle FrontDoorButtonLights message
    void mapMastertoCOPButtonLights_RS(const FloorBitfield& msg); // Handle RearDoorButtonLights message
    void mapSpecialFunctionCOPtoMasterFS(const virtualIOMapping_data_t& msg); // Handle SpecialFunctionCOPtoMasterFS1 message
    void mapSpecialFunctionCOPtoMasterRS(const virtualIOMapping_data_t& msg); // Handle SpecialFunctionCOPtoMasterRS1 message
    void mapCOPtoMasterFloorCall(const virtualIOMapping_data_t& msg); // Handle COPtoMasterDataspecialfunction_FS message
    void mapCOPtoMasterFloorCallCancel(const virtualIOMapping_data_t& msg); // Handle COPtoMasterDataspecialfunction_FS message

    struct BitfieldMapping
    {
        uint8_t bitmask; // Bitmask for the mapping
        uint8_t basicFunction; // Basic function associated with the mapping
        uint8_t subFunction; // Sub-function associated with the mapping
        uint8_t byteIndex{0}; // Byte index for the mapping

    };

private:

    NKET_Protokoll proto;
    uint32_t lastError = 0; // Variable to store the last error state
    uint8_t initState = 0; // Variable to store the initialization state
    inline void setinitState(uint8_t val) { initState = val; }
	void setLastError(uint32_t val) { lastError = val; }
    inline uint32_t getLastError() const { return lastError; }
    HardwareInterface* hardware = nullptr; // Pointer to the HardwareInterface instance
    uint64_t lastHallUpCalls = 0;
    uint64_t lastHallDownCalls = 0;
    bool isSubFunctioninTable(uint8_t subFunction, const BitfieldMapping* table, size_t tableSize);
   
};


#endif // NKET_HANDLER_H
