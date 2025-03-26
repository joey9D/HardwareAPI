/*
 * iCanOpenNode.h
 *
 *  Created on: Sep 20, 2024
 *      Author: michael.grathwohl
 */

#ifndef ICANOPENNODE_H_
#define ICANOPENNODE_H_

#include <cstdint>

class iCanOpenNode
{
public:
	iCanOpenNode() = default;
	virtual ~iCanOpenNode() = default;

	/* This function will initialize the required CANOpen Stack objects, allocate the memory and prepare stack for communication reset*/
	virtual int canopen_app_init(void* CanOpenDesc) = 0;
	/* This function will reset the CAN communication periperhal and also the CANOpen stack variables */
	virtual uint32_t canopen_app_resetCommunication() = 0;
	/* This function will check the input buffers and any outstanding tasks that are not time critical, this function should be called regurarly from your code (i.e from your while(1))*/
	virtual uint8_t canopen_app_process() = 0;
	/* Thread function executes in constant intervals, this function can be called from FreeRTOS tasks or Timers ********/
	virtual void canopen_app_interrupt(void) = 0;

protected:


private:

};


#include "../basic/Timer.h"
#include "CANopen.h"

typedef struct {
	/*
	 * This is the Node ID that you ask the CANOpen stack to assign to your device, although it might not always
	 * be the final NodeID, after calling canopen_app_init() you should check ActiveNodeID of CANopenNodeSTM32 structure for assigned Node ID.
	 */
    uint8_t desiredNodeID;
    /*
     * Assigned Node ID
     */
    uint8_t activeNodeID;
    /*
     * This is the baudrate you've set in your CubeMX Configuration
     */
    uint16_t baudrate;
    /*
     * Pass in the timer that is going to be used for generating 1ms interrupt for tmrThread function,
	 * please note that CANOpenSTM32 Library will override HAL_TIM_PeriodElapsedCallback function,
	 * if you also need this function in your codes, please take required steps
	 */
    TIM_HandleTypeDef* timerHandle;
    /*
     * After this time the timerHandle Interrupt will be called.
     */
    uint32_t timerCall_in_us;

    /*
     * Pass in the CAN Handle to this function and it will be used for all CAN Communications. It can be FDCan or CAN
	 * and CANOpenSTM32 Driver will take of care of handling that
	 */
#ifdef CO_STM32_FDCAN_Driver
    FDCAN_HandleTypeDef* CANHandle;
#else
    CAN_HandleTypeDef* CANHandle;
#endif
    /*
     * Pass in the function that initialize the CAN peripheral, usually MX_CAN_Init
     */
    void (*HWInitFunction)(uint16_t baud);

    uint8_t outStatusLEDGreen; // This will be updated by the stack - Use them for the LED management
    uint8_t outStatusLEDRed;   // This will be updated by the stack - Use them for the LED management
    CO_t* canOpenStack;

} CANopenNodeSTM32_t;

class CanOpenNodeSTM32 : iCanOpenNode
{
public:
	CanOpenNodeSTM32() = default;
	virtual ~CanOpenNodeSTM32() = default;

	/* This function will initialize the required CANOpen Stack objects, allocate the memory and prepare stack for communication reset*/
	virtual int canopen_app_init(void* CanOpenDesc);
	/* This function will reset the CAN communication periperhal and also the CANOpen stack variables */
	virtual uint32_t canopen_app_resetCommunication();
	/* This function will check the input buffers and any outstanding tasks that are not time critical, this function should be called regurarly from your code (i.e from your while(1))*/
	virtual uint8_t canopen_app_process();
	/* Thread function executes in constant intervals, this function can be called from FreeRTOS tasks or Timers ********/
	virtual void canopen_app_interrupt(void);

private:
	Timer _diffTimer;
	CANopenNodeSTM32_t *canopenNodeSTM32 = nullptr;
	CO_t* CO = nullptr;

};

#endif /* ICANOPENNODE_H_ */
