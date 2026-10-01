/*
 * interrupt.c
 *
 *  Created on: Sep 26, 2026
 *      Author: Jack
 */
#include "interrupt.h"


void my_interrupt_enable(IRQn_Type irqn)
{
    NVIC ->ISER[irqn / 32U] = 1U << (irqn % 32U);
}

void my_interrupt_disable(IRQn_Type irqn)
{
    NVIC ->ICER[irqn / 32U] = 1U << (irqn % 32U);
}

void  my_interrupt_init_pin(GPIO_TypeDef *GPIOx, uint16_t gpio_pin, my_exti_trigger_e trigger_type)
{
    uint32_t gpio_port = (uint32_t) GPIOx & (7U << 10U); // Every GPIO port is differentiated only by bits 10-12
    gpio_port >>= 10U;
    uint16_t pin_number = my_gpio_get_pin_number(gpio_pin);

    // Enable SYSCFG Controller Clock
    RCC ->APB2ENR |= 1U << 14U;

    // Enable SYSCFG_EXTI Mux
    SYSCFG ->EXTICR[pin_number / 4U] &= ~(0xFU << ((pin_number % 4U) * 4U));
    SYSCFG ->EXTICR[pin_number / 4U] |= (gpio_port << ((pin_number % 4U) * 4U));

    // Unmask the interrupt
    EXTI ->IMR |= 1U << pin_number;

    // Set trigger detection type
    switch(trigger_type)
    {
    case my_exti_rising_trigger:
        EXTI ->RTSR |= 1U << pin_number;
        break;
    case my_exti_falling_trigger:
        EXTI ->FTSR |= 1U << pin_number;
        break;
    case my_exti_rising_falling_trigger:
        EXTI ->RTSR |= 1U << pin_number;
        EXTI ->FTSR |= 1U << pin_number;
        break;
    }
}

int my_interrupt_get_pending(uint16_t gpio_pin)
{
    uint16_t pin_number = my_gpio_get_pin_number(gpio_pin);
    return (EXTI ->PR >> pin_number) & 1U;
}

void my_interrupt_clear(uint16_t gpio_pin)
{
    uint16_t pin_number = my_gpio_get_pin_number(gpio_pin);
    EXTI ->PR = 1U << pin_number;
}
