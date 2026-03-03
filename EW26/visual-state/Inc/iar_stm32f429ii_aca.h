//*****************************************************************************
//
// Copyright (c) 2022, IAR Systems AB.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//
//*****************************************************************************

#ifndef IAR_STM32F429II_ACA__H
#define IAR_STM32F429II_ACA__H

//cstat -MISRAC++2008*                                                                             // Disable MISRA-C++2008 in C header

#include <stdint.h>
#include <stdbool.h>
#include <intrinsics.h>

//cstat -MISRAC2012*                                                                               // suppress warnings from provided header files
#include "stm32f4xx_hal.h"
#include "gpio.h"
//cstat +MISRAC2012*

#define LEDn                           8U

// Push-buttons
#define BUT1_Pin                       GPIO_PIN_0
#define BUT1_GPIO_Port                 GPIOA
#define BUT2_Pin                       GPIO_PIN_13
#define BUT2_GPIO_Port GPIOC
#define BUT3_Pin                       GPIO_PIN_9
#define BUT3_GPIO_Port                 GPIOG

// LEDs
#define LED1_Pin                       GPIO_PIN_4
#define LED1_GPIO_Port                 GPIOA
#define LED2_Pin                       GPIO_PIN_4
#define LED2_GPIO_Port                 GPIOD
#define LED3_Pin                       GPIO_PIN_5
#define LED3_GPIO_Port                 GPIOD
#define LED4_Pin                       GPIO_PIN_6
#define LED4_GPIO_Port                 GPIOD
#define LED5_Pin                       GPIO_PIN_7
#define LED5_GPIO_Port                 GPIOD
#define LED6_Pin                       GPIO_PIN_11
#define LED6_GPIO_Port                 GPIOD
#define LED7_Pin                       GPIO_PIN_12
#define LED7_GPIO_Port                 GPIOD
#define LED8_Pin                       GPIO_PIN_13
#define LED8_GPIO_Port                 GPIOD

// LED TypeDef
typedef uint8_t LED_TypeDef_t;
#define LED1                           ((Button_TypeDef_t) 0x0U)
#define LED2                           ((Button_TypeDef_t) 0x1U)
#define LED3                           ((Button_TypeDef_t) 0x2U)
#define LED4                           ((Button_TypeDef_t) 0x3U)
#define LED5                           ((Button_TypeDef_t) 0x4U)
#define LED6                           ((Button_TypeDef_t) 0x5U)
#define LED7                           ((Button_TypeDef_t) 0x6U)
#define LED8                           ((Button_TypeDef_t) 0x7U)

// Button TypeDef
typedef uint8_t Button_TypeDef_t;
#define BUT_NONE                       ((Button_TypeDef_t) 0x0U)
#define BUT1                           ((Button_TypeDef_t) 0x1U)
#define BUT2                           ((Button_TypeDef_t) 0x2U)
#define BUT3                           ((Button_TypeDef_t) 0x4U)

// Variable declaration
extern GPIO_TypeDef*  GPIO_PORT[LEDn];
extern const uint16_t GPIO_PIN[LEDn];

// Function declaration
void ACA_BoardInit(void);
void ACA_LEDOn(LED_TypeDef_t Led);
void ACA_LEDOff(LED_TypeDef_t Led);
void SystemClock_Config(void);

//cstat +MISRAC++2008*

#endif // IAR_STM32F429II_ACA__H