#include "tx_api.h"

#include "app_peripherals.h"

extern UINT traceAverage;

void thread_led_entry(ULONG thread_input)
{
  UINT ledDelayTicks;
  
  while (1)
  {
    ledDelayTicks = 20 - (UINT)(traceAverage / 0x100);

    LED1_OFF();
    tx_thread_sleep(ledDelayTicks);
    
    LED2_OFF();
    tx_thread_sleep(ledDelayTicks);
    
    LED3_OFF();
    tx_thread_sleep(ledDelayTicks);
    
    LED4_OFF();
    tx_thread_sleep(ledDelayTicks);
    
    LED5_OFF();
    tx_thread_sleep(ledDelayTicks);
    
    LED1_ON();
    LED2_ON();
    LED3_ON();
    LED4_ON();
    LED5_ON();
    tx_thread_sleep(ledDelayTicks);
  }
}
