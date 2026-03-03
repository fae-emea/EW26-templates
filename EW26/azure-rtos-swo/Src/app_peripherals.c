#include "app_peripherals.h"

/**
  * @brief  Start Timer
  */
void startTimer(TIM_HandleTypeDef *htim)
{
  if (HAL_OK != HAL_TIM_Base_Start(htim))
  {
    while(1);
  }
}

/**
  * @brief  Stop Timer
  */
void stopTimer(TIM_HandleTypeDef *htim)
{
  if (HAL_OK != HAL_TIM_Base_Stop(htim))
  {
    while(1);
  }
}

/**
  * @brief  Start DAC
  */
void startDAC(DAC_HandleTypeDef *hdac, uint32_t *data, uint16_t length)
{
  if (HAL_OK != HAL_DAC_Start_DMA(hdac, DAC_CHANNEL_2, data, length, DAC_ALIGN_12B_R))
  {
    while(1);
  }
}

/**
  * @brief  Stop Timer
  */
void stopDAC(DAC_HandleTypeDef *hdac)
{
  if (HAL_OK != HAL_DAC_Stop_DMA(hdac, 2))
  {
    while(1);
  }
}

/**
  * @brief  Start ADC
  */
void startADC(ADC_HandleTypeDef *hadc)
{
  HAL_ADC_Start_IT(hadc);
}


/**
  * @brief  Stop ADC
  */
void stopADC(ADC_HandleTypeDef *hadc)
{
  HAL_ADC_Stop_IT(hadc);
}

