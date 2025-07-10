#include "ShiftRegisterIO.h"

GPIO_TypeDef* const ShiftRegisterIO::PORTA = GPIOA;
GPIO_TypeDef* const ShiftRegisterIO::PORTB = GPIOB;


void ShiftRegisterIO::init()  // To do Write a common configure function for a strcuture for specific microcontrolller.
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // Configure PORTA pins: STR, D0, CLK
    GPIO_InitStruct.Pin = PIN_STR | PIN_D0 | PIN_CLK;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(PORTA, &GPIO_InitStruct);

    // Configure PL (Parallel Load) on PORTB
    GPIO_InitStruct.Pin = PIN_PL;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    HAL_GPIO_Init(PORTB, &GPIO_InitStruct);

    // Configure PISO input on PORTA
    GPIO_InitStruct.Pin = PIN_PISO;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(PORTA, &GPIO_InitStruct);

    // Initial states
    HAL_GPIO_WritePin(PORTA, PIN_STR, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(PORTA, PIN_D0, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(PORTA, PIN_CLK, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(PORTB, PIN_PL, GPIO_PIN_SET);

    outputState = 0;
    inputState = 0;
}

void ShiftRegisterIO::pulse(GPIO_TypeDef* port, uint16_t pin) 
{
    HAL_GPIO_WritePin(port, pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(port, pin, GPIO_PIN_RESET);
}
/* U7 is SIPO (Serial In Parallel Out) shift register. It takes serial data and converts it to parallel data. 
The output is latched on the STR pin. 
The CLK pin is used to clock the data into the register. The D0 pin is used to input the serial data.
*/
void ShiftRegisterIO::writeOutputs(uint8_t data) 
{
    outputState = data;
    for (int i = 7; i >= 0; --i) 
    {
        HAL_GPIO_WritePin(PORTA, PIN_D0, (data >> i) & 0x01 ? GPIO_PIN_SET : GPIO_PIN_RESET);
        pulse(PORTA, PIN_CLK);
    }
    pulse(PORTA, PIN_STR); // latch data to output
}

/*U8 is PISO (Parallel In Serial Out) shift register. It takes parallel data and converts it to serial data.
The parallel data is loaded on the PL pin. The CLK pin is used to clock the data out of the register. 
The PISO pin is used to output the serial data.
*/


uint8_t ShiftRegisterIO::readInputs() 
{
    inputState = 0;

    // Load parallel inputs from U8
    HAL_GPIO_WritePin(PORTB, PIN_PL, GPIO_PIN_RESET); // assert PL low to load parallel data , low -> U8 attaches its 8 input pins.
    HAL_GPIO_WritePin(PORTB, PIN_PL, GPIO_PIN_SET); //  de-assert PL -> freeze the snapshot of the inputs inside U8. 

    // if (HAL_GPIO_ReadPin(PORTA, PIN_PISO) == GPIO_PIN_SET) {
    //     HAL_GPIO_TogglePin(LED_GREEN_PORT, LED_GREEN_PIN); // Debugging: Toggle LED if PISO is high
    //     HAL_Delay(200);
    // }

    // GPIO_PinState rawAfterPL = HAL_GPIO_ReadPin(PORTA, PIN_PISO);

    for (int i = 7; i >= 0; --i) 
    {
        pulse(PORTA, PIN_CLK); // rising edge  of clk -> shifts the next bit into the PISO.
        if (HAL_GPIO_ReadPin(PORTA, PIN_PISO)) 
        {
            inputState |= (1 << i); // read the PISO pin and set the corresponding bit in inputState.
        }
    }
    return inputState;
}

void ShiftRegisterIO::setOutputBit(uint16_t index, bool state) 
{
    if (index >= 8) return;
    if (state)
        outputState |= (1 << index);
    else
        outputState &= ~(1 << index);
    writeOutputs(outputState);
}

bool ShiftRegisterIO::getInputBit(uint16_t index) const 
{
    if (index >= 8) return false;
    return (inputState >> index) & 0x01;
}
