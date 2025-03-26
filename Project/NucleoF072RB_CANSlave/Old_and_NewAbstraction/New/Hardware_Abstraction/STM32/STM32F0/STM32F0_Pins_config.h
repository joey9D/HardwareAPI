#ifndef STM32F0_PINS_CONFIG_H
#define STM32F0_PINS_CONFIG_H

#include "stm32f0xx_hal.h" // Or your specific device's HAL header
#include "singleton.h"

#define LED_GREEN_PIN GPIO_PIN_5
#define LED_GREEN_PORT GPIOA
#define LED_RED_PIN  GPIO_PIN_6
#define LED_RED_PORT GPIOA

// Define a structure to hold the port and pin
typedef struct {
    GPIO_TypeDef* port;
    uint16_t pin;
} GPIO_PinConfig_t;

typedef struct {
    void* port;   /* e.g., GPIOA, or null if not STM32.  */
    uint16_t pin_input; /* e.g., GPIO_PIN_0, or an integer if ESP32. */
    uint16_t pin_output; /* e.g., GPIO_PIN_1, or an integer if ESP32. */
    bool input_inverted; /* true if input is inverted (active low). */
    bool output_inverted; /* true if output is inverted. */
    bool output_high_current; /* true if output clamp needs higher drive. */
    int input_pull; /* Could be: 0 = no pull, 1 = pull-up, 2 = pull-down,
                       or you can store actual defines from your MCU's HAL. */
} clamp_config_t;

extern const clamp_config_t clamp_configs[];

class pin_config {
    SINGLETON (pin_config)
public:
    int getClampPin(int clamp, bool output);
    int getClampPull(int clamp);
    bool getClampHighCurrent(int clamp);
    bool getClampInverted(int clamp, bool output);
    bool measureClampInput(int clamp);
    void setClampOutput(int clamp, bool state);
    // static inline void stm32_get_config_defaults(GPIO_InitTypeDef *GPIO_InitStruct);
    // static inline void stm32_pin_set_output_strength(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, uint32_t Speed);
    // static inline void stm32_pin_set_config(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, uint32_t Mode, uint32_t Pull, uint32_t Speed, uint32_t Alternate);
    // static inline void stm32_pin_set_output_level(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState);
    // static inline GPIO_PinState stm32_pin_get_input_level(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
    GPIO_TypeDef* getClampGPIOPort(int clamp);

};

#endif // PINS_CONFIG_H
