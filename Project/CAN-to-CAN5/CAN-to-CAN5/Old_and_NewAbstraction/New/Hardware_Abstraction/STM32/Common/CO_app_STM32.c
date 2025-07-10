/*
 * CANopen main program file.
 *
 * This file is a template for other microcontrollers.
 *
 * @file        main_generic.c
 * @author      Hamed Jafarzadeh 	2022
 * 				Janez Paternoster	2021
 * @copyright   2021 Janez Paternoster
 *
 * This file is part of CANopenNode, an opensource CANopen Stack.
 * Project home page is <https://github.com/CANopenNode/CANopenNode>.
 * For more information on CANopen see <http://www.can-cia.org/>.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "CO_app_STM32.h"
#include "CANopen.h"
#include "main.h"
#include <stdio.h>

//#include "../Hardware_Abstraction/STM32/STM32CANHardware.h"




// Global hardware abstraction instance
//extern STM32CANHardware hardware;


#include "CO_storageBlank.h"
#include "OD.h"

BootupNodeInfo bootupNodes[MAX_BOOTUP_NODES];
uint8_t bootupNodeCount = 0;
// It will be set by canopen_app_init and will be used across app to get access to CANOpen objects
CANopenNodeSTM32* canopenNodeSTM32;

/* Printf function of CanOpen app */
#ifdef LOG_CANNODE_STACK
#define log_printf(macropar_message, ...) printf(macropar_message, ##__VA_ARGS__)
#else
#define log_printf(...)
#endif

/* default values for CO_CANopenInit() */
#ifndef NMT_CONTROL
#define NMT_CONTROL CO_NMT_STARTUP_TO_OPERATIONAL | CO_NMT_ERR_ON_ERR_REG | CO_ERR_REG_GENERIC_ERR | CO_ERR_REG_COMMUNICATION
#endif
#define FIRST_HB_TIME        500
#define SDO_SRV_TIMEOUT_TIME 1000
#define SDO_CLI_TIMEOUT_TIME 500
#define SDO_CLI_BLOCK        false
#define OD_STATUS_BITS       NULL
#define MS_TO_US			 1000

// Global variables
CO_t* CO = NULL; /* CANopen object */
CO_ReturnError_t err;

// Local variables
static uint32_t timeDifference_us = 0;
static uint32_t time_old;

inline static uint8_t isTimeExpired()
{
	uint8_t ret = 0;

	/* get time difference since last function call */
	uint32_t time_current = HAL_GetTick();
	if((time_current - time_old) > 0)
	{// Make sure more than 1ms elapsed
		timeDifference_us = (time_current - time_old) * MS_TO_US;
		time_old = time_current;
		ret = 1;
	}

	return ret;
}

inline static uint32_t getTimeExpiredDiff()
{
	return timeDifference_us;
}

/* This function will basically setup the CANopen node */
int canopen_app_init(CANopenNodeSTM32* _canopenNodeSTM32)
{
    // Keep a copy global reference of canOpenSTM32 Object
    canopenNodeSTM32 = _canopenNodeSTM32;

#if (CO_CONFIG_STORAGE) & CO_CONFIG_STORAGE_ENABLE
    static CO_storage_t storage;
    static CO_storage_entry_t storageEntries[] = {{.addr = &OD_PERSIST_COMM,
                                                   .len = sizeof(OD_PERSIST_COMM),
                                                   .subIndexOD = 2,
                                                   .attr = CO_storage_cmd | CO_storage_restore,
                                                   .addrNV = NULL}};
    uint8_t storageEntriesCount = sizeof(storageEntries) / sizeof(storageEntries[0]);
    uint32_t storageInitError = 0;
#endif

    /* Allocate memory */
    CO_config_t* config_ptr = NULL;
#ifdef CO_MULTIPLE_OD
    /* example usage of CO_MULTIPLE_OD (but still single OD here) */
    CO_config_t co_config = {0};
    OD_INIT_CONFIG(co_config); /* helper macro from OD.h */
    co_config.CNT_LEDS = 1;
    co_config.CNT_LSS_SLV = 1;
    config_ptr = &co_config;
#endif /* CO_MULTIPLE_OD */

    uint32_t heapMemoryUsed;
    CO = CO_new(config_ptr, &heapMemoryUsed);
    if (CO == NULL)
    {
        log_printf("Error: Can't allocate memory\n");
        return CO_ERROR_OUT_OF_MEMORY;
    }
    else
    {
        log_printf("Allocated %u bytes for CANopen objects\n", (unsigned int)heapMemoryUsed);
    }

    canopenNodeSTM32->canOpenStack = CO;

#if (CO_CONFIG_STORAGE) & CO_CONFIG_STORAGE_ENABLE
    err = CO_storageBlank_init(&storage, CO->CANmodule, OD_ENTRY_H1010_storeParameters,
                               OD_ENTRY_H1011_restoreDefaultParameters, storageEntries, storageEntriesCount,
                               &storageInitError);

    if (err != CO_ERROR_NO && err != CO_ERROR_DATA_CORRUPT)
    {
        log_printf("Error: Storage %d\n", storageInitError);
        return 2;
    }
#endif

    return canopen_app_resetCommunication();
}

uint32_t canopen_app_resetCommunication()
{
    /* CANopen communication reset - initialize CANopen objects *******************/
    log_printf("CANopenNode - Reset communication...\n");

    /* Wait rt_thread. */
    CO->CANmodule->CANnormal = false;

    /* Enter CAN configuration. */
    CO_CANsetConfigurationMode((void*)canopenNodeSTM32);
    CO_CANmodule_disable(CO->CANmodule);

    /* initialize CANopen */
    err = CO_CANinit(CO, canopenNodeSTM32, 0); // Bitrate for STM32 microcontroller is being set in MXCube Settings
    if (err != CO_ERROR_NO)
    {
        log_printf("Error: CAN initialization failed: %d\n", err);
        return CO_ERROR_INVALID_STATE;
    }

#if (CO_CONFIG_LSS) & CO_CONFIG_LSS_SLAVE
    CO_LSS_address_t lssAddress = {.identity = {.vendorID = OD_PERSIST_COMM.x1018_identity.vendor_ID,
                                                .productCode = OD_PERSIST_COMM.x1018_identity.productCode,
                                                .revisionNumber = OD_PERSIST_COMM.x1018_identity.revisionNumber,
                                                .serialNumber = OD_PERSIST_COMM.x1018_identity.serialNumber}};
    err = CO_LSSinit(CO, &lssAddress, &canopenNodeSTM32->desiredNodeID, &canopenNodeSTM32->baudrate);
    if (err != CO_ERROR_NO)
    {
        log_printf("Error: LSS slave initialization failed: %d\n", err);
        return CO_ERROR_INVALID_STATE;
    }
#elif (CO_CONFIG_LSS) & CO_CONFIG_LSS_MASTER
/*
	err = CO_LSSmaster_init(CO->LSSmaster, 1000, CO->CANmodule,  CO_GET_CO(RX_IDX_LSS_MST), CO_CAN_ID_LSS_SLV, CO->CANmodule, CO_GET_CO(TX_IDX_LSS_MST), CO_CAN_ID_LSS_MST);
	if (err != CO_ERROR_NO)
	{
		log_printf("Error: LSS master initialization failed: %d\n", err);
		return 2;
	}
*/
#endif

    canopenNodeSTM32->activeNodeID = canopenNodeSTM32->desiredNodeID;
    uint32_t errInfo = 0;

    err = CO_CANopenInit(CO,                   /* CANopen object */
                         NULL,                 /* alternate NMT */
                         NULL,                 /* alternate em */
                         OD,                   /* Object dictionary */
                         OD_STATUS_BITS,       /* Optional OD_statusBits */
                         NMT_CONTROL,          /* CO_NMT_control_t */
                         FIRST_HB_TIME,        /* firstHBTime_ms */
                         SDO_SRV_TIMEOUT_TIME, /* SDOserverTimeoutTime_ms */
                         SDO_CLI_TIMEOUT_TIME, /* SDOclientTimeoutTime_ms */
                         SDO_CLI_BLOCK,        /* SDOclientBlockTransfer */
                         canopenNodeSTM32->activeNodeID, &errInfo);
    if (err != CO_ERROR_NO && err != CO_ERROR_NODE_ID_UNCONFIGURED_LSS)
    {
        if (err == CO_ERROR_OD_PARAMETERS)
        {
            log_printf("Error: Object Dictionary entry 0x%X\n", errInfo);
        }
        else
        {
            log_printf("Error: CANopen initialization failed: %d\n", err);
        }
        return CO_ERROR_NODE_ID_UNCONFIGURED_LSS;
    }
    #ifdef CANOPEN_MASTER
    /* Here some software filters for bootup messages are registered and used as the CANopenstack uses Software filters
     filters for all messages with DLC = 1 done and then an array is initialized to hold these messages
    */

    canextrafilters(); // Add extra filters for bootup messages which are not part of the standard CANopen stack
    #endif
    err = CO_CANopenInitPDO(CO, CO->em, OD, canopenNodeSTM32->activeNodeID, &errInfo);
    if (err != CO_ERROR_NO)
    {
        if (err == CO_ERROR_OD_PARAMETERS)
        {
            log_printf("Error: Object Dictionary entry 0x%X\n", errInfo);
        }
        else
        {
            log_printf("Error: PDO initialization failed: %d\n", err);
        }
        return CO_ERROR_INVALID_STATE;
    }

    /* Configure Timer interrupt function for execution every 1 millisecond */
    HAL_TIM_Base_Start_IT(canopenNodeSTM32->timerHandle); //1ms interrupt // 

    /* Configure CAN transmit and receive interrupt */
    /******************************************************************************* */





    /*********************************************************************************** */
    /* Configure CANopen callbacks, etc */
    if (!CO->nodeIdUnconfigured)
    {
#if (CO_CONFIG_STORAGE) & CO_CONFIG_STORAGE_ENABLE
        if (storageInitError != 0)
        {
            CO_errorReport(CO->em, CO_EM_NON_VOLATILE_MEMORY, CO_EMC_HARDWARE, storageInitError);
        }
#endif
    }
    else
    {
        log_printf("CANopenNode - Node-id not initialized\n");
    }

    /* start CAN */
    CO_CANsetNormalMode(CO->CANmodule);

    log_printf("CANopenNode - Running...\n");
    fflush(stdout);
    time_old = HAL_GetTick();
    return CO_ERROR_NO;
}

uint8_t canopen_app_process()
{
    /* loop for normal program execution ******************************************/
	uint8_t executed = 0;

    if(isTimeExpired())
    { // Make sure more than 1ms elapsed
        /* CANopen process */
        CO_NMT_reset_cmd_t reset_status = CO_process(CO, false, getTimeExpiredDiff(), NULL);
        canopenNodeSTM32->outStatusLEDRed = CO_LED_RED(CO->LEDs, CO_LED_CANopen);
        canopenNodeSTM32->outStatusLEDGreen = CO_LED_GREEN(CO->LEDs, CO_LED_CANopen);
        executed = 1;

        if(reset_status == CO_RESET_COMM)
        {
            /* delete objects from memory */
            CO_CANsetConfigurationMode((void*)canopenNodeSTM32);
            CO_delete(CO);
            log_printf("CANopenNode Reset Communication request\n");
            canopen_app_resetCommunication(); // Reset Communication routine
        }
        else if(reset_status == CO_RESET_APP)
        {
            log_printf("CANopenNode Device Reset\n");
            HAL_NVIC_SystemReset(); // Reset the STM32 Microcontroller
        }
    }
    return executed;
}

/* Thread function executes in constant intervals, this function can be called from FreeRTOS tasks or Timers ********/
void 
canopen_app_interrupt(void)
{
    CO_LOCK_OD(CO->CANmodule);
    if(!CO->nodeIdUnconfigured && CO->CANmodule->CANnormal)
    {
        bool_t syncWas = false;
#if (CO_CONFIG_SYNC) & CO_CONFIG_SYNC_ENABLE
        syncWas = CO_process_SYNC(CO, canopenNodeSTM32->timerCall_in_us, NULL);
#endif
#if (CO_CONFIG_PDO) & CO_CONFIG_RPDO_ENABLE
        CO_process_RPDO(CO, syncWas, canopenNodeSTM32->timerCall_in_us, NULL);
#endif
#if (CO_CONFIG_PDO) & CO_CONFIG_TPDO_ENABLE
        CO_process_TPDO(CO, syncWas, canopenNodeSTM32->timerCall_in_us, NULL);
#endif

        /* Further I/O or nonblocking application code may go here. */
    }
    CO_UNLOCK_OD(CO->CANmodule);
}


void canextrafilters()
{

#define BOOTUP_FILTER_IDX 13 // Example: set to first free index after all modules
static uint8_t bootupFilterDummyObject;
CO_CANrxBufferInit(
    CO->CANmodule,
    BOOTUP_FILTER_IDX, // Index for the bootup filter , found out by trial and error , stack has maximum 14 filters here for one FIFO.
    0x700, // CAN ID for bootup messages (0x700 + node ID)
    0x780, // CAN ID for bootup messages (0x780 + node ID)
    false,
	&bootupFilterDummyObject, // Dummy object, not used
    bootupCallback // Callback function for bootup messages
);

}

// Finds a free subindex in OD 0x1016 for storing node IDs and heartbeat times

static uint8_t find_free_1016_subindex(CO_t *CO)
{
    if (CO == NULL || OD == NULL) return 0;

    OD_entry_t *OD_1016 = OD_find(OD, 0x1016); // Find the OD entry for 0x1016 where consumer nodes are stored
    if (OD_1016 == NULL) return 0; 

    uint8_t max = OD_1016->subEntriesCount - 1; // Subindex 0 is reserved, so we start from 1 , calculates available subindex count
    if (max > 127) max = 127; // Safety: limit to reasonable value

    for (uint8_t i = 1; i <= max; ++i) {
        uint32_t val = 0; // Initialize value to zero
        if (OD_get_u32(OD_1016, i, &val, true) == ODR_OK) // Read the value at subindex i , if the read returns OK
        {
             uint8_t nodeId = (val >> 16) & 0xFF; // Extract node ID from the value
            if (nodeId == 0) return i; // Free slot if nodeID is 0 , then we return the subindex 
        }
    }
    return 0; // No free slot
}

void bootupCallback(void *object, void *msg)
{
CO_CANrxMsg_t *rxMsg = (CO_CANrxMsg_t *)msg; // Cast the message to CO_CANrxMsg_t type , this variable will receive the message
uint16_t canId = CO_CANrxMsg_readIdent(rxMsg); // Read the CAN ID from the message
uint8_t nodeId = canId & 0x7F;// Extract the node ID from the CAN ID (assuming 7-bit node ID)
uint8_t *data = CO_CANrxMsg_readData(rxMsg); // Read the data from the message
uint8_t dlc = CO_CANrxMsg_readDLC(rxMsg); // Read the Data Length Code.

if (dlc == 1) // Check if the DLC is 1, which is standard for bootup messages or Heartbeat 
	{
		// Check if node is already in the array
		for (uint8_t i = 0; i < bootupNodeCount; ++i)
		{
			if (bootupNodes[i].nodeId == nodeId) //If nodeId matches an existing node
			{
				bootupNodes[i].data = data[0]; // Update the data for the existing node
				return;
			}
		}
		// Add new node if space is available
		if (bootupNodeCount < MAX_BOOTUP_NODES) 
		{
			bootupNodes[bootupNodeCount].nodeId = nodeId;
			bootupNodes[bootupNodeCount].data = data[0];
			bootupNodes[bootupNodeCount].heartbeat_ms = 1500; // Default heartbeat
			bootupNodeCount++;
			writeto1016(nodeId); // Write to OD 0x1016 to monitor this node

		}
	}
}

void writeto1016(uint8_t nodeId)
{
	// --- Write to OD 0x1016 for heartbeat monitoring ---
				CO_t *CO = canopenNodeSTM32->canOpenStack; // Get your CO_t pointer
				uint8_t freeSubindex = find_free_1016_subindex(CO); // Find a free subindex in OD 0x1016
				if (freeSubindex) // If a free subindex is found
				{
					uint32_t val = ((uint32_t)nodeId << 16) | 1500; // 1500 ms heartbeat
					OD_entry_t *OD_1016 = OD_find(OD,0x1016);

					ODR_t odRet = OD_set_u32(OD_1016, freeSubindex, val, false);
					// This will call OD_write_1016, which sets up monitoring!
				}


}




