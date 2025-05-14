#include <cassert>
#include "periph/exti_stm32c0.hpp"
#include "gpio_hw_mapping.hpp"
#include "stm32c0xx.h"
#include "core_cm0plus.h"

using namespace periph;

static exti_stm32c0 *obj_list[gpio_hw_mapping::pins];

constexpr IRQn_Type irqn[gpio_hw_mapping::pins] =
{
    EXTI0_1_IRQn, EXTI0_1_IRQn, EXTI2_3_IRQn, EXTI2_3_IRQn, EXTI4_15_IRQn,
    EXTI4_15_IRQn, EXTI4_15_IRQn, EXTI4_15_IRQn, EXTI4_15_IRQn, EXTI4_15_IRQn,
    EXTI4_15_IRQn, EXTI4_15_IRQn, EXTI4_15_IRQn, EXTI4_15_IRQn, EXTI4_15_IRQn,
    EXTI4_15_IRQn
};

exti_stm32c0::exti_stm32c0(gpio_stm32c0 &gpio, enum trigger trigger):
    gpio(gpio),
    _trigger(trigger)
{
    assert(gpio.mode() == gpio::mode::digital_input);

    // Enable clock
    RCC->APBENR2 |= RCC_APBENR2_SYSCFGEN;

    uint8_t pin = gpio.pin();

    // Setup EXTI line source
    uint8_t exti_offset = (pin % EXTI_EXTICR1_EXTI1_Pos) * EXTI_EXTICR1_EXTI1_Pos;
    EXTI->EXTICR[pin / EXTI_EXTICR1_EXTI1_Pos] &= ~(EXTI_EXTICR1_EXTI0 << exti_offset);
    EXTI->EXTICR[pin / EXTI_EXTICR1_EXTI1_Pos] |= static_cast<uint8_t>(gpio.port()) << exti_offset;

    uint32_t line_bit = 1 << pin;
    // Setup EXTI mask regs
    EXTI->EMR1 &= ~line_bit;
    EXTI->IMR1 &= ~line_bit;

    // Setup EXTI trigger
    EXTI->RTSR1 |= line_bit;
    EXTI->FTSR1 |= line_bit;
    if(_trigger == trigger::rising)
    {
        EXTI->FTSR1 &= ~line_bit;
    }
    else if(_trigger == trigger::falling)
    {
        EXTI->RTSR1 &= ~line_bit;
    }

    obj_list[pin] = this;

    NVIC_ClearPendingIRQ(irqn[pin]);
    NVIC_SetPriority(irqn[pin], 2);
    NVIC_EnableIRQ(irqn[pin]);
}

exti_stm32c0::~exti_stm32c0()
{
    uint8_t pin = gpio.pin();

    NVIC_DisableIRQ(irqn[pin]);
    EXTI->IMR1 &= ~(1 << pin);

    uint8_t exti_offset = (pin % EXTI_EXTICR1_EXTI1_Pos) * EXTI_EXTICR1_EXTI1_Pos;
    EXTI->EXTICR[pin / EXTI_EXTICR1_EXTI1_Pos] &= ~(EXTI_EXTICR1_EXTI0 << exti_offset);

    obj_list[pin] = nullptr;
}

void exti_stm32c0::set_callback(std::function<void()> on_interrupt)
{
    this->on_interrupt = std::move(on_interrupt);
}

void exti_stm32c0::enable()
{
    assert(on_interrupt);

    uint8_t pin_bit = 1 << gpio.pin();

    //EXTI->PR |= 1 << pin;
    EXTI->RPR1 = pin_bit;
    EXTI->FPR1 = pin_bit;

    EXTI->IMR1 |= pin_bit;

    NVIC_ClearPendingIRQ(irqn[gpio.pin()]);
}

void exti_stm32c0::disable()
{
    EXTI->IMR1 &= ~(1 << gpio.pin());
}

void exti_stm32c0::trigger(enum trigger trigger)
{
    _trigger = trigger;
    uint32_t line_bit = 1 << gpio.pin();

    EXTI->RTSR1 |= line_bit;
    EXTI->FTSR1 |= line_bit;
    if(_trigger == trigger::rising)
    {
        EXTI->FTSR1 &= ~line_bit;
    }
    else if(_trigger == trigger::falling)
    {
        EXTI->RTSR1 &= ~line_bit;
    }
}

extern "C" void exti_irq_hndlr(periph::exti_stm32c0 *obj)
{
    //EXTI->PR = 1 << obj->gpio.pin();
    uint32_t pin_bit = 1 << obj->gpio.pin();

    EXTI->RPR1 = pin_bit;
    EXTI->FPR1 = pin_bit;

    if(obj->on_interrupt)
    {
        obj->on_interrupt();
    }
}

extern "C" void EXTI0_1_IRQHandler(void)
{
    uint32_t pending_r = EXTI->RPR1;
    uint32_t pending_f = EXTI->FPR1;

    if(pending_r & (1 << 0) || pending_f & (1 << 0))
    {
        exti_irq_hndlr(obj_list[0]);
    }
    else if(pending_r & (1 << 1) || pending_f & (1 << 1))
    {
        exti_irq_hndlr(obj_list[1]);
    }
}

extern "C" void EXTI2_3_IRQHandler(void)
{
    uint32_t pending_r = EXTI->RPR1;
    uint32_t pending_f = EXTI->FPR1;

    if(pending_r & (1 << 2) || pending_f & (1 << 2))
    {
        exti_irq_hndlr(obj_list[2]);
    }
    else if(pending_r & (1 << 3) || pending_f & (1 << 3))
    {
        exti_irq_hndlr(obj_list[3]);
    }
}

extern "C" void EXTI4_15_IRQHandler(void)
{
    uint32_t pending_r = EXTI->RPR1;
    uint32_t pending_f = EXTI->FPR1;
    uint32_t pending = pending_r | pending_f;

    for(uint8_t i = 4; i <= 15; ++i)
    {
        if(pending & (1 << i))
        {
            exti_irq_hndlr(obj_list[i]);
            break;
        }
    }
}
