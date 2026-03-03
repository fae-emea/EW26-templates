/*
 * Copyright (c) 1996 - 2026 IAR Systems AB.
 *
 * IAR Embedded Workbench tutorial
 *
 * SerialPortInterrupt.c
 *
 * Prints the Fibonacci sequence using an interrupt handler for a
 * dummy device.
 *
 * Device: This tutorial uses the device ST STM32F107xB.
 *         Specify the device in the project Options dialog box on the 
 *         General Options Setup page.
 *
 * Receive data register: The RBUF data receive register in the tutorial 
 *                       refers to USART1_DR.
 *
 * Interrupt vector: UART_VECTOR in the tutorial refers to USART1_IRQ.
 *
 * See the file <target>/doc/licenses/IARSourceLicense.txt for detailed
 * license information.
 *
 * $Revision: 113347 $
 */

/* Enables use of extended keywords. */
#pragma language=extended

#include <ST/iostm32f107xx.h>
#include <stdint.h>

#include <stdio.h>
#include <intrinsics.h>

#include "Utilities.h"

/* Tracks the current number in the Fibonacci sequence. */
uint_fast16_t callCount = 0;

/* Fibonacci number */
uint32_t fib;

/* Initializes UART. */
void InitUart(void)
{
  /* Not needed when running the tutorial in the simulator. */
}

/* Called while waiting for interrupts. */
void DoForegroundProcess(void)
{
  putchar('.');
}

/* Defines an interrupt handler for the ARMv7m (Cortex-M) USART1 interrupt. */
void UartReceiveHandler()
{
  /* Read the Fibonacci value from the receive data register. */
  fib = USART1_DR;
  PutFib(fib);

  /* Increment the current number in the Fibonacci sequence. */
  ++callCount;

  /* Not needed to clear or reset anything when running the tutorial in the simulator. */
}

/* Main application for the timer interrupt simulation tutorial;
 * prints the Fibonacci sequence.
 */
void main( void )
{
  __disable_interrupt();

  /* Initalize the serial port and the Fibonacci numbers. */
  InitUart();
  InitFib();

  __enable_interrupt();

  /* Loops 'forever', taking input when interrupted. */
  while (callCount < MAX_FIB)
  {
    DoForegroundProcess();
  }
}
