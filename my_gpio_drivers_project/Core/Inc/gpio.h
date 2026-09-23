/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.h
  * @brief   This file contains all the function prototypes for
  *          the gpio.c file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GPIO_H__
#define __GPIO_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */
#define my_gpio_pin_set 1U
#define my_gpio_pin_reset 0U

typedef enum
{
    my_gpio_mode_input,
    my_gpio_mode_output,
    my_gpio_mode_alternate,
    my_gpio_mode_analog
} my_gpio_mode_e;

typedef enum
{
    my_gpio_speed_low,
    my_gpio_speed_medium,
    my_gpio_speed_fast,
    my_gpio_speed_high
} my_gpio_speed_e;

typedef enum
{
    my_gpio_resistor_none,
    my_gpio_resistor_pu,
    my_gpio_resistor_pd
} my_gpio_resistor_e;
/* USER CODE END Private defines */

//void MX_GPIO_Init(void);

/* USER CODE BEGIN Prototypes */
void my_gpio_init(GPIO_TypeDef *GPIOx, uint16_t gpio_pin,
                                       my_gpio_mode_e gpio_mode,
                                       uint16_t gpio_output_type,
                                       my_gpio_speed_e gpio_speed,
                                       my_gpio_resistor_e gpio_resistor);
void my_gpio_write_pin(GPIO_TypeDef *GPIOx, uint16_t gpio_pin, uint8_t gpio_pin_state);
GPIO_PinState my_gpio_read_pin(GPIO_TypeDef *GPIOx, uint16_t gpio_pin);
void my_gpio_toggle_pin(GPIO_TypeDef GPIOx, uint16_t gpio_pin);
uint16_t my_gpio_get_pin_number(uint16_t gpio_pin);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ GPIO_H__ */

