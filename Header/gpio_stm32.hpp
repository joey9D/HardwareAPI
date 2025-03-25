#ifndef _GPIO_STM32_HPP
#define _GPIO_STM32_HPP

#include "../Interfaces/gpio_base.hpp"
#include "main.h" // main -> stm32 header with GPIO_TypeDef


class GPIO_STM32 : public GPIOBase {
    protected:
        GPIO_TypeDef* _port;
        uint32_t _pin;
        bool _pinInverted;

    public:
        GPIO_STM32(GPIO_TypeDef* port, uint32_t pin, bool pinInverted = false) {
            this->_port = port;
            this->_pin = pin;
            this->_pinInverted = pinInverted;

        }
        
        ~GPIO_STM32();

        void config(Mode mode, Pull pull, Speed speed) override {
            _mode = mode;
            _pull = pull;
            _speed = speed;

            GPIO_InitTypeDef GPIO_InitStruct = {0};
            GPIO_InitStruct.Pin = _pin;

            // ? instead of if else
            GPIO_InitStruct.Mode = (mode == Mode::Input) ? GPIO_MODE_INPUT :
                                    (mode == Mode::Output) ? GPIO_MODE_OUTPUT_PP :
                                    (mode == Mode::OpenDrain) ? GPIO_MODE_OUTPUT_OD :
                                    (mode == Mode::Analog) ? GPIO_MODE_ANALOG : GPIO_MODE_AF_PP;
            GPIO_InitStruct.Pull = (pull == Pull::NoPull) ? GPIO_NOPULL :
                                    (pull == Pull::PullUp) ? GPIO_PULLUP : GPIO_PULLDOWN;
            GPIO_InitStruct.Speed = (speed == Speed::Low) ? GPIO_SPEED_FREQ_LOW :
                                    (speed == Speed::Medium) ? GPIO_SPEED_FREQ_MEDIUM :
                                    (speed == Speed::High) ? GPIO_SPEED_FREQ_HIGH : GPIO_SPEED_FREQ_VERY_HIGH;

            HAL_GPIO_Init(_port, &GPIO_InitStruct);
        }

        void write(bool pinState) override {
            HAL_GPIO_WritePin(_port, _pin, pinState);
        }

        bool read() const override {
            bool readingState = HAL_GPIO_ReadPin(_port, _pin);
            return readingState
        }

        void toggle() override {
            HAL_GPIO_TogglePin( _port, _pin);
        }
    }










#endif /* _GPIO_STM32_HPP */