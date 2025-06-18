#ifndef __STM32_GPIO_H
#define __STM32_GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32c0xx_hal_gpio.h"
#include "gpio_interface.h"
#include "stm32x0_gpio_mapping.hpp"

#ifdef __cplusplus
namespace stm32
{
class STM32Gpio : public GpioInterface
{
public:
	enum class Port : uint8_t
	{
		A, B, C, D, F  // port E is  non-existent
	};

	enum class Mode
	{
		/*!< Input Floating Mode                                                 */
		Input = GPIO_MODE_INPUT,
		/*!< Output Push Pull Mode                                               */
		Output_Push_Pull = GPIO_MODE_OUTPUT_PP,
		/*!< Output Open Drain Mode                                              */
		Output_Open_Drain = GPIO_MODE_OUTPUT_OD,
		/*!< Alternate Function Push Pull Mode                                   */
		Alt_Function_Push_Pull = GPIO_MODE_AF_PP,
		/*!< Alternate Function Open Drain Mode                                  */
		Alt_Function_Open_Drain = GPIO_MODE_AF_OD,
		/*!< Analog Mode                                                         */
		Analog = GPIO_MODE_ANALOG,
		/*!< External Interrupt Mode with Rising edge trigger detection          */
		Interrupt_Rising = GPIO_MODE_IT_RISING,
		/*!< External Interrupt Mode with Falling edge trigger detection         */
		Interrupt_Falling = GPIO_MODE_IT_FALLING,
		/*!< External Interrupt Mode with Rising/Falling edge trigger detection  */
		Interrupt_Rising_Falling = GPIO_MODE_IT_RISING_FALLING,
		/*!< External Event Mode with Rising edge trigger detection              */
		Event_Rising = GPIO_MODE_EVT_RISING,
		/*!< External Event Mode with Falling edge trigger detection             */
		Event_Falling = GPIO_MODE_EVT_FALLING,
		/*!< External Event Mode with Rising/Falling edge trigger detection      */
		Event_Rising_Falling = GPIO_MODE_EVT_RISING_FALLING,
	};

	enum class Pull
	{
		None = GPIO_NOPULL,      /*!< No Pull-up or Pull-down activation  */
		Up = GPIO_PULLUP,        /*!< Pull-up activation                  */
		Down = GPIO_PULLDOWN,    /*!< Pull-down activation                */
	};

	enum class Speed
	{
		Low = GPIO_SPEED_FREQ_LOW,               /*!< Low speed       */
		Medium = GPIO_SPEED_FREQ_MEDIUM,         /*!< Medium speed    */
		High = GPIO_SPEED_FREQ_HIGH,             /*!< High speed      */
		Very_High = GPIO_SPEED_FREQ_VERY_HIGH,   /*!< Very high speed */
	};

	STM32Gpio(
		uint16_t pin,
	    Port port,
	    Mode mode,
	    Pull pull,
	    Speed speed
	);

	~STM32Gpio() = default;

	[[nodiscard]] uint16_t getPin() const;
	[[nodiscard]] Port getPort() const;
	[[nodiscard]] GPIO_TypeDef *get_GPIO_TypeDef_port() const;
	[[nodiscard]] Mode getMode() const;
	[[nodiscard]] Pull getPull() const;
	[[nodiscard]] Speed getSpeed() const;

	[[nodiscard]] bool readPin() const final;
	void writePin(bool value) final;
	void togglePin() final;
	bool lockPin() final;

private:
	uint16_t _pin;
	Port _port;
	Mode _mode;
	Pull _pull;
	Speed _speed;

	void clock_enable(Port port)
	{
		switch (port)
		{
			case Port::A: __HAL_RCC_GPIOA_CLK_ENABLE(); break;
			case Port::B: __HAL_RCC_GPIOB_CLK_ENABLE(); break;
			case Port::C: __HAL_RCC_GPIOC_CLK_ENABLE(); break;
			case Port::D: __HAL_RCC_GPIOD_CLK_ENABLE(); break;
//	            case Port::E: __HAL_RCC_GPIOE_CLK_ENABLE(); break;
			case Port::F: __HAL_RCC_GPIOF_CLK_ENABLE(); break;
		}
	}
};

} /* namespace */

#endif /* __cplusplus class */

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* __STM32_GPIO_H */
