#pragma once
#include "stm32g0xx_hal.h"
//#include "STM32F0_Pins_config.h"




struct BoardPins 
{
    Pin GreenLED   {GPIOA, GPIO_PIN_5, false, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL};
    Pin Clamp0In {GPIOA, GPIO_PIN_0, false, GPIO_MODE_INPUT, GPIO_PULLUP, ExtiTrigger::RisingFalling};
    Pin Clamp0Out  {GPIOA, GPIO_PIN_1, false, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL};
    Pin SR_STR     {GPIOA, GPIO_PIN_2, false, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL};
    Pin SR_D0      {GPIOA, GPIO_PIN_7, false, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL};
    Pin SR_CLK     {GPIOA, GPIO_PIN_6, false, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL};
    Pin SR_PL      {GPIOB, GPIO_PIN_1, false, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL};
    Pin SR_PISO    {GPIOA, GPIO_PIN_4, false, GPIO_MODE_INPUT,     GPIO_NOPULL};

    // Optionally, arrays for groups:
    std::array<Pin*, 1> clampInputs  { &Clamp0In };
    std::array<Pin*, 1> clampOutputs { &Clamp0Out };
    std::array<Pin*, 8> allPins      { &GreenLED, &Clamp0In, &Clamp0Out, &SR_STR, &SR_D0, &SR_CLK, &SR_PL, &SR_PISO };
};