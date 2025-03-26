#ifndef HARDWARE_ABSTRACTION_C_H
#define HARDWARE_ABSTRACTION_C_H

#ifdef __cplusplus
extern "C" {
#endif

typedef void* HardwareInstance;

// Core System
HardwareInstance CreateHardwareInstance();
void Hardware_Delay(HardwareInstance instance, uint32_t ms);
uint32_t Hardware_GetTick(HardwareInstance instance);

// GPIO
void Hardware_GPIO_SetMode(HardwareInstance instance, void* port, uint8_t pin, int mode);
int Hardware_GPIO_Read(HardwareInstance instance, void* port, uint8_t pin);
void Hardware_GPIO_Write(HardwareInstance instance, void* port, uint8_t pin, int state);

// CAN (Add other peripherals as needed)
void Hardware_CAN_Init(HardwareInstance instance, uint8_t bus, uint32_t baudrate);
void Hardware_CAN_Send(HardwareInstance instance, uint8_t bus, uint32_t id, uint8_t* data, uint8_t len);
int Hardware_CAN_Receive(HardwareInstance instance, uint8_t bus, uint32_t* id, uint8_t* buffer, uint8_t* len);

// Timer
void Hardware_Timer_Base_Start_IT(HardwareInstance instance, TIM_HandleTypeDef* htim);

// NVIC
void System_Reset(HardwareInstance instance);

#ifdef __cplusplus
}
#endif

#endif // HARDWARE_ABSTRACTION_C_H
