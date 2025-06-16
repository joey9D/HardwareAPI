#pragma once
#include <cassert>
#include "stm32_gpio.hpp"
#include "stm32_gpio_mapping.hpp"

namespace stm32
{
class STM32Gpio : public GpioInterface
{
public:
    enum class Port
    {
        A, B, C, D, E, F
    }

    enum class Mode
    {
        /*!< Input Floating Mode                                                 */
        Input = GPIO_MODE_INPUT
        /*!< Output Push Pull Mode                                               */
        Output_Push_Pull = GPIO_MODE_OUTPUT_PP
        /*!< Output Open Drain Mode                                              */
        Output_Open_Drain = GPIO_MODE_OUTPUT_OD
        /*!< Alternate Function Push Pull Mode                                   */
        Alt_Function_Push_Pul = GPIO_MODE_AF_PP
        /*!< Alternate Function Open Drain Mode                                  */
        Alt_Function_Open_Drain = GPIO_MODE_AF_OD
        /*!< Analog Mode                                                         */
        Analog = GPIO_MODE_ANALOG
        /*!< External Interrupt Mode with Rising edge trigger detection          */
        Interrupt_Rising = GPIO_MODE_IT_RISING
        /*!< External Interrupt Mode with Falling edge trigger detection         */
        Interrupt_Falling = GPIO_MODE_IT_FALLING
        /*!< External Interrupt Mode with Rising/Falling edge trigger detection  */
        Interrupt_Rising_Falling = GPIO_MODE_IT_RISING_FALLING
        /*!< External Event Mode with Rising edge trigger detection              */
        Event_Rising = GPIO_MODE_EVT_RISING
        /*!< External Event Mode with Falling edge trigger detection             */
        Event_Falling = GPIO_MODE_EVT_FALLING
        /*!< External Event Mode with Rising/Falling edge trigger detection      */
        Event_Rising_Falling = GPIO_MODE_EVT_RISING_FALLING
    };

    enum class Pull
    {
        None = GPIO_NOPULL      /*!< No Pull-up or Pull-down activation  */
        Up = GPIO_PULLUP        /*!< Pull-up activation                  */
        Down = GPIO_PULLDOWN    /*!< Pull-down activation                */
    };

    enum class Speed
    {
        Low = GPIO_SPEED_FREQ_LOW               /*!< Low speed       */
        Mdeium = GPIO_SPEED_FREQ_MEDIUM         /*!< Medium speed    */
        High = GPIO_SPEED_FREQ_HIGH             /*!< High speed      */
        Very_High = GPIO_SPEED_FREQ_VERY_HIGH   /*!< Very high speed */
    };

    enum class HAL_State
    {
        HAL_OK,
        HAL_ERROR,
        HAL_BUSY,
        HAL_TIMEOUT
    };

    STM32Gpio(
        uint16_t pin,
        Port port,
        Mode mode,
        Pull pull,
        Speed speed)
        : _pin(pin), _port(port), _mode(mode), _pull(pull), _speed(speed)
    {
        assert(pin < stm32x0_gpio_mapping::pin_count);
        assert(port < stm32x0_gpio_mapping::gpio_port[static_cast<uint8_t>(port)]);

        GPIO_InitTypeDef GPIO_InitStruct = {0};

        clock_enable(_port);

        writePin(0);

        GPIO_InitStruct.Pin = static_cast<uint32_t>(_pin);
        GPIO_InitStruct.Mode = static_cast<uint32_t>(_mode);
        GPIO_InitStruct.Pull = static_cast<uint32_t>(_pull);
        Gpio_InitStruct.Speed = static_cast<uint32_t>(_speed);
        HAL_GPIO_Init(getPort(), &GPIO_InitStruct);
    }

    ~SMT32Gpio9() override= default;

    // getter
    [[nodiscard]] uint16_t getPin() const override {    return _pin;    }
    [[nodiscard]] GPIO_TypeDef* getPort() const override
    {
        return stm32x0_gpio_mapping::gpio_port[static_cast<size_t>(_port)];
    }
    [[nodiscard]] Mode getMode() const override {    return _mode;   }
    [[nodiscard]] Pull getPull() const override {    return _pull;   }
    [[nodiscard]] Speed getSpeed() const override {    return _speed;   }


    // gpio function abstraction for hal functions
    [[nodiscard]] bool readPin() const override
    {
        return HAL_GPIO_ReadPin(getPort(), getPin());
    }

    void writePin(bool value) override
    {
        HAL_GPIO_WritePin(getPort(), getPin(), value ? GPIO_PIN_SET : GPIO_PIN_RESET);
    }

    void togglePin() override
    {
        HAL_GPIO_TogglePin(getPort(), getPin());
    }

    bool lockPin() override
    {
        HAL_GPIO_LockPin(getPort(), getPin());
    }

    void EXTI_IRQHandler() override
    {
        HAL_GPIO_EXTI_IRQHandler(getPin());
    }

    void EXTI_Rising_Callback() override
    {
        HAL_GPIO_EXTI_Rising_Callback(getPin());
    }

    void EXTI_Falling_Callback() override
    {
        HAL_GPIO_EXTI_Falling_Callback(getPin());
    }

private:
    uint16_t _pin;
    Port _port;
    Mode _mode;
    Pull _pull;
    Speed _speed;


    void clock_enable(Port port) {
        switch (port) {
            case Port::A: __HAL_RCC_GPIOA_CLK_ENABLE(); break;
            case Port::B: __HAL_RCC_GPIOB_CLK_ENABLE(); break;
            case Port::C: __HAL_RCC_GPIOC_CLK_ENABLE(); break;
            case Port::D: __HAL_RCC_GPIOD_CLK_ENABLE(); break;
            case Port::E: __HAL_RCC_GPIOE_CLK_ENABLE(); break;
            case Port::F: __HAL_RCC_GPIOF_CLK_ENABLE(); break;
        }
    }
};
} /* end namespace stm32 */
