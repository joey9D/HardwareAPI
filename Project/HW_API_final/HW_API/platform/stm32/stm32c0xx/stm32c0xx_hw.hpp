/*
 * stm32c0_hw.hpp
 *
 *  Created on: Jul 10, 2025
 *      Author: jan.kristel
 */

#ifndef __STM32C0XX_HW_HPP
#define __STM32C0XX_HW_HPP

#ifdef __cplusplus
#include <cstdint>
#else
#include <stdint.h>
#endif

#include "hw_interface.hpp"

#ifdef __cplusplus

class Stm32c0xx_hw : public HardwareInterface
{
public:
	void init_sys() override ;
	void init_clock() override ;
	void delay(uint32_t ms) override;

	void initAllPins() override;
private:
	PinConfig_t _config;
};

#endif /* __cplusplus class */

#endif /* STM32_STM32C0_STM32C0_HW_HPP_ */
