#include "tx_api.h"

#include "app_itm.h"
#include "app_peripherals.h"
#include "app_waveform.h"

#define ADC_AVERAGE_QUANTIZATION (16U)

extern ADC_HandleTypeDef hadc1;
extern DAC_HandleTypeDef hdac;
extern TIM_HandleTypeDef htim2;

extern TX_QUEUE queueADC;

UINT averageADC = 0, traceAverage, lastVolume;

/**
  * @brief  ADC thread entry point
  */
void thread_adc_entry(ULONG thread_input)
{
  UINT queueValue = 0, index = 0, resultsADC[ADC_AVERAGE_QUANTIZATION] = { 0 }; 
  
  tx_thread_sleep(3);
  startADC(&hadc1);
  startTimer(&htim2);
  
  while (1)
  {
    if (TX_SUCCESS == tx_queue_receive(&queueADC,&queueValue, TX_WAIT_FOREVER))
    {
      itmQueueDecrement();
      resultsADC[index++] = queueValue;
      if (ADC_AVERAGE_QUANTIZATION == index)
      {
        index = 0U;
      }
      averageADC = 0;
      for (int x = 0; x < ADC_AVERAGE_QUANTIZATION; x++)
      {
        averageADC += resultsADC[x];
      }
      averageADC /= ADC_AVERAGE_QUANTIZATION;
      traceAverage = averageADC;
      
      if (abs((int)averageADC - (int)lastVolume) > VOLUME_THRESHOLD)
      {
        itmDataTrace(&averageADC);
        scaleWave(averageADC);
        lastVolume = averageADC;
        itmDataTrace(&traceAverage);
      }
    }
  }
}

/**
  * @brief  Interrupt handling for the ADC
  */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
  UINT ADCout;  
  
  ADCout = HAL_ADC_GetValue(hadc);
  tx_queue_send(&queueADC, &ADCout, 0);
  itmQueueIncrement();
}
