#include "../CANHardwareInterface.h"

#include "../../Drivers/STM32F0xx_HAL_Driver/Inc/stm32f0xx_hal.h"

#include "STM32CANHardware.h"

    

//void CAN_Init() {
    // Example CAN initialization logic
//    CAN_FilterTypeDef sFilterConfig = {0};
//    sFilterConfig.FilterBank = 0;
//    sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
//    sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
//    sFilterConfig.FilterIdHigh = 0x0000;
//    sFilterConfig.FilterIdLow = 0x0000;
//    sFilterConfig.FilterMaskIdHigh = 0x0000;
//    sFilterConfig.FilterMaskIdLow = 0x0000;
//    sFilterConfig.FilterFIFOAssignment = CAN_RX_FIFO0;
//    sFilterConfig.FilterActivation = ENABLE;

//    if (HAL_CAN_ConfigFilter(STM32HALManager::GetInstance().GetCANHandle(), &sFilterConfig) != HAL_OK) {
//        STM32HALManager::Error_Handler();
//    }
//}

/*void STM32CANHardware::CAN_Start() {
    if (HAL_CAN_Start(STM32HALManager::GetInstance().GetCANHandle()) != HAL_OK) {
        STM32HALManager::Error_Handler();
    }
}*/

/*void STM32CANHardware::CAN_Transmit(const char* data, int length) {
    CAN_TxHeaderTypeDef txHeader = {0};
    uint32_t txMailbox;
    uint8_t txData[8] = {0};

    txHeader.DLC = length;
    txHeader.IDE = CAN_ID_EXT;
    txHeader.RTR = CAN_RTR_DATA;

    for (int i = 0; i < length && i < 8; i++) {
        txData[i] = data[i];
    }

    if (HAL_CAN_AddTxMessage(STM32HALManager::GetInstance().GetCANHandle(), &txHeader, txData, &txMailbox) != HAL_OK) {
        STM32HALManager::Error_Handler();
    }
}

void STM32CANHardware::CAN_Receive(char* buffer, int length) {
    CAN_RxHeaderTypeDef rxHeader = {0};
    uint8_t rxData[8] = {0};

    if (HAL_CAN_GetRxMessage(STM32HALManager::GetInstance().GetCANHandle(), CAN_RX_FIFO0, &rxHeader, rxData) == HAL_OK) {
        for (int i = 0; i < rxHeader.DLC && i < length; i++) {
            buffer[i] = rxData[i];
        }
    } else {
        STM32HALManager::Error_Handler();
    }
}*/

bool GPIO_Read(int pin) {
    return HAL_GPIO_ReadPin(GPIOA, pin) == GPIO_PIN_SET;
}

void GPIO_Write(int pin, bool value) {
    HAL_GPIO_WritePin(GPIOA, pin, value ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

unsigned long GetTick() {
    return HAL_GetTick();
}
