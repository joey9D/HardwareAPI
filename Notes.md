# Notes  

Timer-Klasse via systick?  

Arduino digitalWriteFast
<https://github.com/ArminJo/digitalWriteFast>
kommt mit:

- pinModeFast()
- digitalWriteFast()
- digitalReadFast()
- digitalToggleFast()

hier kommt dann auch **pin speed** zum Einsatz.

```c++
/**
 * Input
 */
MyInput::MyInput(uint32_t pin, uint32_t mode, uint32_t pull, uint32_t speed, uint32_t port, bool pinInverted) 
#if defined(ARDUINO_AVR_UNO_WIFI_REV2) || defined(AVR_UNO_WIFI_REV2)
    : _pin(pin), _mode(mode)
#elif defined(NUCLEO_G071RB) || defined(STM32_G071RB)
    : _pin(pin), _mode(mode), _pull(pull), _speed(speed), _port(port), _pinInverted(pinInverted)
#endif
{
    // initilisations list
    _debounceTime = debounceTime;
}

/*Input*/
bool MyInput::isInputPinOn() const {
    bool retval = false;
# if defined(ARDUINO_AVR_UNO_WIFI_REV2) || defined(AVR_UNO_WIFI_REV2)
    if (digitalRead(getPin()) == HIGH) {
        retval = true;
    }

#elif defined(NUCLEO_G071RB || STM32_NUCLEO_G071RB)
    if (HAL_GPIO_ReadPin(getPort(), getPin()) == GPIO_PIN_SET) {
           retval = true;
    }

#endif
    if (isPinInverted()) {
        retval = !retval;
    }

    return retval;
}
```
