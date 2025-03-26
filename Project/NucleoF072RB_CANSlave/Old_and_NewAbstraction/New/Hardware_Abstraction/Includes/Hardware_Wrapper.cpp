#include "Hardware_Abstraction_C.h"
#include "Hardware_Interface.h"
#include "Hardware_Factory_STM32.h"

extern "C" {
    HardwareInstance CreateHardwareInstance() {
        return (HardwareInstance)HardwareFactory::Create();
    }

    // Core System
    void Hardware_Delay(HardwareInstance instance, uint32_t ms) {
        static_cast<HardwareInterface*>(instance)->Delay(ms);
    }

    uint32_t Hardware_GetTick(HardwareInstance instance) {
        return static_cast<HardwareInterface*>(instance)->GetTick();
    }

    // GPIO
    void Hardware_GPIO_SetMode(HardwareInstance instance, void* port, uint8_t pin, int mode) {
        static_cast<HardwareInterface*>(instance)->GPIO_SetMode(port, pin, static_cast<GPIO_Mode>(mode));
    }

    int Hardware_GPIO_Read(HardwareInstance instance, void* port, uint8_t pin) {
        return static_cast<HardwareInterface*>(instance)->GPIO_Read(port, pin) ? 1 : 0;
    }

    void Hardware_GPIO_Write(HardwareInstance instance, void* port, uint8_t pin, int state) {
        static_cast<HardwareInterface*>(instance)->GPIO_Write(port, pin, static_cast<GPIO_State>(state));
    }

    // CAN
    void Hardware_CAN_Init(HardwareInstance instance, uint8_t bus, uint32_t baudrate) {
        static_cast<HardwareInterface*>(instance)->CAN_Init(bus, baudrate);
    }

    void Hardware_CAN_Send(HardwareInstance instance, uint8_t bus, uint32_t id, uint8_t* data, uint8_t len) {
        static_cast<HardwareInterface*>(instance)->CAN_Send(bus, id, data, len);
    }

    int Hardware_CAN_Receive(HardwareInstance instance, uint8_t bus, uint32_t* id, uint8_t* buffer, uint8_t* len) {
        return static_cast<HardwareInterface*>(instance)->CAN_Receive(bus, *id, buffer, *len) ? 1 : 0;
    }

    // Timer
    void Hardware_Timer_Base_Start_IT(HardwareInstance instance, TIM_HandleTypeDef* htim) {
        static_cast<HardwareInterface*>(instance)->Timer_Base_Start_IT(htim);
    }

    // NVIC
    void System_Reset(HardwareInstance instance) {
        static_cast<HardwareInterface*>(instance)->System_Reset();
    }
}
