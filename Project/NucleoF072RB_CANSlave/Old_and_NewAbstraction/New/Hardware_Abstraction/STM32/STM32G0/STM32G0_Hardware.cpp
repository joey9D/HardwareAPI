#include "STM32G0_Hardware.h"
#include "stm32g0xx_hal.h"

// Clock
void STM32G0_Hardware::Clock_Init() {
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

void STM32G0_Hardware::Delay(uint32_t ms) {
    HAL_Delay(ms);
}

uint32_t STM32G0_Hardware::GetTick() {
    return HAL_GetTick();
}

// GPIO
void STM32G0_Hardware::GPIO_SetMode(void* port, uint8_t pin, GPIO_Mode mode) {
    GPIO_InitTypeDef gpio = {0};
    gpio.Pin = 1 << pin;
    gpio.Mode = static_cast<uint32_t>(mode);
    HAL_GPIO_Init(reinterpret_cast<GPIO_TypeDef*>(port), &gpio);
}

bool STM32G0_Hardware::GPIO_Read(void* port, uint8_t pin) {

    return HAL_GPIO_ReadPin(reinterpret_cast<GPIO_TypeDef*>(port), pin) == GPIO_PIN_SET;
}

void STM32G0_Hardware::GPIO_Write(void* port, uint8_t pin, GPIO_State state) {
    HAL_GPIO_WritePin(reinterpret_cast<GPIO_TypeDef*>(port), pin, state == GPIO_HIGH ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

// CAN
void STM32G0_Hardware::CAN_Init(uint8_t bus, uint32_t baudrate) {
    // ...implementation...
}

void STM32G0_Hardware::CAN_Send(uint8_t bus, uint32_t id, uint8_t* data, uint8_t len) {
    // ...implementation...
}

bool STM32G0_Hardware::CAN_Receive(uint8_t bus, uint32_t& id, uint8_t* buffer, uint8_t& len) {
    // ...implementation...
    return false;
}

void STM32G0_Hardware::CAN_ConfigFilter(uint8_t bus, uint32_t id, uint32_t mask) {
    // ...implementation...
}

void STM32G0_Hardware::errorHandler(uint32_t error) {
    if(error != HAL_FDCAN_ERROR_NONE)
		{
			switch(error)
			{
			case HAL_FDCAN_ERROR_TIMEOUT:
			case HAL_FDCAN_ERROR_NOT_INITIALIZED:
			case HAL_FDCAN_ERROR_NOT_READY:
			case HAL_FDCAN_ERROR_NOT_STARTED:
			case HAL_FDCAN_ERROR_NOT_SUPPORTED:
			case HAL_FDCAN_ERROR_PARAM:
			case HAL_FDCAN_ERROR_PENDING:
			case HAL_FDCAN_ERROR_RAM_ACCESS:
			case HAL_FDCAN_ERROR_FIFO_EMPTY:
			case HAL_FDCAN_ERROR_FIFO_FULL:
			case HAL_FDCAN_ERROR_LOG_OVERFLOW:
			case HAL_FDCAN_ERROR_RAM_WDG:
			case HAL_FDCAN_ERROR_PROTOCOL_ARBT:
			case HAL_FDCAN_ERROR_PROTOCOL_DATA:
			case HAL_FDCAN_ERROR_RESERVED_AREA:
			case FDCAN_PROTOCOL_ERROR_NONE:
			case FDCAN_PROTOCOL_ERROR_ACK:
			case FDCAN_PROTOCOL_ERROR_BIT0:
			case FDCAN_PROTOCOL_ERROR_CRC:
			case FDCAN_PROTOCOL_ERROR_NO_CHANGE:
			default:
				break;
			}

			//todo
			//canopen_app_resetCommunication();
		}
}

// TFT/Display
void STM32G0_Hardware::TFT_Init(uint16_t width, uint16_t height) {
    // ...implementation...
}

void STM32G0_Hardware::TFT_DrawPixel(uint16_t x, uint16_t y, uint16_t color) {
    // ...implementation...
}

void STM32G0_Hardware::TFT_FillScreen(uint16_t color) {
    // ...implementation...
}

bool STM32G0_Hardware::TFT_TouchGetXY(uint16_t& x, uint16_t& y) {
    // ...implementation...
    return false;
}

// ADC
void STM32G0_Hardware::ADC_Start(uint8_t channel) {
//    hadc.Instance = ADC1;
//    hadc.Init.Resolution = ADC_RESOLUTION_12B;
//    HAL_ADC_Init(&hadc);
//    HAL_ADC_Start(&hadc);
}

uint16_t STM32G0_Hardware::ADC_Read(uint8_t channel) {
//    return HAL_ADC_GetValue(&hadc);
    return 0;
}

// PWM
void STM32G0_Hardware::PWM_Set(uint8_t timer, uint8_t channel, uint16_t value) {
    // ...implementation...
}

// Multi-core
void STM32G0_Hardware::M4_Core_Start(void (*func)(void)) {
    // ...implementation...
}

void STM32G0_Hardware::A7_Core_Init() {
    // ...implementation...
}

// Timer
void STM32G0_Hardware::Timer_Base_Start_IT(void* htim) {
    HAL_TIM_Base_Start_IT(reinterpret_cast<TIM_HandleTypeDef*>(htim));
}

// NVIC
void STM32G0_Hardware::System_Reset() {
    HAL_NVIC_SystemReset();
}

// Wireless (WB/WL)
#ifdef ENABLE_WIRELESS
void STM32G0_Hardware::BLE_Init() {
    // ...implementation...
}

void STM32G0_Hardware::LoRa_Send(uint8_t* data, uint8_t len) {
    // ...implementation...
}
#endif
