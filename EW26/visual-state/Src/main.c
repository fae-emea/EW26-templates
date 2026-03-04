//*****************************************************************************
//
// Copyright (c) 2022-2026, IAR Systems AB.
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

#include "main.h"
#include "simpleEventHandler.h"

#define debounce_time_ms   10u

int main(void);

// Main function
int main(void)
{
   SEM_EVENT_TYPE eventNo;
   
   ACA_BoardInit();
   
   // Turn off LEDs
   for(LED_TypeDef_t i = LED1; i <= LED8; i++ )
   {
      ACA_LEDOff(i);
   }
   
	System1VSInitAll();
	SEQ_Initialize();
	(void)SEQ_AddEvent(SE_RESET);
   
   while (true)
   {
      if(SEQ_RetrieveEvent(&eventNo) != UCC_QUEUE_EMPTY)
		{
			if (System1VSDeduct(eventNo) != SES_OKAY)
         {
				ErrorHandler();
         }
		}
   }
}

void BUTTON_Debounce(void)
{
   static uint_fast8_t but1_counter = 0u;
   static uint_fast8_t but2_counter = 0u;
   
   if(HAL_GPIO_ReadPin(BUT1_GPIO_Port, BUT1_Pin) == GPIO_PIN_RESET)
   {
      if (but1_counter < debounce_time_ms)
      {
         but1_counter++;
      }
      else
      {
         if (but1_counter == debounce_time_ms)
         {
            but1_counter++;
            (void)SEQ_AddEvent(eButton1);
         }
      }
   }
   else
   {
      but1_counter = 0;
   }

   if(HAL_GPIO_ReadPin(BUT2_GPIO_Port, BUT2_Pin) == GPIO_PIN_RESET)
   {
      if (but2_counter < debounce_time_ms)
      {
         but2_counter++;
      }
      else
      {
         if (but2_counter == debounce_time_ms)
         {
            but2_counter++;
            (void)SEQ_AddEvent(eButton2);
         }
      }
   }
   else
   {
      but2_counter = 0;
   }   
}


// Error handler if HAL configuration fails
void ErrorHandler(void)
{
   // Infinite loop if HAL returns an error
   __disable_interrupt();
   while (true)
   {
   }
}
