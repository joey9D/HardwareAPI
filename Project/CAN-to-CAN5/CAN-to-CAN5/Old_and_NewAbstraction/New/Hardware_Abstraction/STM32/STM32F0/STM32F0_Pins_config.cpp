// #include "STM32F0_Pins_config.h"
// #include <cassert>


// typedef enum {
//     GPIO_INPUT,
//     GPIO_OUTPUT
// } GPIO_Direction;


// // #define X(NAME, PORT, PIN, INVERTED, MODE, PULL) \
// //     const Pin NAME(PORT, PIN, INVERTED, MODE, PULL);
// // PIN_LIST
// // #undef X

// // #define X(NAME, PORT, PIN, INVERTED, MODE, PULL) &NAME,
// // const Pin* allPins[] = {
// //     PIN_LIST
// // };
// // #undef X

// // #define X(NAME, PORT, PIN, INVERTED, MODE, PULL) &NAME,
// // const Pin* clampInPins[] = { &CLAMP_INPUT_LIST };
// // const Pin* clampOutPins[] = { &CLAMP_OUTPUT_LIST };
// // #undef X

// // void initAllPins() {
// //     for (auto pin : allPins) {
// //         pin->init();
// //     }
// // }






// pin_config::pin_config() 
// {
//     // Constructor implementation
// }

// const clamp_config_t clamp_configs[] = 
// {
//     /* Clamp 0 */
//     {
//         .port = GPIOA, /* input on port A  */
//         .pin_input = GPIO_PIN_0, /* input pin number */
//         .pin_output = GPIO_PIN_1, /* output pin number */
//         .input_inverted = false,
//         .output_inverted = false,
//         .output_high_current = false, /* no high current needed */
//         .input_pull = GPIO_PULLUP, /* from stm32f7xx_hal_gpio.h */
//         .debounce_time = 250 /* no debounce */

//     },
//     /* Clamp 1 */
//     {
//         .port = GPIOA,
//         .pin_input = GPIO_PIN_2,
//         .pin_output = GPIO_PIN_3,
//         .input_inverted = true, /* input is active low */
//         .output_inverted = false,
//         .output_high_current = true, /* e.g., needs more current */
//         .input_pull = GPIO_PULLUP, /* use an internal pull-up */
//         .debounce_time = 10 /* no debounce */
//     }
    
// };


// int pin_config::getClampPin(int clamp, bool output) 
// {
//     // Adjust clamp number to start from 1 instead of 0
//     assert(clamp >= 0 && clamp < NUMBER_OF_CLAMPS);

//     if (output) 
//     {
//         return (clamp_configs[clamp].pin_output);
//     } 
//     else 
//     {
//         return(clamp_configs[clamp].pin_input);
//     }
// }

// GPIO_TypeDef* pin_config::getClampGPIOPort(int clamp) 
// {
//     // Adjust clamp number to start from 1 instead of 0
//     assert(clamp >= 0 && clamp < NUMBER_OF_CLAMPS);
//     //clamp -= 1; // Decrement clamp number to match array index

//     return reinterpret_cast<GPIO_TypeDef*>(clamp_configs[clamp].port);
// }

// int pin_config::getClampPull(int clamp) 
// {
//     // Adjust clamp number to start from 1 instead of 0
//     assert(clamp >= 0 && clamp < NUMBER_OF_CLAMPS);
//     //clamp -= 1; // Decrement clamp number to match array index

//     return clamp_configs[clamp].input_pull;
// }

// bool pin_config::getClampHighCurrent(int clamp) 
// {
//     // Adjust clamp number to start from 1 instead of 0
//     assert(clamp >= 0 && clamp < NUMBER_OF_CLAMPS);
//     //clamp -= 1; // Decrement clamp number to match array index

//     return clamp_configs[clamp].output_high_current;
// }

// bool pin_config::getClampInverted(int clamp, bool output) 
// {
//     // Adjust clamp number to start from 1 instead of 0
//     assert(clamp >= 0 && clamp < NUMBER_OF_CLAMPS);
//     //clamp -= 1; // Decrement clamp number to match array index

//     return output 
//            ? clamp_configs[clamp].output_inverted 
//            : clamp_configs[clamp].input_inverted;
// }





