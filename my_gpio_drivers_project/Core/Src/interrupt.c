#include "interrupt.h"

void my_interrupt_enable(IRQn_Type)
{
    NVIC ->ISER[IRQN_Type >> 5U] = 1U & 0x1FU; // Bitwise division and modulus division by a power of 2.
}

void  my_interrupt_init_pin(GPIO_TypeDef *GPIOx, uint16_t gpio_pin, my_exti_trigger_e trigger_type)
{
    uint32_t gpio_port = (uint32_t) GPIOx & (7U << 10U); // Every GPIO port is differentiated only by bits 11-13
    gpio_port >>= 10U;
    uint16_t pin_number = my_gpio_get_pin_number(gpio_pin);

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

    // Enable SYSCFG Controller Clock
    RCC ->APB2ENR |= 1U << 14U;

    // Enable SYSCFG_EXTI Mux
    SYSCFG ->EXTICR[pin_number >> 2U] &= ~(0xF << ((pin_number & 3U) * 4U)); // Bitwise division and modulus division by power of 2
    SYSCFG ->EXTICR[pin_number >> 2U] |= (gpio_port << ((pin_number & 3U) * 4U));
}
