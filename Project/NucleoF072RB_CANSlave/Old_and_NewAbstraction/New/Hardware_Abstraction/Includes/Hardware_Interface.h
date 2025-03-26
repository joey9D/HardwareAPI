#ifndef HARDWARE_INTERFACE_H
#define HARDWARE_INTERFACE_H


#include <cstdint>

// Enums for GPIO modes and states
enum GPIO_Mode {
    GPIO_MODE_INPUT = 0,
    GPIO_MODE_OUTPUT = 1,
    GPIO_MODE_ALTERNATE = 2,
    GPIO_MODE_ANALOG = 3
};

enum GPIO_State {
    GPIO_LOW = 0,
    GPIO_HIGH = 1
};

enum HardwareError { HW_ERROR_NONE, HW_ERROR_CAN_BUS_OFF, HW_ERROR_CAN_PASSIVE };



class HardwareInterface {
public:
    // Core System
    virtual void Clock_Init() = 0;                      ///< Initialize the system clock
    virtual void Delay(uint32_t ms) = 0;               ///< Delay in milliseconds
    virtual uint32_t GetTick() = 0;                    ///< Get system tick count

    // GPIO
    virtual void GPIO_SetMode(void* port, uint8_t pin, GPIO_Mode mode) = 0; ///< Configure GPIO pin mode
    virtual bool GPIO_Read(void* port, uint16_t pin) = 0;                    ///< Read GPIO pin state
    virtual void GPIO_Write(void* port, uint8_t pin, GPIO_State state) = 0;
    virtual void setpinDirection(int clamp, bool output) =0;
    virtual bool GPIOPinInput(int clamp) =0;
    virtual void GPIOPinOutput(int clamp, bool state) =0;
    virtual void GreenLed(bool state)=0;
    virtual void RedLed()=0;

    // CAN
    virtual void CAN_Init(uint8_t bus, uint32_t baudrate) = 0;                ///< Initialize CAN bus
    virtual void CAN_Send(uint8_t bus, uint32_t id, uint8_t* data, uint8_t len) = 0; ///< Send CAN message
    virtual bool CAN_Receive(uint8_t bus, uint32_t& id, uint8_t* buffer, uint8_t& len) = 0; ///< Receive CAN message
    virtual void CAN_ConfigFilter(uint8_t bus, uint32_t id, uint32_t mask) = 0; ///< Configure CAN filter
    virtual void errorHandler(uint32_t error) = 0; ///< Error handler	



    // TFT/Display
    virtual void TFT_Init(uint16_t width, uint16_t height) = 0;               ///< Initialize TFT display
    virtual void TFT_DrawPixel(uint16_t x, uint16_t y, uint16_t color) = 0;   ///< Draw a pixel on TFT
    virtual void TFT_FillScreen(uint16_t color) = 0;                          ///< Fill the screen with a color
    virtual bool TFT_TouchGetXY(uint16_t& x, uint16_t& y) = 0;                ///< Get touch coordinates

    // Wireless (WB/WL)
    #ifdef ENABLE_WIRELESS
    virtual void BLE_Init() = 0;                                              ///< Initialize BLE
    virtual void LoRa_Send(uint8_t* data, uint8_t len) = 0;                   ///< Send LoRa message
    #endif

    // Advanced Peripherals
    virtual void ADC_Start(uint8_t channel) = 0;                              ///< Start ADC conversion
    virtual uint16_t ADC_Read(uint8_t channel) = 0;                           ///< Read ADC value
    virtual void PWM_Set(uint8_t timer, uint8_t channel, uint16_t value) = 0; ///< Set PWM value

    // Multi-core (H7/MP)
    virtual void M4_Core_Start(void (*func)(void)) = 0;                       ///< Start M4 core
    virtual void A7_Core_Init() = 0;                                          ///< Initialize A7 core (Linux)

    // Timer
    virtual void Timer_Base_Start_IT(void* htim) = 0; ///< Start timer with interrupt

    // NVIC
    virtual void System_Reset()=0; ///< Reset the system

    virtual ~HardwareInterface() = default;                                   ///< Virtual destructor for cleanup
};
#endif


