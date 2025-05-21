#include "systick.hpp"
#include "rcc.hpp"
#include "stm32c0xx.h"
#include "core_cm0plus.h"
//#include "FreeRTOS.h"
//#include "task.h"
#include "FreeRTOSConfig.h"

using namespace periph;

namespace {
    // Tick-Zähler wie in FreeRTOS (1 Takt = 1 ms bei configTICK_RATE_HZ = 1000)
    static volatile TickType_t systick_counter = 0;
}

// Handler für den SysTick Interrupt
extern "C" void SysTick_Handler(void)
{
    systick_counter = systick_counter + 1;
}

void systick::init()
{
    uint32_t systick_freq = rcc::frequency(rcc::clk_source::ahb);
    SysTick_Config(systick_freq / configTICK_RATE_HZ);
}

TickType_t xTaskGetTickCount()
{
    return systick_counter;
}

std::chrono::microseconds systick::get()
{
    return std::chrono::milliseconds(xTaskGetTickCount());
}

std::chrono::microseconds systick::get_past(std::chrono::microseconds timestamp)
{
    return std::chrono::milliseconds(xTaskGetTickCount()) - timestamp;
}

void systick::delay(uint32_t delay_ms)
{
    auto start = xTaskGetTickCount();

    while((xTaskGetTickCount() - start) < delay_ms)
    {

    }
}

/* Implemented in FreeRTOS/port.c
extern "C" void SysTick_Handler(void)
{
    systick_cnt++;
}
*/
