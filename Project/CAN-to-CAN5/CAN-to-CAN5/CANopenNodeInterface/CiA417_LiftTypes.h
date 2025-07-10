/*
 * LiftTypes.h
 *
 *  Created on: Dec 12, 2023
 *      Author: michael.grathwohl
 *
 *  abgeschaut von Jan Panier
 */

#ifndef CIA417_LIFTTYPES_H_
#define CIA417_LIFTTYPES_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/* ------------------------------------------------------------------------------------ */
/* CiA CANopen General start */
/* ------------------------------------------------------------------------------------ */

typedef enum libCOL_baudrate_tag
{
	//libCOL_BAUD_auto 	= 0,
	libCOL_BAUD_10k 	= 10,
	libCOL_BAUD_20k 	= 20,
	libCOL_BAUD_50k 	= 50,
	libCOL_BAUD_125k 	= 125,
	libCOL_BAUD_250k 	= 250,
	libCOL_BAUD_500k 	= 500,
	libCOL_BAUD_800k	= 800,
	libCOL_BAUD_1M 		= 1000
} libCOL_baudrate_t;

typedef struct virtualIOMapping_data
{
	uint8_t basicFunction =0;
	uint8_t subFunction = 0;
	uint8_t lift = 0;
	uint8_t floor = 0;
	uint8_t door = 0;
	uint8_t functionData = 0;
} virtualIOMapping_data_t;


/* ------------------------------------------------------------------------------------ */
/* CiA CANopen General end */
/* ------------------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------------------ */
/* CiA 417 General start */
/* ------------------------------------------------------------------------------------ */

// Description from CiA-417-2 0x1000
// used in Object 0x6000
typedef enum libCOL_deviceType_tag {
	libCOL_multipleVirtualDevice 	= 0x0000,
	libCOL_callController 			= 0x0100,
	libCOL_inputPanel 				= 0x0200,
	libCOL_outputPanel 				= 0x0300,
	libCOL_carDoorController 		= 0x0400,
	libCOL_carDoor 					= 0x0500,
	libCOL_carPosition 				= 0x0600,
	libCOL_lightBarrier 			= 0x0700,
	libCOL_carDriveController 		= 0x0800,
	libCOL_carDrive 				= 0x0900,
	libCOL_loadMeasuring 			= 0x0A00,
	libCOL_remoteDataTransmission	= 0x0B00,
	libCOL_powerMeasuring 			= 0x0C00,
	libCOL_accessRequest 			= 0x0D00,
	libCOL_emergencyPhone 			= 0x0E00,
	libCOL_positionSupervisor 		= 0x0F00,
	libCOL_monitoring 				= 0x1000,
	libCOL_energyRecoverySystem		= 0x1100,
	//libCOL_Reserved 				= 0x1200-0xFD00,
	libCOL_bootloader 				= 0xFE00
	//libCOL_Reserved 				= 0xFF00,
} libCOL_deviceType_t;

typedef enum libCOL_LiftBits_tag
{
	libCOL_lift1 = 0x01,
	libCOL_lift2 = 0x02,
	libCOL_lift3 = 0x04,
	libCOL_lift4 = 0x08,
	libCOL_lift5 = 0x10,
	libCOL_lift6 = 0x20,
	libCOL_lift7 = 0x40,
	libCOL_lift8 = 0x80
} libCOL_LiftBits_t;

typedef union libCOL_Lift_tag
{
	uint8_t raw;
	libCOL_LiftBits_t bits : 8;
	struct
	{
		uint8_t lift1 : 1;
		uint8_t lift2 : 1;
		uint8_t lift3 : 1;
		uint8_t lift4 : 1;
		uint8_t lift5 : 1;
		uint8_t lift6 : 1;
		uint8_t lift7 : 1;
		uint8_t lift8 : 1;
	} bitsSingle;
} libCOL_Lift_t;

typedef enum libCOL_DoorBit_tag
{
	libCOL_Floor_CarPanels	= 0x00,
	//Floor panels: 0x01 - 0xFE
	libCOL_Floor_NotUsed	= 0xFF
} libCOL_DoorBit_t;

typedef enum libCOL_doorBits_tag
{
	libCOL_door1 			= 0x01,
	libCOL_door2 			= 0x02,
	libCOL_door3 			= 0x04,
	libCOL_door4 			= 0x08,

	libCOL_sourceDoor1 		= 0x01,
	libCOL_sourceDoor2 		= 0x02,
	libCOL_sourceDoor3 		= 0x04,
	libCOL_sourceDoor4 		= 0x08,
	libCOL_destinationDoor1 = 0x10,
	libCOL_destinationDoor2 = 0x20,
	libCOL_destinationDoor3 = 0x40,
	libCOL_destinationDoor4	= 0x80
} libCOL_doorBits_t;

typedef union libCOL_Door_tag
{
	uint8_t raw;
	struct
	{
		uint8_t door1 : 1;
		uint8_t door2 : 1;
		uint8_t door3 : 1;
		uint8_t door4 : 1;
	} call;
	struct
	{
		uint8_t sourceDoor1 : 1;
		uint8_t sourceDoor2 : 1;
		uint8_t sourceDoor3 : 1;
		uint8_t sourceDoor4 : 1;
		uint8_t destinationDoor1 : 1;
		uint8_t destinationDoor2 : 1;
		uint8_t destinationDoor3 : 1;
		uint8_t destinationDoor4 : 1;
	} destinationCall;
} libCOL_Door_t;

/* ------------------------------------------------------------------------------------ */
/* CiA 417 General end */
/* ------------------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------------------ */
/* CiA 417 Object 0x6100 (Master Input, Slave Output) start */
/* ------------------------------------------------------------------------------------ */

typedef enum libCOL_inputBasicFunction_tag
{
	libCOL_if_Lift_status_information_request	= 0x00,
	libCOL_if_generic 							= 0x01,
	libCOL_if_hallStandard 						= 0x02,
	libCOL_if_hallLowPriority 					= 0x03,
	libCOL_if_hallHighPriority 					= 0x04,
	libCOL_if_carCallStandard 					= 0x05,
	libCOL_if_carCallLowPriority 				= 0x06,
	libCOL_if_carCallHighPriority 				= 0x07,
	libCOL_if_destinationCallStandard 			= 0x08,
	libCOL_if_destinationCallLowPriority 		= 0x09,
	libCOL_if_destinationCallHighPriority 		= 0x0A,
	libCOL_if_destinationFloorCallStandard 		= 0x0B,
	libCOL_if_destinationFloorCallLowPriority 	= 0x0C,
	libCOL_if_destinationFloorCallHighPriority	= 0x0D,
	libCOL_if_specialFunction 					= 0x0E,
	libCOL_if_accessCodeUpload 					= 0x0F,
	libCOL_if_speechConnectionRequest 			= 0x10,
	libCOL_if_areaMonitoringConnectionRequest 	= 0x11,
	libCOL_if_fireDetector 						= 0x12,
	libCOL_if_inspectionControlCar 				= 0x13,
	//libCOL_if_Reserved						= 0x14,
	libCOL_if_floorSelector 					= 0x15,
	libCOL_if_statusSafetyCircuitries 			= 0x16,
	//libCOL_if_Reserved						= 0x17-0x1F,
	libCOL_if_guestCall 						= 0x20,
	//libCOL_if_Reserved						= 0x21-0x3E,
	libCOL_if_liftLights 						= 0x3F
	//libCOL_if_Reserved						= 0x40-0x7F,
	//libCOL_if_ManufacturerSpecific			= 0x80-0xFF,
} libCOL_inputBasicFunction_t;

typedef union libCOL_inputSubfunction_tag
{
	uint8_t raw;
	enum
	{
		/*
		 * libCOL_if_hallStandard,
		 * libCOL_if_hallLowPriority,
		 * libCOL_if_hallHighPriority
		 */
		libCOL_hall_up 								= 0x01,
		libCOL_hall_down 							= 0x02,
		libCOL_hall 								= 0x03,
		libCOL_hall_extraUp 						= 0x04,
		libCOL_hall_extraDown						= 0x05,
		libCOL_hall_extra 							= 0x06
	} hall : 8;
	enum
	{
		/* libCOL_if_specialFunction */
		libCOL_special_requestFan1 					= 0x01,
		libCOL_special_requestFan2 					= 0x02,
		libCOL_special_requestLoadTime1 			= 0x03,
		libCOL_special_requestLoadTime2 			= 0x04,
		libCOL_special_keyLock1 					= 0x05,
		libCOL_special_keyLock2 					= 0x06,
		libCOL_special_keyLock3 					= 0x07,
		libCOL_special_keyLock4 					= 0x08,
		libCOL_special_requestDoorOpen 				= 0x09,
		libCOL_special_requestDoorClose 			= 0x0A,
		libCOL_special_fireRecall 					= 0x0B,
		libCOL_special_fireService 					= 0x0C,
		libCOL_special_hallCallDisable 				= 0x0D,
		libCOL_special_attendantService 			= 0x0E,
		libCOL_special_vipService 					= 0x0F,
		libCOL_special_outOfOrder 					= 0x10,
		libCOL_special_bedPassengerService 			= 0x11,
		libCOL_special_specialService 				= 0x12,
		libCOL_special_serviceRun 					= 0x13,
		libCOL_special_dockingServiceEnable 		= 0x14,
		libCOL_special_dockungServiceUp 			= 0x15,
		libCOL_special_dockingServiceDown 			= 0x16,
		libCOL_special_fireAlarm 					= 0x17,
		libCOL_special_providePriority 				= 0x18,
		libCOL_special_liftAttendantStartButton 	= 0x19,
		libCOL_special_liftAttendantDriveThroughButton = 0x1A,
		libCOL_special_securityRun 					= 0x1B,
		libCOL_special_secondCallPanel 				= 0x1C,
		libCOL_special_doorEnable 					= 0x1D,
		libCOL_special_callCancelButtonFireOperation	= 0x1E,
		libCOL_special_fireAlarmReset 				= 0x1F,
		libCOL_special_bodyDetector 				= 0x20,
		libCOL_special_earthquakeDetector 			= 0x21,
		libCOL_special_cleaningTravel 				= 0x22,
		libCOL_special_emergencyAlarmReady			= 0x23,
		libCOL_special_emergencyAlarmGreenPictogram	= 0x24,
		libCOL_special_emergencyAlarmYellowPictogram	= 0x25,
		libCOL_special_emergencyAlarmButtonPressed	= 0x26
	} special : 8;
	enum
	{
		/* libCOL_if_inspectionControlCar */
		libCOL_inspection_carOn 					= 0x01,
		libCOL_inspection_carUp 					= 0x02,
		libCOL_inspection_carDown 					= 0x03,
		libCOL_inspection_carFast 					= 0x04,
		libCOL_inspection_pitOn 					= 0x05,
		libCOL_inspection_pitUp 					= 0x06,
		libCOL_inspection_pitDown 					= 0x07,
		libCOL_inspection_pitFast 					= 0x08,
		libCOL_inspection_emergencyRecallOperationOn	= 0x09,
		libCOL_inspection_emergencyRecallOperationUp	= 0x0A,
		libCOL_inspection_emergencyRecallOperationDown	= 0x0B
	} inspection : 8;
	enum
	{
		/* libCOL_if_floorSelector */
		libCOL_floorSelect_correctionSwitchTop 		= 0x01,
		libCOL_floorSelect_correctionSwitchBottom 	= 0x02,
		libCOL_floorSelect_reLevelSwitchUp 			= 0x03,
		libCOL_floorSelect_reLevelSwitchDown 		= 0x04,
		libCOL_floorSelect_impulseUp 				= 0x05,
		libCOL_floorSelect_impulseDown 				= 0x06,
		libCOL_floorSelect_levelPositionSwitchUp 	= 0x07,
		libCOL_floorSelect_levelPositionSwitchDown 	= 0x08,
		libCOL_floorSelect_preLimitSwitchTop 		= 0x09,
		libCOL_floorSelect_preLimitSwitchBottom 	= 0x0A,
		libCOL_floorSelect_levelSensor 				= 0x0B,
		libCOL_floorSelect_zoneSensor				= 0x0C
	} floorSelector : 8;
	enum
	{
		/* libCOL_if_statusSafetyCircuitries */
		libCOL_statusSafety_circuitry1 				= 0x01,
		libCOL_statusSafety_circuitry2 				= 0x02,
		libCOL_statusSafety_circuitry3 				= 0x03,
		libCOL_statusSafety_hallDoor 				= 0x04,
		libCOL_statusSafety_carDoor 				= 0x05,
		libCOL_statusSafety_doorLock 				= 0x06
	} statusSafety : 8;
	enum
	{
		/* libCOL_if_liftLights */
		libCOL_light_mainCarLightOnRequest 			= 0x01,
		libCOL_light_mainCarLightOffRequest 		= 0x02,
		libCOL_light_secondaryCarLightOnRequest 	= 0x03,
		libCOL_light_secondaryCarLightOffRequest 	= 0x04,
		libCOL_light_emergencyCarLightOnRequest 	= 0x05,
		libCOL_light_emergencyCarLightOffRequest	= 0x06,
		libCOL_light_ambientCarLightOnRequest 		= 0x07,
		libCOL_light_ambientCarLightOffRequest 		= 0x08,
		libCOL_light_panelCarLightOnRequest 		= 0x09,
		libCOL_light_panelCarLightOffRequest 		= 0x0A,
		libCOL_light_floorLightOnRequest 			= 0x0B,
		libCOL_light_floorLightOffRequest 			= 0x0C,
		libCOL_light_shaftLightOnRequest 			= 0x0D,
		libCOL_light_shaftLightOffRequest 			= 0x0E
	} light : 8;
} libCOL_inputSubfunction_t;

typedef union libCOL_inputFunctionData_tag
{
	uint8_t raw;
	struct
	{
		enum
		{
			libCOL_inputNotSet 			= 0x00,
			libCOL_inputSet 			= 0x01,
			libCOL_functionDefect 		= 0x02,
			libCOL_functionNotInstalled = 0x03
		} state : 2;
		uint8_t reserved : 2;
		bool response : 1;
		bool lock : 1;
	} destinationCall;
	//Note: The protocol only defines functionData for basic functions 0x8 to 0xD and 0xF for some reason but this one looks more like a generic one
	struct
	{
		enum
		{
			libCOL_genericInputNotSet 			= 0x00,
			libCOL_genericInputSet 				= 0x01,
			libCOL_genericFunctionDefect 		= 0x02,
			libCOL_genericFunctionNotInstalled	= 0x03
		} genericState : 2;
		uint8_t genericReserved : 2;
		bool genericResponse : 1;
		bool genericLock : 1;
	} generic;
	enum
	{
		libCOL_uploadTimeoutExpired 			= 0x00,
		libCOL_mediaDetected 					= 0x01
	} accessCode;
} libCOL_inputFunctionData_t;

typedef struct libCOL_input_tag
{
	libCOL_inputBasicFunction_t basicfunction : 8;
	libCOL_inputSubfunction_t subFunction;
	libCOL_Lift_t lift;
	uint8_t floor;
	libCOL_Door_t door;
	libCOL_inputFunctionData_t functionData;
} libCOL_input_t;

typedef struct libCOL_numbered_input_tag
{
	libCOL_input_t input;
	uint8_t number;
} libCOL_numbered_input_t;

typedef union libCOL_inputParameter1_tag
{
	uint32_t raw;
	struct
	{
		struct
		{
			bool enable : 1;
			uint8_t reserved : 7;
		} enable;
		uint8_t error : 8;
		uint16_t reserved : 16;
	} parameter;
} libCOL_inputParameter1_t;

typedef union libCOL_inputParameter2_tag
{
	uint32_t raw;
	struct
	{
		uint8_t reserved : 8;
		uint8_t limitation : 8;
		uint8_t sending : 8;
		uint8_t reserved2 : 8;
	} parameter;
} libCOL_inputParameter2_t;

typedef union libCOL_inputParameter3_tag
{
	uint32_t raw;
	struct
	{
		uint8_t debounce : 8;
		struct
		{
			bool lowEdge : 1;
			bool highEdge : 1;
			uint8_t reserved : 5;
			bool polarity : 1;
		} edgepol;
		uint16_t reserved : 16;
	} parameter;
} libCOL_inputParameter3_t;

/* ------------------------------------------------------------------------------------ */
/* CiA 417 Object 0x6100 end */
/* ------------------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------------------ */
/* CiA 417 Object 0x6200 (Master Output, Slave Input) start */
/* ------------------------------------------------------------------------------------ */

typedef enum libCOL_outputBasicFunction_tag
{
	/* Object 0x6200 */
	libCOL_of_callControllerCommand 						= 0x00,
	libCOL_of_genericOutput 								= 0x01,
	libCOL_of_hallCallAcknowledgement 						= 0x02,
	libCOL_of_lowPriorityHallCallAcknowledgement 			= 0x03,
	libCOL_of_highPriorityHallCallAcknowledgement 			= 0x04,
	libCOL_of_carCallAcknowledgement 						= 0x05,
	libCOL_of_lowPriorityCarCallAcknowledgement 			= 0x06,
	libCOL_of_highPriorityCarCallAcknowledgement 			= 0x07,
	libCOL_of_destinationCallAcknowledgement 				= 0x08,
	libCOL_of_lowPriorityDestinationCallAcknowledgement 	= 0x09,
	libCOL_of_highPriorityDestinationCallAcknowledgement 	= 0x0A,
	libCOL_of_destinationFloorAcknowledgement 				= 0x0B,
	libCOL_of_lowPriorityDestinationFloorAcknowledgement 	= 0x0C,
	libCOL_of_highPriorityDestinationFloorAcknowledgement	= 0x0D,
	libCOL_of_specialFunctionAcknowledgement 				= 0x0E,
	libCOL_of_accessCodeUploadAcknowledgement 				= 0x0F,
	libCOL_of_speechConnectionAcknowledgement 				= 0x10,
	libCOL_of_areaMonitoringConnectionAcknowledgement 		= 0x11,
	//libCOL_of_Reserved									= 0x12-0x1F,
	libCOL_of_guestCallAcknowledgement 						= 0x20,
	//libCOL_of_Reserved									= 0x21-0x3E,
	libCOL_of_liftLightsAcknowledgement 					= 0x3F,
	libCOL_of_positionIndication 							= 0x40,
	libCOL_of_hallLantern 									= 0x41,
	libCOL_of_directionIndication 							= 0x42,
	libCOL_of_specialIndication 							= 0x43,
	libCOL_of_arrivalIndication 							= 0x44,
	//libCOL_of_Reserved									= 0x45-0x46,
	libCOL_of_vocalFloorsAnnouncement 						= 0x47,
	libCOL_of_vocalUserMessage 								= 0x48,
	libCOL_of_musicPlayback 								= 0x49,
	libCOL_of_miscellaneousOutputs 							= 0x4A,
	libCOL_of_singleFaultIndication 						= 0x4B,
	libCOL_of_nextStop 										= 0x4C,
	libCOL_of_timeToDoorClosure 							= 0x4D,
	libCOL_of_liftStatusIndication 							= 0x4E,
	//libCOL_of_Reserved									= 0x4F-0x7F,
	//libCOL_of_ManufacturerSpecific						= 0x80-0xFF,
	libCOL_of_positionIndicationBinary 						= 0x80,
	libCOL_of_positionIndicationGray 						= 0x81,
	libCOL_of_positionIndication7Segment 					= 0x83,
	libCOL_of_vocalFloorsAnnouncementBinary 				= 0x86,
	libCOL_of_vocalFloorsAnnouncementGray 					= 0x87
} libCOL_outputBasicFunction_t;

typedef union libCOL_outputSubFunction_tag {
	uint8_t raw;
	enum
	{
		/* libCOL_of_callControllerCommand */
		libCOL_requestAll 						= 0x00,
		libCOL_requestHallCalls 				= 0x01,
		libCOL_requestSpecialInputs 			= 0x02,
		libCOL_requestAllInputsExceptCalls		= 0x03,
		libCOL_requestCallsAck 					= 0x04,
		libCOL_requestNone 						= 0xFF
	} callControllerCommand : 8;

	enum
	{
		/*
		 * libCOL_of_hallCallAcknowledgement
		 * libCOL_of_lowPriorityHallCallAcknowledgement
		 * libCOL_of_highPriorityHallCallAcknowledgement
		 */
		libCOL_hall_up_ack 						= 0x01,
		libCOL_hall_down_ack 					= 0x02,
		libCOL_hall_ack 						= 0x03,
		libCOL_hall_extraUp_ack 				= 0x04,
		libCOL_hall_extraDown_ack				= 0x05,
		libCOL_hall_extra_ack 					= 0x06
	} hallCallAck : 8;

	enum
	{
		/* libCOL_of_specialFunctionAcknowledgement */
		libCOL_special_requestFan1_ack 						= 0x01,
		libCOL_special_requestFan2_ack 						= 0x02,
		libCOL_special_requestLoadTime1_ack 				= 0x03,
		libCOL_special_requestLoadTime2_ack 				= 0x04,
		libCOL_special_keyLock1_ack 						= 0x05,
		libCOL_special_keyLock2_ack 						= 0x06,
		libCOL_special_keyLock3_ack 						= 0x07,
		libCOL_special_keyLock4_ack 						= 0x08,
		libCOL_special_requestDoorOpen_ack 					= 0x09,
		libCOL_special_requestDoorClose_ack 				= 0x0A,
		libCOL_special_fireRecall_ack 						= 0x0B,
		libCOL_special_fireService_ack 						= 0x0C,
		libCOL_special_hallCallDisable_ack 					= 0x0D,
		libCOL_special_attendantService_ack 				= 0x0E,
		libCOL_special_vipService_ack 						= 0x0F,
		libCOL_special_outOfOrder_ack 						= 0x10,
		libCOL_special_bedPassengerService_ack 				= 0x11,
		libCOL_special_specialService_ack 					= 0x12,
		libCOL_special_serviceRun_ack 						= 0x13,
		libCOL_special_dockingServiceEnable_ack 			= 0x14,
		libCOL_special_dockungServiceUp_ack 				= 0x15,
		libCOL_special_dockingServiceDown_ack 				= 0x16,
		libCOL_special_fireAlarm_ack 						= 0x17,
		libCOL_special_providePriority_ack 					= 0x18,
		libCOL_special_liftAttendantStartButton_ack 		= 0x19,
		libCOL_special_liftAttendantDriveThroughButton_ack	= 0x1A,
		libCOL_special_securityRun_ack 						= 0x1B,
		libCOL_special_secondCallPanel_ack 					= 0x1C,
		libCOL_special_doorEnable_ack 						= 0x1D,
		libCOL_special_callCancelButtonFireOperation_ack 	= 0x1E,
		libCOL_special_fireAlarmReset_ack 					= 0x1F,
		libCOL_special_bodyDetector_ack 					= 0x20,
		libCOL_special_earthquakeDetector_ack 				= 0x21,
		libCOL_special_cleaningTravel_ack 					= 0x22,
		libCOL_special_EmergencyAlarmReady_ack				= 0x23,
		libCOL_special_EmergencyAlarmGreen_ack				= 0x24,
		libCOL_special_EmergencyAlarmYellow_ack				= 0x25,
		libCOL_special_EmergencyAlarmButtonPressed_ack		= 0x26
		//libCOL_special_Reserved							= 0x27-0xFF
	} special : 8;

	enum
	{
		/* libCOL_of_liftLightsAcknowledgement */
		libCOL_liftLightsMainLight_On_ack					= 0x01,
		libCOL_liftLightMainLight_Off_ack					= 0x02,
		libCOL_liftLightSecondaryLight_On_ack				= 0x03,
		libCOL_liftLightSecondaryLight_Off_ack				= 0x04,
		libCOL_liftLightEmergencyLight_On_ack				= 0x05,
		libCOL_liftLightEmergencyLight_Off_ack				= 0x06,
		libCOL_liftLightAmbientLight_On_ack					= 0x07,
		libCOL_liftLightAmbientLight_Off_ack				= 0x08,
		libCOL_liftLightPanelLight_On_ack					= 0x09,
		libCOL_liftLightPanelLight_Off_ack					= 0x0A,
		libCOL_liftLightFloorLight_On_ack					= 0x0B,
		libCOL_liftLightFloorLight_Off_ack					= 0x0C,
		libCOL_liftLightShaftLight_On_ack					= 0x0D,
		libCOL_liftLightShaftLight_Off_ack					= 0x0E
		//libCOL_liftLightShaftLight_Reserved				= 0x0F-0xFF
	} liftLights : 8;

	enum
	{
		/* libCOL_of_hallLantern */
		libCOL_hallLantern_Up								= 0x01,
		libCOL_hallLantern_Down								= 0x02
	} hallLantern : 8;

	enum
	{
		/* libCOL_of_directionIndication */
		libCOL_directionIndication_Up						= 0x01,
		libCOL_directionIndication_Down						= 0x02,
		libCOL_directionIndication_MovingUp					= 0x11,
		libCOL_directionIndication_MovingDown				= 0x22
	} directionIndication : 8;

	enum
	{
		/* libCOL_of_specialIndication */
		libCOL_specialIndication_clear 						= 0x00,
		libCOL_specialIndication_noLoad 					= 0x01,
		libCOL_specialIndication_fullLoad 					= 0x02,
		libCOL_specialIndication_overLoad 					= 0x03,
		libCOL_specialIndication_fireRecall 				= 0x04,
		libCOL_specialIndication_fireService 				= 0x05,
		libCOL_specialIndication_helpIsComing 				= 0x06,
		libCOL_specialIndication_specialService 			= 0x07,
		libCOL_specialIndication_loadTime 					= 0x08,
		libCOL_specialIndication_occupied 					= 0x09,
		libCOL_specialIndication_outOfOrder 				= 0x0A,
		libCOL_specialIndication_closeDoor 					= 0x0B,
		libCOL_specialIndication_fireAlarm 					= 0x0C,
		libCOL_specialIndication_hallCallDisable 			= 0x0D,
		libCOL_specialIndication_travelToFireAlarmFloor 	= 0x0E,
		libCOL_specialIndication_travelToFireRecallFloor 	= 0x0F,
		libCOL_specialIndication_liftInMaintenance 			= 0x10,
		libCOL_specialIndication_vipTransport 				= 0x11,
		libCOL_specialIndication_guestCall 					= 0x12,
		libCOL_specialIndication_medicalEmergencyTransport	= 0x13,
		libCOL_specialIndication_chemicalTransport 			= 0x14,
		libCOL_specialIndication_bedTransport 				= 0x15,
		libCOL_specialIndication_testTravel 				= 0x16,
		libCOL_specialIndication_lowPriorityCallTransport 	= 0x17,
		libCOL_specialIndication_highPriorityCallTransport 	= 0x18,
		libCOL_specialIndication_stepWarningIndication 		= 0x19,
		libCOL_specialIndication_liftAttendantService 		= 0x1A,
		libCOL_specialIndication_rescueOperation 			= 0x1B,
		libCOL_specialIndication_emergencyPowerOperation 	= 0x1C,
		libCOL_specialIndication_personTrapped 				= 0x1D,
		libCOL_specialIndication_liftIsTravelling 			= 0x1E,
		libCOL_specialIndication_Userdef1 					= 0x1F, //PleaseWait
		libCOL_specialIndication_Userdef2 					= 0x20, //PleaseSpeak
		libCOL_specialIndication_Userdef3 					= 0x21, //WaitSpeak
		libCOL_specialIndication_Userdef4 					= 0x22, //EmergencyLight
		libCOL_specialIndication_Userdef5 					= 0x23, //OpenDoor
		libCOL_specialIndication_Userdef6 					= 0x24, //SmokingProhibited
		libCOL_specialIndication_Userdef7 					= 0x25,
		libCOL_specialIndication_Userdef8 					= 0x26,
		libCOL_specialIndication_Userdef9 					= 0x27,
		libCOL_specialIndication_Userdef10 					= 0x28,
		libCOL_specialIndication_Userdef11 					= 0x29
		//libCOL_specialIndication_Reserved					= 0x2A-0xFF
	} specialIndication : 8;

	enum
	{
		libCOL_arrivalIndication_Up 						= 0x01,
		libCOL_arrivalIndication_Down 						= 0x02,
		libCOL_arrivalIndication_NoDirection 				= 0x03
	} arrivalIndication: 8;

	union
	{
		uint8_t floorNumber;
		enum
		{
			/* libCOL_of_vocalFloorsAnnouncement */
			libCOL_switchOffFloorAnnouncement	= 0x00,
			libCOL_announceCurrentFloor 		= 0xFF
		} special : 8;
	} vocalFloorAnnouncement;

	enum
	{
		/* libCOL_of_vocalUserMessage */
		libCOL_switchOffAnnouncements 	= 0x00,
		libCOL_doorOpening 				= 0x01,
		libCOL_doorClosing 				= 0x02,
		libCOL_liftGoingUp 				= 0x03,
		libCOL_liftGoingDown 			= 0x04,
		libCOL_liftIsReserved 			= 0x05,
		libCOL_liftIsAvailable 			= 0x06,
		libCOL_liftOverload 			= 0x07,
		libCOL_liftOutOutOrder 			= 0x08,
		libCOL_liftInMaintenance 		= 0x09,
		libCOL_liftInEmergencyOperation	= 0x0A,
		libCOL_liftOnFiremenService 	= 0x0B,
		libCOL_stayAwayFromDoors 		= 0x0C,
		libCOL_levelAccessProtected 	= 0x0D,
		libCOL_mindTheStep 				= 0x0E,
		libCOL_leaveTheCar 				= 0x0F,
		libCOL_selectDestination 		= 0x10,
		libCOL_doNotUseThisLift 		= 0x11,
		libCOL_waitForRescueService 	= 0x12,
		libCOL_useEmergencyPhone 		= 0x13,
		libCOL_emergencyCallInProgress 	= 0x14,
		libCOL_emergencyCallEstablished	= 0x15,
		//libCOL_Reserved				= 0x16-0xFE,
		libCOL_stopCurrentAnnouncement 	= 0xFF
	} vocalUserMessage : 8;

	enum
	{
		/* libCOL_of_musicPlayback */
		libCOL_switchOffMusic	= 0x00,
		//libCOL_PlayTitle		= 0x01-0xFA
		libCOL_pauseMusic 		= 0xFB,
		libCOL_resumeMusic 		= 0xFC,
		libCOL_reservedMusic1	= 0xFD,
		libCOL_reservedMusic2 	= 0xFF
	} musicPlayback : 8;

	enum
	{
		/* libCOL_of_miscellaneousOutputs */
		libCOL_miscellaneousOutputsHallCallEnable	= 0x01,
		libCOL_miscellaneousOutputsLiftOperational	= 0x02,
		libCOL_miscellaneousOutputsLiftFault		= 0x03,
		libCOL_miscellaneousOutputsLiftBlocked		= 0x04,
		libCOL_miscellaneousOutputsAlarmButtonFilter	= 0x05,
		libCOL_miscellaneousOutputsCarBuzzer		= 0x06,
		libCOL_miscellaneousOutputsButtonSelfPressThroughMagneticCoil	= 0x07,
		libCOL_miscellaneousOutputsButtonSelfPressThroughMagneticCoilWithoutIOFeedback	= 0x08
		//libCOL_miscellaneousOutputsCarBuzzer		= 0x09-0xFF,
	} miscellaneousOutputs : 8;

	enum
	{
		/* libCOL_of_singleFaultIndication */
		libCOL_singleFaultIndicationDoorFault				= 0x01,
		libCOL_singleFaultIndicationDriveUnitFault			= 0x02,
		libCOL_singleFaultIndicationLoadMeasuringFault		= 0x03,
		libCOL_singleFaultIndicationPositionUnitFault		= 0x04,
		libCOL_singleFaultIndicationEmergencyCallUnitFault	= 0x05,
		libCOL_singleFaultIndicationUnintendedCarMovement	= 0x06,
		libCOL_singleFaultIndicationLightPowerSupplyFailure	= 0x07,
		libCOL_singleFaultIndicationCarLightFault			= 0x08,
		libCOL_singleFaultIndicationLightBarrierUnitFault	= 0x09,
		libCOL_singleFaultIndicationDoorOpenButtonFault		= 0x0A,
		libCOL_singleFaultIndicationStoppingAccuracyFault	= 0x0B,
		libCOL_singleFaultIndicationUnintendedSafetyContactDoorFault	= 0x0C,
		libCOL_singleFaultIndicationSafetyCircuitBypassFault			= 0x0D,
		libCOL_singleFaultIndicationPowerSupplyFailure		= 0x0E
	} singleFaultIndication : 8;

} libCOL_outputSubFunction_t;

typedef enum
{
	noAction 		= 0x00, //default
	continuously	= 0x01,
	pulsed 			= 0x02, //single
	flashing 		= 0x03, //blinking
	colored 		= 0x04, //highlighted
	volume 			= 0x05, //sound
	scroll 			= 0x06
} vo_property;

typedef enum
{
	pulse_ms500 	= 0x00,
	pulse_ms1000 	= 0x01,
	pulse_ms1500 	= 0x02,
	pulse_ms2000 	= 0x03,
	pulse_ms3000 	= 0x04,
	pulse_ms5000 	= 0x05,
	pulse_ms10000	= 0x06,
	pulse_ms15000	= 0x07
} vo_pulse;

typedef enum
{
	flash_ms100 	= 0x00, //10 Hz
	flash_ms133 	= 0x01, //7.5 Hz
	flash_ms200 	= 0x02, //5 Hz
	flash_ms500 	= 0x03, //2 Hz
	flash_ms666 	= 0x04, //1.5 Hz
	flash_ms1000	= 0x05, //1 Hz
	flash_ms2000 	= 0x06, //0.5 Hz
	flash_ms4000 	= 0x07 //0.25 Hz
} vo_flash;

typedef enum
{
	 white 		= 0x00,
	 yellow		= 0x01,
	 green 		= 0x03,
	 red 		= 0x05,
	 blue 		= 0x07
 } vo_color;

 typedef  enum
 {
	 minimum	= 0x00,
	 vary1 		= 0x01,
	 vary2 		= 0x02,
	 vary3 		= 0x03,
	 vary4 		= 0x04,
	 vary5 		= 0x05,
	 vary6 		= 0x06,
	 maximum 	= 0x07
 } vo_volume;

 typedef enum
 {
	 automatic	= 0x00,
	 line1 		= 0x01,
	 line2 		= 0x02,
	 line3 		= 0x03,
	 line4 		= 0x04,
	 line5 		= 0x05,
	 line6 		= 0x06,
	 line7 		= 0x07
 } vo_scroll;

typedef union libCOL_outputFunctionData_tag
{
	uint8_t raw;
	struct
	{
		uint8_t status : 1;		// BIT0
		uint8_t property : 3;	// BIT1..3
		uint8_t parameter: 3;	// BIT4..6
		uint8_t predicate : 1;	// BIT7
	} generic;
} libCOL_outputFunctionData_t;

typedef libCOL_Lift_t libCOL_outputLift_t;
typedef libCOL_Door_t libCOL_outputDoor_t;

typedef struct libCOL_output_tag
{
	libCOL_outputBasicFunction_t basicfunction : 8;
	libCOL_outputSubFunction_t subFunction;
	libCOL_Lift_t lift;
	uint8_t floor;
	libCOL_Door_t door;
	libCOL_outputFunctionData_t functionData;
} libCOL_output_t;

typedef struct libCOL_numbered_output_tag
{
	libCOL_output_t output;
	uint8_t number;
} libCOL_numbered_output_t;

typedef union libCOL_outputParameter1_tag
{
	uint32_t raw;
	struct
	{
		struct
		{
			bool enable 		: 1;
			uint8_t reserved	: 7;
		} enable;
		uint8_t error			: 8;
		uint8_t reserved 		: 8;
		libCOL_outputFunctionData_t defaultData;
	} parameter;
} libCOL_outputParameter1_t;

typedef union libCOL_outputParameter2_tag
{
	uint32_t raw;
	struct
	{
		uint8_t reserved 	: 8;
		uint8_t limitation	: 8;
		uint8_t reception 	: 8;
		uint8_t impulse 	: 8;
	} parameter;
} libCOL_outputParameter2_t;

typedef union libCOL_outputParameter3_tag
{
	uint32_t raw;
	struct
	{
		uint8_t reserved 		: 8;
		struct
		{
			uint8_t reserved	: 7;
			bool polarity 		: 1;
		} polarity;
		uint16_t reserved2 		: 16;
	} parameter;
} libCOL_outputParameter3_t;

/* ------------------------------------------------------------------------------------ */
/* CiA 417 Object 0x6200 end */
/* ------------------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif

#endif /* CIA417_LIFTTYPES_H_ */
