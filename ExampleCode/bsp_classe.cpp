/*
* IOHandler.h
*
*  Created on: Dec 18, 2023
*      Author: michael.grathwohl
*/

#ifndef IOHANDLER_H_
#define IOHANDLER_H_
#include <stdint.h>
#include <assert.h>
#include "../basic/Timer.h"
#include "main.h"

class GPIOBasic {
    public:
        GPIOBasic(uint16_t Pin, GPIO_TypeDef *Port, bool inverted = false) {
            assert(Port != NULL);
            _Pin = Pin;
            _Port = Port;
            _invertedPin = inverted;
        };

        virtual ~GPIOBasic() {};

        uint16_t getPin() {
            return _Pin;
        };


        GPIO_TypeDef *getPort() {
            return _Port;
        };

        bool isPinInverted() {
            return _invertedPin;
        };

    private:
        uint16_t _Pin = 0;
        GPIO_TypeDef *_Port = nullptr;
        bool _invertedPin = false;
};

class GPIOInput : public GPIOBasic {
    public:
        GPIOInput(uint16_t Pin, GPIO_TypeDef *Port, bool inverted, uint32_t debounceTime = 0) : GPIOBasic(Pin, Port, inverted) {
            _debounceTime = debounceTime;
        };

        bool isPinOn() {
            bool retval = false;
            if (HAL_GPIO_ReadPin(getPort(), getPin()) == GPIO_PIN_SET) {
                retval = true;
            }

            if (isPinInverted()) {
                retval = !retval;
            }

            return retval;
        };

        bool isDebouncePinOn() {
            bool retval = false;
            if (_debounceTime != 0) {
                switch (_debounceState) {
                case 0: // pin off idle
                    if (isPinOn()) {
                        _debounceTimer.startTime(_debounceTime);
                        _debounceState = 1; // pin off debounce
                    }
                    break;
                case 1: // pin off debounce
                    if (isPinOn()) {
                        if (_debounceTimer.isTimeExpired()) {
                            _debounceState = 2;
                        }
                    } else {
                        _debounceTimer.stopTime();
                        _debounceState = 0; // pin off idle
                    }
                    break;
                case 2: // pin on idle
                    retval = true;
                    if (!isPinOn()) {
                        _debounceTimer.startTime(_debounceTime);
                        _debounceState = 3; // pin on debounce
                    }
                    break;
                case 3: // pin on debounce
                    retval = true;
                    if (!isPinOn()) {
                        
                        if (_debounceTimer.isTimeExpired()) {
                            _debounceState = 0; // pin off idle
                        }
                    } else {
                        _debounceTimer.stopTime();
                        _debounceState = 2; // pin on idle
                    }
                    break;
                default:
                    _debounceState = 0;
                    break;
                }
            } else {
                retval = isPinOn();
            }
            return retval;
        };

    private:
        uint32_t _debounceTime = 0;
        Timer _debounceTimer;
        uint8_t _debounceState = 0;
    };

class GPIOOutput : public GPIOBasic {
    public:
        GPIOOutput(uint16_t Pin, GPIO_TypeDef *Port, bool inverted) : GPIOBasic(Pin, Port, inverted) {
            setOutput(false);
        };

        void setOutput(bool onState) {
            if (_oldState != onState) {
                GPIO_PinState PinState;
                _oldState = onState;
                if (isPinInverted()) {
                    onState = !onState;
                }

                if (onState) {
                    PinState = GPIO_PIN_SET;
                } else {
                    PinState = GPIO_PIN_RESET;
                }

                HAL_GPIO_WritePin(getPort(), getPin(), PinState);
            }
        };

        void toggle() {
            setOutput(!_oldState);
        };

        bool isPinOn() {
            return _oldState;
        };

    private:
        bool _oldState = true;
};
#endif /* IOHANDLER_H_ */