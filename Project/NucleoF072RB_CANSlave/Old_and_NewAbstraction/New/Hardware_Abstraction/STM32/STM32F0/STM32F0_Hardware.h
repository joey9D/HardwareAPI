#ifndef STM32F0_HARDWARE_H
#define STM32F0_HARDWARE_H

#include "Hardware_Interface.h"
#include "stm32f0xx_hal.h"
#include "STM32F0_Pins_config.h"
#include "CO_app_STM32.h"
class STM32F0_Hardware : public HardwareInterface {

public:
// Core System
void Clock_Init() override;                     ///< Initialize the system clock
void Delay(uint32_t ms) override;               ///< Delay in milliseconds
uint32_t GetTick() override;                    ///< Get system tick count

// GPIO
void GPIO_SetMode(void* port, uint8_t pin, GPIO_Mode mode) override; ///< Configure GPIO pin mode
bool GPIO_Read(void* port, uint16_t pin) override;                    ///< Read GPIO pin state
void GPIO_Write(void* port, uint8_t pin, GPIO_State state) override; ///< Write GPIO pin state
void setpinDirection(int clamp, bool output) override;
bool GPIOPinInput(int clamp) override;
void GPIOPinOutput(int clamp, bool state) override;
void GreenLed(bool state) override;
void RedLed() override;

// CAN
void CAN_Init(uint8_t bus, uint32_t baudrate) override;                ///< Initialize CAN bus
void CAN_Send(uint8_t bus, uint32_t id, uint8_t* data, uint8_t len) override; ///< Send CAN message
bool CAN_Receive(uint8_t bus, uint32_t& id, uint8_t* buffer, uint8_t& len) override; ///< Receive CAN message
void CAN_ConfigFilter(uint8_t bus, uint32_t id, uint32_t mask) override; ///< Configure CAN filter;
void errorHandler(uint32_t error) override; ///< Error handler

// TFT/Display
void TFT_Init(uint16_t width, uint16_t height) override;               ///< Initialize TFT display
void TFT_DrawPixel(uint16_t x, uint16_t y, uint16_t color) override;   ///< Draw a pixel on TFT
void TFT_FillScreen(uint16_t color) override;                          ///< Fill the screen with a color
bool TFT_TouchGetXY(uint16_t& x, uint16_t& y) override;                ///< Get touch coordinates

// Wireless (WB/WL)
#ifdef ENABLE_WIRELESS
void BLE_Init() override;                                              ///< Initialize BLE
void LoRa_Send(uint8_t* data, uint8_t len) override;                   ///< Send LoRa message
#endif

// Advanced Peripherals
void ADC_Start(uint8_t channel) override;                              ///< Start ADC conversion
uint16_t ADC_Read(uint8_t channel) override;                           ///< Read ADC value
void PWM_Set(uint8_t timer, uint8_t channel, uint16_t value) override; ///< Set PWM value

// Multi-core (H7/MP)
void M4_Core_Start(void (*func)(void)) override;                       ///< Start M4 core
void A7_Core_Init() override;                                          ///< Initialize A7 core (Linux)

// Counters
uint32_t gpioReadCounter = 0;  ///< Counter for GPIO_Read calls
uint32_t gpioWriteCounter = 0; ///< Counter for GPIO_Write calls

// Timer
void Timer_Base_Start_IT(void* htim) override; ///< Start timer with interrupt

// NVIC
void System_Reset() ; ///< Reset the system

private:
    CANopenNodeSTM32 _canOpenNodeParameters;



};

#endif
