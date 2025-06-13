#pragma once

#include "gpio_interface.hpp"


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
        // Initialize the GPIO pin here
    }

    ~SMT32Gpio9() = default;;

    // getter
    uint16_t getPin() const;
    GPIO_TypeDef* getPort() const;
    Mode getMode() const;
    Pull getPull() const;
    Speed getSpeed() const;

    // Optional: Setter mit Typprüfung
    void setMode(Mode mode);
    void setPull(Pull pull);
    void setSpeed(Speed speed);



    // gpio function abstraction for hal functions
    bool readPin() const;
    void writePin(bool value) const;
    void togglePin() const;


private:
    uint16_t _pin;
    GPIO_TypeDef *_port;
    Mode _mode;
    Pull _pull;
    Speed _speed;
};
