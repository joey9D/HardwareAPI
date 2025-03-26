/*
 * iCanOpenNode.cpp
 *
 *  Created on: Sep 20, 2024
 *      Author: michael.grathwohl
 */

#include "iCanOpenNode.h"
#include "OD.h"

/* Printf function of CanOpen app */
#ifdef LOG_CANNODE_STACK
#define log_printf(macropar_message, ...) printf(macropar_message, ##__VA_ARGS__)
#else
#define log_printf(...)
#endif

#define FIRST_HB_TIME        500
#define SDO_SRV_TIMEOUT_TIME 1000
#define SDO_CLI_TIMEOUT_TIME 500
#define SDO_CLI_BLOCK        false
#define OD_STATUS_BITS       NULL

int CanOpenNodeSTM32::canopen_app_init(void* CanOpenDesc)
{
    // Keep a copy global reference of canOpenSTM32 Object
    canopenNodeSTM32 = static_cast<CANopenNodeSTM32_t*>(CanOpenDesc);

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

    _diffTimer.startTime(1);

    return canopen_app_resetCommunication();
}

uint32_t CanOpenNodeSTM32::canopen_app_resetCommunication()
{
	CO_ReturnError_t err = CO_ERROR_NO;
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
                         static_cast<CO_NMT_control_t>(NMT_CONTROL),          /* CO_NMT_control_t */
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
    HAL_TIM_Base_Start_IT(canopenNodeSTM32->timerHandle); //1ms interrupt

    /* Configure CAN transmit and receive interrupt */

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
    //fflush(stdout);
    _diffTimer.resetTime();
    return CO_ERROR_NO;
}

uint8_t CanOpenNodeSTM32::canopen_app_process()
{
    /* loop for normal program execution ******************************************/
	uint8_t executed = 0;

    if(_diffTimer.isTimeExpired())
    { // Make sure more than 1ms elapsed
        /* CANopen process */
        CO_NMT_reset_cmd_t reset_status = CO_process(CO, false, _diffTimer.getExpiredDiffTime(), NULL);
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

void CanOpenNodeSTM32::canopen_app_interrupt(void)
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

