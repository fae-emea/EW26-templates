#ifndef _PERIPHERALS_H_
#define _PERIPHERALS_H_

#include "main.h"
#include "stm32f4xx_hal.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define LED1_ON()    do { HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET); } while(0);
#define LED2_ON()    do { HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET); } while(0);
#define LED3_ON()    do { HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_RESET); } while(0);
#define LED4_ON()    do { HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, GPIO_PIN_RESET); } while(0);
#define LED5_ON()    do { HAL_GPIO_WritePin(LED5_GPIO_Port, LED5_Pin, GPIO_PIN_RESET); } while(0);
#define LED6_ON()    do { HAL_GPIO_WritePin(LED6_GPIO_Port, LED6_Pin, GPIO_PIN_RESET); } while(0);
#define LED7_ON()    do { HAL_GPIO_WritePin(LED7_GPIO_Port, LED7_Pin, GPIO_PIN_RESET); } while(0);
#define LED8_ON()    do { HAL_GPIO_WritePin(LED8_GPIO_Port, LED8_Pin, GPIO_PIN_RESET); } while(0);
#define LED_APP_ON() do { LED1_ON();LED2_ON();LED3_ON();LED4_ON();LED5_ON();           } while(0);


#define LED1_OFF()    do { HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET); } while(0);
#define LED2_OFF()    do { HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET); } while(0);
#define LED3_OFF()    do { HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_SET); } while(0);
#define LED4_OFF()    do { HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, GPIO_PIN_SET); } while(0);
#define LED5_OFF()    do { HAL_GPIO_WritePin(LED5_GPIO_Port, LED5_Pin, GPIO_PIN_SET); } while(0);
#define LED6_OFF()    do { HAL_GPIO_WritePin(LED6_GPIO_Port, LED6_Pin, GPIO_PIN_SET); } while(0);
#define LED7_OFF()    do { HAL_GPIO_WritePin(LED7_GPIO_Port, LED7_Pin, GPIO_PIN_SET); } while(0);
#define LED8_OFF()    do { HAL_GPIO_WritePin(LED8_GPIO_Port, LED8_Pin, GPIO_PIN_SET); } while(0);
#define LED_APP_OFF() do { LED1_OFF();LED2_OFF();LED3_OFF();LED4_OFF();LED5_OFF();    } while(0);

void startTimer(TIM_HandleTypeDef *htim);
void stopTimer(TIM_HandleTypeDef *htim);

void startDAC(DAC_HandleTypeDef *hdac, uint32_t *data, uint16_t length);
void stopDAC(DAC_HandleTypeDef *hdac);

void startADC(ADC_HandleTypeDef *hadc);
void stopADC(ADC_HandleTypeDef *hadc);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _PERIPHERALS_H_ */