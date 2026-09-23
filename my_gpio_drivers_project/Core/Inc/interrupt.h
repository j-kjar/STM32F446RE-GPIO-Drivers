#ifndef __INTERRUPT_H__
#define __INTERRUPT_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
#include "gpio.h"

typedef enum
{
    my_exti_rising_trigger,
    my_exti_falling_trigger,
    my_exti_rising_falling_trigger
} my_exti_trigger_e;

void my_interrupt_enable(IRQn_Type);
void my_interrupt_init_pin(GPIO_TypeDef *GPIOx, uint16_t gpio_pin, my_exti_trigger_e trigger_type);




#ifdef __cplusplus
}
#endif
#endif
