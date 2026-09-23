/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
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

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins as
        * Analog
        * Input
        * Output
        * EVENT_OUT
        * EXTI
*/
//void MX_GPIO_Init(void)
//{
//
//  GPIO_InitTypeDef GPIO_InitStruct = {0};
//
//  /* GPIO Ports Clock Enable */
//  __HAL_RCC_GPIOC_CLK_ENABLE();
//  __HAL_RCC_GPIOH_CLK_ENABLE();
//  __HAL_RCC_GPIOA_CLK_ENABLE();
//  __HAL_RCC_GPIOB_CLK_ENABLE();
//
//  /*Configure GPIO pin Output Level */
//  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
//
//  /*Configure GPIO pin : B1_Pin */
//  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
//  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);
//
//  /*Configure GPIO pin : LD2_Pin */
//  GPIO_InitStruct.Pin = LD2_Pin;
//  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//  GPIO_InitStruct.Pull = GPIO_NOPULL;
//  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
//  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);
//
//}

/* USER CODE BEGIN 2 */
void my_gpio_init(GPIO_TypeDef *GPIOx, uint16_t gpio_pin,
                                       my_gpio_mode_e gpio_mode,
                                       uint16_t gpio_output_type, //TODO: Gotta be a better way to do this
                                       my_gpio_speed_e gpio_speed,
                                       my_gpio_resistor_e gpio_resistor) // TODO: Alternate function, interrupts; lock?
{
    // Clock Enable
    uint32_t gpio_port = (uint32_t) GPIOx & (7U << 10U); // Every GPIO port is differentiated only by bits 11-13
    RCC ->AHB1ENR |= 1U << (GPIO_Port >> 10U);

    uint16_t pin_number = my_gpio_get_pin_number(gpio_pin);

    // Set Pin Mode
    GPIOx ->MODER &= ~(3U << (pin_number * 2));
    GPIOx ->MODER |= gpio_mode << (pin_number * 2);

    // Set Output Type
    GPIOx ->OTYPER &= ~(1U << pin_number);
    GPIOx ->OTYPER |= gpio_output_type << pin_number;

    // Set Pin Speed
    GPIOx ->OSPEEDR &= ~(3U << (pin_number * 2));
    GPIOx ->OSPEED |= gpio_speed << (pin_number * 2);

    // Set Resistor Type (PU/PD)
    GPIOx ->PUPDR &= ~(3U << (pin_number * 2));
    GPIOx ->PUPDR |= gpio_resistor << (pin_number * 2);

}

void my_gpio_write_pin(GPIO_TypeDef *GPIOx, uint16_t gpio_pin, uint8_t gpio_pin_state)
{
    uint16_t pin_number = my_gpio_get_pin_number(gpio_pin);
    if (gpio_pin_state == my_gpio_pin_reset)
    {
        GPIOx ->BSRR = 1U << (16U + pin_number);
    }
    else
    {
        GPIOx ->BSRR = 1U << pin_number;
    }
}

GPIO_PinState my_gpio_read_pin(GPIO_TypeDef *GPIOx, uint16_t gpio_pin)
{
    uint16_t pin_number = my_gpio_get_pin_number(gpio_pin);
    if (GPIOx ->IDR & (1U << pin_number) == 0)
    {
        return GPIO_PIN_RESET;
    }
    else
    {
        return GPIO_PIN_SET;
    }
}

void my_gpio_toggle_pin(GPIO_TypeDef GPIOx, uint16_t gpio_pin)
{
    uint16_t pin_number = my_gpio_get_pin_number(gpio_pin);
    GPIOx ->ODR ^= (1U << pin_number);
}

uint16_t my_gpio_get_pin_number(uint16_t gpio_pin)
{
    uint16_t curr_bit = gpio_pin;
    uint8_t pin_number = 0U;
    while (curr_bit != 1U)
    {
        curr_bit >>= 1U;
        pin_number++;
    }
    return pin_number;
}
/* USER CODE END 2 */
