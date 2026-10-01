/*
 * interrupt.h
 *
 *  Created on: Sep 26, 2026
 *      Author: Jack
 */

#ifndef __INTERRUPT_H__
#define __INTERRUPT_H__

#include "main.h"
#include "gpio.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
    my_exti_rising_trigger,
    my_exti_falling_trigger,
    my_exti_rising_falling_trigger
} my_exti_trigger_e;

void my_interrupt_enable(IRQn_Type irqn);
void my_interrupt_disable(IRQn_Type irqn);
void my_interrupt_init_pin(GPIO_TypeDef *GPIOx, uint16_t gpio_pin, my_exti_trigger_e trigger_type);
int my_interrupt_get_pending(uint16_t gpio_pin);
void my_interrupt_clear(uint16_t gpio_pin);






#ifdef __cplusplus
}
#endif
#endif
