/*
 * sys_clock_init.hpp
 *
 *  Created on: Jul 7, 2025
 *      Author: jan.kristel
 */

#ifndef __SYS_CLOCK_INIT_HPP_
#define __SYS_CLOCK_INIT_HPP_

#include "hardware_interface.hpp"
#include "stm32x0_gpio_mapping.hpp"

#ifdef __cplusplus
namespace stm32
{
class SysClock : public ::HardwareInterface
{
public:
	void Clock_Init(){};
};
} /* namespace */

#endif /* __cplusplus */



#endif /* SYS_CLOCK_INIT_HPP_ */
