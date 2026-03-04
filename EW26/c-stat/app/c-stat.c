/**
  ******************************************************************************
  * @file    c-stat.c
  * @brief   IAR C-STAT and IAR C-RUN Demo
  ******************************************************************************
  * @attention
  *
  * Copyright 2022-2026 (c) IAR Systems AB.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ********
  */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int32_t var_32;

int32_t Arr[4] = { 0, 1 ,2, 3 };
int32_t ArrI = 5; 

void cert1(int i, int *b)
{
  int a = i + b[++i];                            // CERT C: Do not depend on the order of evaluation for side effects.

  printf("%d, %d", a, i);
}

void cert2(void)
{
  static volatile int **ipp;   
  static int *ip;   
  static volatile int i = 0;   

  printf("i = %d.\n", i);
  ipp = &ip;                                     // May produce a warning diagnostic.
  ipp = (int**) &ip;    
  *ipp = &i;                                     // Do not access a volatile object through a non-volatile reference.
  if (*ip != 0)                                  // Valid!
  {
     /* ... */
  }
} 

extern int do_auth(void); 
enum { BUFFERSIZE = 24 };

void cert3(const char *msg)
{
  const char *error_log;                         // Unitialized!
  char buffer[BUFFERSIZE];   

  sprintf(buffer, "Error: %s", error_log);       // An indeterminate value is read.
  printf("%s\n", buffer); 
} 

extern void c(int i, int j); 

int glob;
int a(void)
{
  return glob + 10;
}
int b(void)
{
  glob = 42;   

  return glob;
}

void cert4(void)
{
  c(a(), b());                                   // Unspecified evaluation order for function arguments.
}                                                // Exhibits unspecified behavior (!= undefined behavior).

uint8_t *h(void)
{
  return malloc(0x10);
}

int32_t g(void)
{
  uint8_t *p = h();

  return p[100];                                 // Single fail fo heap!
}

//cstat !ATH-div-0-unchk-global
#pragma cstat_disable="ATH-div-0-unchk-global"
int j = 0;
void div0_test(void)
{
  int32_t i = 5;
  
  j = i / j;                                     // Division by 0!
}

void conv_test()
{
  int32_t i = 5;
  uint8_t ch = 0x50;
  
  ch += 0x105;                                   // Overflow!
  ch  = (uint8_t) ( i * 100);                    // Conversion error: the value changes!
}

void switch_test(void)
{
  uint8_t ch = 250;                              // Unhandled case in switch!
  int32_t i;
  
  switch (ch)
  {
  case 0:
    i = 3;
    break;
  case 5:
    i = 2;
    break;
  }
  i++;
}

void shift_test(void)
{
  int32_t i = 0x0000FFFF;
  
  for(int8_t loop = 0; loop < 16; loop++)
  {
    i = i << 1;                                  // Bit loss when i > 15!
  }
}

int32_t f(void)
{
  int32_t i;

  i = Arr[2];                                    // Double fail (vs global)!
//  i = Arr[ArrI + 1];
//  i += Arr[ArrI + 2];

  return i;
}

//#pragma cstat_enable="SPC-uninit-var-some"
int32_t cov_test(int32_t a)
{
  int32_t result;

  if (a)
  {
    result = 0;
  }
  result++;

  return result;
}

void code_analysis(void)
{
  cov_test(0);
  div0_test();
  conv_test();
  switch_test();
  shift_test();
  cert3("Test login");
}
//CSTAT_ON                                       // enables all C-STAT rules that were activated in the project option.
