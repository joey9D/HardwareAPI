/*
 * hw_enum_classes.hpp
 *
 *  Created on: Jul 10, 2025
 *      Author: jan.kristel
 */

#ifndef CORE_HW_ENUM_CLASSES_HPP_
#define CORE_HW_ENUM_CLASSES_HPP_

#include "stm32x0_gpio_mapping.hpp"

#ifdef __cplusplus

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

	enum class HAL_State
	{
		  OK = 0x00U,
		  Error = 0x01U,
		  Busy = 0x02U,
		  Timeout = 0x03U
	};

#endif /* __cplusplus */


#endif /* CORE_HW_ENUM_CLASSES_HPP_ */
