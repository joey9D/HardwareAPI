#include "STM32F0_Pins_config.h"
#include <cassert>
#include "pins_config.h"


#
const clamp_config_t clamp_configs[] = {
    /* Clamp 0 */
    {
        .port = GPIOA, /* input on port A  */
        .pin_input = GPIO_PIN_0, /* input pin number */
        .pin_output = GPIO_PIN_1, /* output pin number */
        .input_inverted = false,
        .output_inverted = false,
        .output_high_current = false, /* no high current needed */
        .input_pull = GPIO_NOPULL /* from stm32f7xx_hal_gpio.h */
    },
    /* Clamp 1 */
    {
        .port = GPIOC,
        .pin_input = GPIO_PIN_2,
        .pin_output = GPIO_PIN_3,
        .input_inverted = true, /* input is active low */
        .output_inverted = false,
        .output_high_current = true, /* e.g., needs more current */
        .input_pull = GPIO_PULLUP /* use an internal pull-up */
    }
};


int pin_config::getClampPin(int clamp, bool output) {
    // Adjust clamp number to start from 1 instead of 0
    assert(clamp >= 0 && clamp < NUMBER_OF_CLAMPS);

    if (output) {
        return (clamp_configs[clamp].pin_output);
    } else {
        return(clamp_configs[clamp].pin_input);
    }
}

GPIO_TypeDef* pin_config::getClampGPIOPort(int clamp) {
    // Adjust clamp number to start from 1 instead of 0
    assert(clamp >= 0 && clamp < NUMBER_OF_CLAMPS);
    //clamp -= 1; // Decrement clamp number to match array index

    return reinterpret_cast<GPIO_TypeDef*>(clamp_configs[clamp].port);
}

int pin_config::getClampPull(int clamp) {
    // Adjust clamp number to start from 1 instead of 0
    assert(clamp >= 0 && clamp < NUMBER_OF_CLAMPS);
    //clamp -= 1; // Decrement clamp number to match array index

    return clamp_configs[clamp].input_pull;
}

bool pin_config::getClampHighCurrent(int clamp) {
    // Adjust clamp number to start from 1 instead of 0
    assert(clamp >= 0 && clamp < NUMBER_OF_CLAMPS);
    //clamp -= 1; // Decrement clamp number to match array index

    return clamp_configs[clamp].output_high_current;
}

bool pin_config::getClampInverted(int clamp, bool output) {
    // Adjust clamp number to start from 1 instead of 0
    assert(clamp >= 0 && clamp < NUMBER_OF_CLAMPS);
    //clamp -= 1; // Decrement clamp number to match array index

    return output 
           ? clamp_configs[clamp].output_inverted 
           : clamp_configs[clamp].input_inverted;
}

// bool pin_config::measureClampInput(int clamp) {
//     // Adjust clamp number to start from 1 instead of 0
//     assert(clamp > 0 && clamp <= NUMBER_OF_CLAMPS);
//     clamp -= 1; // Decrement clamp number to match array index

//     GPIO_PinConfig_t pinConfig = getClampInputPin(clamp + 1); // Increment back to match the original clamp number
//     return !(HAL_GPIO_ReadPin(pinConfig.port, pinConfig.pin) == getClampInverted(clamp + 1, false));
// }

// void pin_config::setClampOutput(int clamp, bool state) {
//     // Adjust clamp number to start from 1 instead of 0
//     assert(clamp > 0 && clamp <= NUMBER_OF_CLAMPS);
//     clamp -= 1; // Decrement clamp number to match array index

//     GPIO_PinConfig_t pinConfig = getClampOutputPin(clamp + 1); // Increment back to match the original clamp number
//     HAL_GPIO_WritePin(pinConfig.port, pinConfig.pin, !(state == getClampInverted(clamp + 1, true)) ? GPIO_PIN_SET : GPIO_PIN_RESET);
// }
// inline void pins_config::stm32_get_config_defaults(GPIO_InitTypeDef *GPIO_InitStruct)
// {
//     /* Sanity check arguments */
//     assert_param(GPIO_InitStruct != NULL);

//     /* Default configuration values */
//     GPIO_InitStruct->Pin = GPIO_PIN_All;
//     GPIO_InitStruct->Mode = GPIO_MODE_INPUT;
//     GPIO_InitStruct->Pull = GPIO_PULLUP;
//     GPIO_InitStruct->Speed = GPIO_SPEED_FREQ_LOW;
//     GPIO_InitStruct->Alternate = 0;
// }

// inline void pins_config::stm32_pin_set_output_strength(int clamp)
// {
//     GPIO_InitTypeDef GPIO_InitStruct = {0};

//     GPIO_InitStruct.Pin = clamps_config;
//     GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//     GPIO_InitStruct.Pull = GPIO_NOPULL;
//     GPIO_InitStruct.Speed = Speed;

//     HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
// }

// inline void pins_config::stm32_pin_set_config(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, uint32_t Mode, uint32_t Pull, uint32_t Speed, uint32_t Alternate)
// {
//     // Sanity check to avoid dereferencing NULL
//     if (GPIOx == NULL) return;

//     GPIO_InitTypeDef GPIO_InitStruct = {0};

//     GPIO_InitStruct.Pin = GPIO_Pin;
//     GPIO_InitStruct.Mode = Mode;
//     GPIO_InitStruct.Pull = Pull;
//     GPIO_InitStruct.Speed = Speed;
//     GPIO_InitStruct.Alternate = Alternate;

//     HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
// }


// inline void pins_config::stm32_pin_set_output_level(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState) // Redundant
// {
//     HAL_GPIO_WritePin(GPIOx, GPIO_Pin, PinState);
// }

// inline GPIO_PinState pins_config::stm32_pin_get_input_level(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin) //Redundant
// {
//     return HAL_GPIO_ReadPin(GPIOx, GPIO_Pin);
//}




