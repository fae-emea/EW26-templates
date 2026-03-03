#include <arm_itm.h>

#include "tx_api.h"
#include "tx_thread.h"

#include "app_itm.h"

USHORT queueCount = 0U;
USHORT semaphoreCount = 0U;

/*
 * ThreadX has built-in instrumentation that can be used with ITM
 * Build TX with the TX_EXECUTION_PROFILE_ENABLE Assembly preprocessor symbol
 */

/**
  * @brief  Called when the current thread starts executing
  */
__root void _tx_execution_thread_enter(void)
{
    TX_THREAD * thread_ptr;

    thread_ptr = _tx_thread_current_ptr;
    ITM_EVENT8(ITM_THREADID_CHANNEL, (UCHAR)thread_ptr->tx_thread_ux_seq);
}

/**
  * @brief  Called when the current thread is no longer executing
  */
__root void _tx_execution_thread_exit(void)
{
     ITM_EVENT8(ITM_THREADID_CHANNEL, 0U);
}

/**
  * @brief  Update Data Trace ITM channel
  */
void itmDataTrace(unsigned int * data)
{
  ITM_EVENT32(ITM_DATA_TRACE_CHANNEL, *data);
}

/**
  * @brief  Increments the Queue Counter in the ITM channel
  */
void itmQueueIncrement()
{
  queueCount++;
  ITM_EVENT16(ITM_QUEUE_CHANNEL, queueCount);
}

/**
  * @brief  Decrements the Queue Counter in the ITM channel
  */
void itmQueueDecrement()
{
  if (queueCount) queueCount--;
  ITM_EVENT16(ITM_QUEUE_CHANNEL, queueCount);
}

/**
  * @brief  Increments the Semaphore Counter in the ITM channel
  */
void itmSemaphoreIncrement()
{
  semaphoreCount++;
  ITM_EVENT16(ITM_SEMAPHORE_CHANNEL, semaphoreCount);
}

/**
  * @brief  Decrements the Semaphore Counter in the ITM channel
  */
void itmSemaphoreDecrement()
{
  if (semaphoreCount) semaphoreCount--;
  ITM_EVENT16(ITM_SEMAPHORE_CHANNEL, semaphoreCount);
}
