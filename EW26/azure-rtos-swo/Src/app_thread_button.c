#include "tx_api.h"

#include "app_itm.h"
#include "app_peripherals.h"
#include "app_waveform.h"

#include <stdbool.h>
#include <stdio.h>

extern TX_THREAD thread_led;

extern TX_SEMAPHORE semButton1ON;
extern TX_SEMAPHORE semButton2ON;
extern TX_SEMAPHORE semButton3ON;
extern TX_SEMAPHORE semButton1OFF;
extern TX_SEMAPHORE semButton2OFF;
extern TX_SEMAPHORE semButton3OFF;

extern DAC_HandleTypeDef hdac;
extern TIM_HandleTypeDef htim5;

extern INT averageADC;

/**
  * @brief  Button thread entry point
  */
void thread_button_entry(ULONG thread_input)
{
  bool   DAC_ON   = false;
  bool   LEDs_ON  = true;
  wave_t waveform = SINE;
  
  tx_semaphore_get(&semButton1ON, 0);
  tx_semaphore_get(&semButton2ON, 0);
  tx_semaphore_get(&semButton3ON, 0);
  tx_semaphore_get(&semButton1OFF, 0);
  tx_semaphore_get(&semButton2OFF, 0);
  tx_semaphore_get(&semButton3OFF, 0);
  
  makeWave(waveform);
  scaleWave(averageADC);
  
  while (1)
  {
    /* Button 1 - Audio output */
    if (TX_SUCCESS == tx_semaphore_get(&semButton1ON, 1))
    {
      LED7_ON();
      itmSemaphoreDecrement();
      if (!DAC_ON)
      {
        startDAC(&hdac, (uint32_t*)gScaledWave, WAVELENGTH);
        startTimer(&htim5);
        DAC_ON = true;
      } else {
        stopTimer(&htim5);
        stopDAC(&hdac);
        DAC_ON = false;
      }
    }
    if (TX_SUCCESS == tx_semaphore_get(&semButton1OFF, 1))
    {
      LED7_OFF();
      itmSemaphoreDecrement();
    }
    
    /* Button 2 - Change waveform */
    if (TX_SUCCESS == tx_semaphore_get(&semButton2ON, 1))
    {
      LED8_ON();
      itmSemaphoreDecrement();
      if (++waveform > TRIANGLE) waveform = SINE;
      makeWave(waveform);
      scaleWave(averageADC);
    }
    if (TX_SUCCESS == tx_semaphore_get(&semButton2OFF, 1))
    {
      LED8_OFF();
      itmSemaphoreDecrement();
    }
    
    /* Button 3 - suspend/resume LEDs thread */
    if (TX_SUCCESS == tx_semaphore_get(&semButton3ON, 1))
    {
      LED6_ON();
      itmSemaphoreDecrement();
      if (LEDs_ON)
      {
        LEDs_ON = false;
        tx_thread_suspend(&thread_led);
        LED_APP_OFF();
      } else {
        LEDs_ON = true;
        tx_thread_resume(&thread_led);
      }
    }
    if (TX_SUCCESS == tx_semaphore_get(&semButton3OFF, 1))
    {
      LED6_OFF();
      itmSemaphoreDecrement();
    }
    tx_thread_sleep(1);
  }
}


/**
  * @brief  Interrupt handling for the push-buttons
  */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  switch (GPIO_Pin)
  {
  case BUT1_Pin:
    if (GPIO_PIN_SET == HAL_GPIO_ReadPin(BUT1_GPIO_Port, BUT1_Pin))
    {
      tx_semaphore_put(&semButton1OFF);
    } else {
      tx_semaphore_put(&semButton1ON);
    }
    break;
  case BUT2_Pin:
    if (GPIO_PIN_SET == HAL_GPIO_ReadPin(BUT2_GPIO_Port, BUT2_Pin))
    {
      tx_semaphore_put(&semButton2OFF);
    } else {
      tx_semaphore_put(&semButton2ON);
    }
    break;
  case BUT3_Pin:
    if (GPIO_PIN_SET == HAL_GPIO_ReadPin(BUT3_GPIO_Port, BUT3_Pin))
    {
      tx_semaphore_put(&semButton3OFF);
    } else {
      tx_semaphore_put(&semButton3ON);
    }
    break;
  default:
    break;
  }
}
