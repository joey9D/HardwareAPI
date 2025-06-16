#pragma once
#include <cassert>
#include "stm32_gpio.hpp"
#include "stm32_gpio_mapping.hpp"


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
        GPIO_MODE_INPUT
        /*!< Output Push Pull Mode                                               */
        GPIO_MODE_OUTPUT_PP
        /*!< Output Open Drain Mode                                             */
        GPIO_MODE_OUTPUT_OD
        /*!< Alternate Function Push Pull Mode                                   */
        GPIO_MODE_AF_PP
        /*!< Alternate Function Open Drain Mode                                  */
        GPIO_MODE_AF_OD
        /*!< Analog Mode                                                         */
        GPIO_MODE_ANALOG
        /*!< External Interrupt Mode with Rising edge trigger detection          */
        GPIO_MODE_IT_RISING
        /*!< External Interrupt Mode with Falling edge trigger detection         */
        GPIO_MODE_IT_FALLING
        /*!< External Interrupt Mode with Rising/Falling edge trigger detection  */
        GPIO_MODE_IT_RISING_FALLING
        /*!< External Event Mode with Rising edge trigger detection             */
        GPIO_MODE_EVT_RISING
        /*!< External Event Mode with Falling edge trigger detection            */
        GPIO_MODE_EVT_FALLING
        /*!< External Event Mode with Rising/Falling edge trigger detection      */
        GPIO_MODE_EVT_RISING_FALLING
    }

    enum class Pull
    {
        GPIO_NOPULL     /*!< No Pull-up or Pull-down activation  */
        GPIO_PULLUP     /*!< Pull-up activation                  */
        GPIO_PULLDOWN   /*!< Pull-down activation                */
    }

    enum class Speed
    {
        GPIO_SPEED_FREQ_LOW          /*!< Low speed       */
        GPIO_SPEED_FREQ_MEDIUM       /*!< Medium speed    */
        GPIO_SPEED_FREQ_HIGH         /*!< High speed      */
        GPIO_SPEED_FREQ_VERY_HIGH    /*!< Very high speed */
    }

    enum class HAL_State
    {
        HAL_OK,
        HAL_ERROR,
        HAL_BUSY,
        HAL_TIMEOUT
    }

    STM32Gpio(
        uint16_t pin,
        GPIO_TypeDef *port,
        Mode mode,
        Pull pull,
        Speed speed)
        : _pin(pin), _port(port), _mode(mode), _pull(pull), _speed(speed)
    {
        assert(pin < stm32x0_gpio_mapping::pin_count);
        assert(port < stm32x0_gpio_mapping::gpio_port[static_cast<uint8_t>(port)]);

        GPIO_InitTypeDef GPIO_InitStruct = {0};

        __HAL_RCC_GPIOC_CLK_ENABLE();
        __HAL_RCC_GPIOF_CLK_ENABLE();
        __HAL_RCC_GPIOA_CLK_ENABLE();

        writePin();

        GPIO_InitStruct.Pin = _pin;
    }

    ~SMT32Gpio9() = default;;

    // getter
    uint16_t getPin() const {    return _pin;    }
    GPIO_TypeDef* getPort() const {
        return stm32x0_gpio_mapping::gpio_port[static_cast<uint8_t>(_port)];
    }
    Mode getMode() const {    return _mode;   }
    Pull getPull() const {    return _pull;   }
    Speed getSpeed() const {    return _speed;   }

    // Optional: Setter mit Typprüfung
    void setMode(Mode mode);
    void setPull(Pull pull);
    void setSpeed(Speed speed);



    // gpio function abstraction for hal functions
    bool STM32Gpio::readPin() const
    {
        return HAL_GPIO_ReadPin(getPort(), getPin());
    }

    void STM32Gpio::writePin(bool value) const
    {
        HAL_GPIO_WritePin(getPort(), getPin(), value ? GPIO_PIN_SET : GPIO_PIN_RESET);
    }

    void STM32Gpio::togglePin() const
    {
        HAL_GPIO_TogglePin(getPort(), getPin());
    }


private:
    uint16_t _pin;
    GPIO_TypeDef *_port;
    Mode _mode;
    Pull _pull;
    Speed _speed;
};
