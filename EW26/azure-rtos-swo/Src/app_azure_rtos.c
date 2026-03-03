
/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    app_azure_rtos.c
  * @author  MCD Application Team
  * @brief   azure_rtos application implementation file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2021 STMicroelectronics.
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

#include "app_azure_rtos.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define THREAD_DEFAULT_STACK_SIZE 512
#define ADC_QUEUE_SIZE            100
#define BLOCK_POOL_SIZE           100
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN TX_Pool_Buffer */
/* USER CODE END TX_Pool_Buffer */
static UCHAR tx_byte_pool_buffer[TX_APP_MEM_POOL_SIZE];
static TX_BYTE_POOL tx_app_byte_pool;

/* USER CODE BEGIN PV */
TX_THREAD thread_adc;
TX_THREAD thread_button;
TX_THREAD thread_led;

extern void thread_adc_entry(ULONG);
extern void thread_button_entry(ULONG);
extern void thread_led_entry(ULONG);

TX_SEMAPHORE semButton1ON;
TX_SEMAPHORE semButton2ON;
TX_SEMAPHORE semButton3ON;
TX_SEMAPHORE semButton1OFF;
TX_SEMAPHORE semButton2OFF;
TX_SEMAPHORE semButton3OFF;

TX_QUEUE     queueADC;

TX_BLOCK_POOL block_pool_0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/**
  * @brief  Define the initial system.
  * @param  first_unused_memory : Pointer to the first unused memory
  * @retval None
  */
VOID tx_application_define(VOID *first_unused_memory)
{
  /* USER CODE BEGIN  tx_application_define */

  /* USER CODE END  tx_application_define */

  VOID *memory_ptr;

  if (tx_byte_pool_create(&tx_app_byte_pool, "Tx App memory pool", tx_byte_pool_buffer, TX_APP_MEM_POOL_SIZE) != TX_SUCCESS)
  {
    /* USER CODE BEGIN TX_Byte_Pool_Error */

    /* USER CODE END TX_Byte_Pool_Error */
  }
  else
  {
    /* USER CODE BEGIN TX_Byte_Pool_Success */
    /* USER CODE END TX_Byte_Pool_Success */

    memory_ptr = (VOID *)&tx_app_byte_pool;

    if (App_ThreadX_Init(memory_ptr) != TX_SUCCESS)
    {
      /* USER CODE BEGIN  App_ThreadX_Init_Error */
      while(1);
      /* USER CODE END  App_ThreadX_Init_Error */
    }

    /* USER CODE BEGIN  App_ThreadX_Init_Success */
    
    //! Thread ADC - Allocate the stack and create
    //! -------------------------------------------
    tx_byte_allocate(&tx_app_byte_pool, (VOID **) &memory_ptr, THREAD_DEFAULT_STACK_SIZE, TX_NO_WAIT);
    tx_thread_create(&thread_adc, "ADC Thread", thread_adc_entry, 0,
                     memory_ptr, THREAD_DEFAULT_STACK_SIZE, 
                     16, 16, TX_NO_TIME_SLICE, TX_AUTO_START);
    thread_adc.tx_thread_ux_seq = 1;
    /* Allocate and create the message queue */
    tx_byte_allocate(&tx_app_byte_pool, (VOID **) &memory_ptr, ADC_QUEUE_SIZE * sizeof(ULONG), TX_NO_WAIT);
    tx_queue_create(&queueADC, "ADC Queue", TX_1_ULONG, memory_ptr, ADC_QUEUE_SIZE * sizeof(ULONG));
    
    
    //! Thread BUTTON - Allocate the stack and create
    //! -------------------------------------------  
    tx_byte_allocate(&tx_app_byte_pool, (VOID **) &memory_ptr, THREAD_DEFAULT_STACK_SIZE, TX_NO_WAIT);
    tx_thread_create(&thread_button, "BUTTON Thread", thread_button_entry, 0,
                     memory_ptr, THREAD_DEFAULT_STACK_SIZE, 
                     15, 15, TX_NO_TIME_SLICE, TX_AUTO_START);
    thread_button.tx_thread_ux_seq = 2;
    
    tx_semaphore_create(&semButton1ON,  "B1 ON",  1);
    tx_semaphore_create(&semButton2ON,  "B2 ON",  1);
    tx_semaphore_create(&semButton3ON,  "B3 ON",  1);
    tx_semaphore_create(&semButton1OFF, "B1 OFF", 1);
    tx_semaphore_create(&semButton2OFF, "B2 OFF", 1);
    tx_semaphore_create(&semButton3OFF, "B3 OFF", 1);
    
    
    //! Thread LED - Allocate the stack and create
    //! -------------------------------------------
    tx_byte_allocate(&tx_app_byte_pool, (VOID **) &memory_ptr, THREAD_DEFAULT_STACK_SIZE, TX_NO_WAIT);
    tx_thread_create(&thread_led, "LED Thread", thread_led_entry, 0,
                     memory_ptr, THREAD_DEFAULT_STACK_SIZE, 
                     14, 14, TX_NO_TIME_SLICE, TX_AUTO_START);
    thread_led.tx_thread_ux_seq = 3;
    
    //! Create a small memory block pool
    tx_byte_allocate(&tx_app_byte_pool, (VOID **) &memory_ptr, BLOCK_POOL_SIZE, TX_NO_WAIT);
    tx_block_pool_create(&block_pool_0, "Block Pool 0", sizeof(ULONG), memory_ptr, BLOCK_POOL_SIZE);
    tx_block_allocate(&block_pool_0, (VOID **) &memory_ptr, TX_NO_WAIT);
    
    //! Release the block back to the pool
    tx_block_release(memory_ptr);

    /* USER CODE END  App_ThreadX_Init_Success */

  }

}

/* USER CODE BEGIN  0 */

/* USER CODE END  0 */
