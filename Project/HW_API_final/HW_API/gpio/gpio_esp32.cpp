#include "gpio_esp32.hpp"
#include "hw_enum_classes.hpp"
#include "../drivers/esp32_hal_wrapper/esp32_hal_inc.hpp"

Gpio::Gpio(
    uint64_t pin,
    Mode mode,
    Pull pull,
    Speed speed,
    bool inverted,
    uint32_t debounceTime,
    uint8_t debounceState,
    Interrupt intr,
    Alternate alternate) : _pin(pin),
                           _mode(mode),
                           _pull(pull),
                           _speed(speed),
                           _inverted(inverted),
                           _debounceTime(debounceTime),
                           _debounceState(debounceState),
                           _intr(intr),
                           _alternate(alternate)
{
    // Initialization code can be added here if needed
}

void Gpio::gpio_init()
{
    gpio_config_t config = {};
    config.pin_bit_mask = (1ULL << _pin); // unsigned long long
    config.mode = static_cast<gpio_mode_t>(_mode);

    switch (_pull)
    {
    case Pull::Down:
        config.pull_up_en = GPIO_PULLUP_DISABLE;
        config.pull_down_en = GPIO_PULLDOWN_ENABLE;
        break;
    case Pull::Up:
        config.pull_up_en = GPIO_PULLUP_ENABLE;
        config.pull_down_en = GPIO_PULLDOWN_DISABLE;
        break;
    case Pull::UpDown:
        config.pull_up_en = GPIO_PULLUP_ENABLE;
        config.pull_down_en = GPIO_PULLDOWN_ENABLE;
        break;
    default:
        config.pull_up_en = GPIO_PULLUP_DISABLE;
        config.pull_down_en = GPIO_PULLDOWN_DISABLE;
        break;
    }

    config.intr_type = GPIO_INTR_DISABLE;
    gpio_config(&config);
    _lastTimeUs = 0;
}

bool Gpio::readPin() const
{
    return gpio_get_level((gpio_num_t)_pin);
}

void Gpio::writePin(bool value) const
{
    gpio_set_level((gpio_num_t)_pin, value ? 1 : 0);
}

void Gpio::togglePin() const
{
    writePin(!readPin());
}

bool Gpio::isPinOn() const
{
    // return readPin();
    bool retval = false;
    if (gpio_get_level((gpio_num_t)_pin))
    {
        retval = true;
    }

    if (isPinInverted())
    {
        retval = !retval;
    }

    return retval;
}

bool Gpio::isDebouncePinOn()
{
    bool retval = false;
    int level = gpio_get_level((gpio_num_t)_pin);
    if (_inverted)
        level = !level;

    if (_debounceTime != 0)
    {
        switch (_debounceState)
        {
        case 0: // pin off idle
            if (level)
            {
                _lastTimeUs = esp_timer_get_time();
                _debounceState = 1;
            }
            break;
        case 1: // pin off debounce
            if (level)
            {
                if ((esp_timer_get_time() - _lastTimeUs) > _debounceTime)
                {
                    _debounceState = 2;
                }
            }
            else
            {
                _debounceState = 0;
            }
            break;
        case 2: // pin on idle
            retval = true;
            if (!level)
            {
                _lastTimeUs = esp_timer_get_time();
                _debounceState = 3;
            }
            break;
        case 3: // pin on debounce
            retval = true;
            if (!level)
            {
                if ((esp_timer_get_time() - _lastTimeUs) > _debounceTime)
                {
                    _debounceState = 0;
                }
            }
            else
            {
                _debounceState = 2;
            }
            break;
        default:
            _debounceState = 0;
            break;
        }
    }
    else
    {
        retval = true;
    }
    return retval;
}

/**
 * @brief Helper functions
 */

bool Gpio::isPinInverted() const
{
    return _inverted;
}

/**
 * @brief Getter functions
 */
uint64_t Gpio::getPin() const { return _pin; }

Mode Gpio::getMode() const { return _mode; }

Pull Gpio::getPull() const { return _pull; }

Speed Gpio::getSpeed() const { return _speed; }

Alternate Gpio::getAlternate() const { return Alternate::None; } // ESP32 does not use Alternate