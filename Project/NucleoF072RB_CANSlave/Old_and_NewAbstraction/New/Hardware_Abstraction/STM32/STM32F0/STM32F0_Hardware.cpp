#include "STM32F0_Hardware.h"
#include "stm32f0xx_hal.h"
#include "core_cm0.h"
#include "STM32F0_Pins_config.h"





// Clock
void STM32F0_Hardware::Clock_Init() {
    RCC_OscInitTypeDef osc = {0};
    osc.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    osc.HSIState = RCC_HSI_ON;
    osc.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    HAL_RCC_OscConfig(&osc);

    RCC_ClkInitTypeDef clk = {0};
    clk.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK;
    clk.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
    clk.AHBCLKDivider = RCC_SYSCLK_DIV1;
    HAL_RCC_ClockConfig(&clk, FLASH_LATENCY_0);
}

void STM32F0_Hardware::Delay(uint32_t ms) {
    HAL_Delay(ms);
}

uint32_t STM32F0_Hardware::GetTick() {
    return HAL_GetTick();
}
// GPIO
void STM32F0_Hardware::GPIO_SetMode(void* port, uint8_t pin, GPIO_Mode mode) {
    GPIO_InitTypeDef gpio = {0};
    gpio.Pin = 1 << pin;
    gpio.Mode = static_cast<uint32_t>(mode);
    HAL_GPIO_Init(reinterpret_cast<GPIO_TypeDef*>(port), &gpio);
}

bool STM32F0_Hardware::GPIO_Read(void* port, uint16_t pin) {
	// Increment the read counter
    return HAL_GPIO_ReadPin(reinterpret_cast<GPIO_TypeDef*>(port), pin);
}


void STM32F0_Hardware::GPIO_Write(void* port, uint8_t pin, GPIO_State state) {
    gpioWriteCounter++; // Increment the write counter
    HAL_GPIO_WritePin(reinterpret_cast<GPIO_TypeDef*>(port), pin, state == GPIO_HIGH ? GPIO_PIN_SET : GPIO_PIN_RESET);
}
void STM32F0_Hardware::GreenLed(bool state)
{//    GPIO_TypeDef *GPIOx = LED_GREEN_PORT;
//     uint16_t pin = LED_GREEN_PIN;
   
    HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin,state == GPIO_HIGH ? GPIO_PIN_SET : GPIO_PIN_RESET);

}
void  STM32F0_Hardware::RedLed() {


}
void STM32F0_Hardware::setpinDirection(int clamp, bool output)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    
    uint16_t pinHigh = pin_config::instance().getClampPin(clamp, true);
    uint16_t pinLow = pin_config::instance().getClampPin(clamp, false);
    GPIO_TypeDef *GPIOx = pin_config::instance().getClampGPIOPort(clamp);

    if (output) {
        GPIO_InitStruct.Pin = pinHigh;
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL; // Replace with appropriate value
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
        HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
        
        if (pin_config::instance().getClampHighCurrent(clamp)) {
            // Enable high drive strength if needed
            GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        } else {
            GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
        }
        HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
        
        // Set low pin as input
        GPIO_InitStruct.Pin = pinLow;
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        GPIO_InitStruct.Pull = GPIO_NOPULL; // Replace with appropriate value
        HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
    } else {
        // Set both pins as input
        GPIO_InitStruct.Pin = pinHigh;
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        GPIO_InitStruct.Pull = GPIO_NOPULL; // Replace with appropriate value
        HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
        
        GPIO_InitStruct.Pin = pinLow;
        GPIO_InitStruct.Pull = pin_config::instance().getClampPull(clamp);
        HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
    }
}

bool STM32F0_Hardware::GPIOPinInput(int clamp)
{
    uint16_t pinLow = pin_config::instance().getClampPin(clamp, false);
    GPIO_TypeDef *GPIOx = pin_config::instance().getClampGPIOPort(clamp);
    return !(HAL_GPIO_ReadPin(GPIOx, pinLow) == pin_config::instance().getClampInverted(clamp, false));
}

void STM32F0_Hardware::GPIOPinOutput(int clamp, bool state)
{
    uint16_t pinHigh = pin_config::instance().getClampPin(clamp, true);
    GPIO_TypeDef *GPIOx = pin_config::instance().getClampGPIOPort(clamp);
    HAL_GPIO_WritePin(GPIOx, pinHigh, (GPIO_PinState)(!(state == pin_config::instance().getClampInverted(clamp, true))));
}

// CAN
void STM32F0_Hardware::CAN_Init(uint8_t bus, uint32_t baudrate) {

}


void STM32F0_Hardware::CAN_Send(uint8_t bus, uint32_t id, uint8_t* data, uint8_t len) {
    // ...implementation...
}

bool STM32F0_Hardware::CAN_Receive(uint8_t bus, uint32_t& id, uint8_t* buffer, uint8_t& len) {
    // ...implementation...
    return false;
}

void STM32F0_Hardware::CAN_ConfigFilter(uint8_t bus, uint32_t id, uint32_t mask) {
    // ...implementation...
}

void STM32F0_Hardware::errorHandler(uint32_t error) {
    if(error != HAL_CAN_ERROR_NONE)
		{
			switch(error)
			{
			case HAL_CAN_ERROR_EWG:
			case HAL_CAN_ERROR_EPV:
			case HAL_CAN_ERROR_BOF:
			case HAL_CAN_ERROR_STF:
			case HAL_CAN_ERROR_FOR:
			case HAL_CAN_ERROR_ACK:
			case HAL_CAN_ERROR_BR:
			case HAL_CAN_ERROR_BD:
			case HAL_CAN_ERROR_CRC:
			case HAL_CAN_ERROR_RX_FOV0:
			case HAL_CAN_ERROR_RX_FOV1:
			case HAL_CAN_ERROR_TX_ALST0:
			case HAL_CAN_ERROR_TX_TERR0:
			case HAL_CAN_ERROR_TX_ALST1:
			case HAL_CAN_ERROR_TX_TERR1:
			case HAL_CAN_ERROR_TX_ALST2:
			case HAL_CAN_ERROR_TX_TERR2:
			case HAL_CAN_ERROR_TIMEOUT:
			case HAL_CAN_ERROR_NOT_INITIALIZED:
			case HAL_CAN_ERROR_NOT_READY:
			case HAL_CAN_ERROR_NOT_STARTED:
			case HAL_CAN_ERROR_PARAM:
			default:
				break;
			}

			//todo
			//canopen_app_resetCommunication();
		}
}

// TFT/Display
void STM32F0_Hardware::TFT_Init(uint16_t width, uint16_t height) {
    // ...implementation...
}

void STM32F0_Hardware::TFT_DrawPixel(uint16_t x, uint16_t y, uint16_t color) {
    // ...implementation...
}

void STM32F0_Hardware::TFT_FillScreen(uint16_t color) {
    // ...implementation...
}

bool STM32F0_Hardware::TFT_TouchGetXY(uint16_t& x, uint16_t& y) {
    // ...implementation...
    return false;
}

// ADC
void STM32F0_Hardware::ADC_Start(uint8_t channel) {
//    hadc.Instance = ADC1;
//    hadc.Init.Resolution = ADC_RESOLUTION_12B;
//    HAL_ADC_Init(&hadc);
//    HAL_ADC_Start(&hadc);
}

uint16_t STM32F0_Hardware::ADC_Read(uint8_t channel) {
//    return HAL_ADC_GetValue(&hadc);
    return 0;
}

// PWM
void STM32F0_Hardware::PWM_Set(uint8_t timer, uint8_t channel, uint16_t value) {
    // ...implementation...
}

// Multi-core
void STM32F0_Hardware::M4_Core_Start(void (*func)(void)) {
    // ...implementation...
}

void STM32F0_Hardware::A7_Core_Init() {
    // ...implementation...
}

// Timer
void STM32F0_Hardware::Timer_Base_Start_IT(void* htim) {
    HAL_TIM_Base_Start_IT(reinterpret_cast<TIM_HandleTypeDef*>(htim));
}

// NVIC
void STM32F0_Hardware::System_Reset() {
    HAL_NVIC_SystemReset();
}

// Wireless (WB/WL)
#ifdef ENABLE_WIRELESS
void STM32F0_Hardware::BLE_Init() {
    // ...implementation...
}

void STM32F0_Hardware::LoRa_Send(uint8_t* data, uint8_t len) {
    // ...implementation...
}
#endif
