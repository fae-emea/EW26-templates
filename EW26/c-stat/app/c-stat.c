/**
  ******************************************************************************
  * @file    c-stat.c
  * @brief   IAR C-STAT Demo
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

int32_t Arr[4] = { 0, 1 ,2, 3};
int32_t ArrI = 5; 


void cert1(int i, int *b) {   
  int a = i + b[++i];   //Do not depend on the order of evaluation for side effects
  printf("%d, %d", a, i); // CERT C
}


void cert2(void) {   
  static volatile int **ipp;   
  static int *ip;   
  static volatile int i = 0;   
  printf("i = %d.\n", i);   ipp = &ip; /* May produce a warning diagnostic */   
  ipp = (int**) &ip;    
  *ipp = &i; //Do not access a volatile object through a nonvolatile reference   
  if (*ip != 0) { /* Valid */     
  /* ... */   }   
} 


extern int do_auth(void); 
enum { BUFFERSIZE = 24 };  
void cert3(const char *msg) {   
  const char *error_log;   //error_log has not been initialized, an indeterminate value is read
  char buffer[BUFFERSIZE];   
  sprintf(buffer, "Error: %s", error_log);   
  printf("%s\n", buffer); 
} 

extern void c(int i, int j); 

int glob; 
int a(void) {   
  return glob + 10; } 

int b(void) {   
  glob = 42;   
return glob; } 

void cert4(void) {   c(a(), b()); }  //The order of evaluation for function arguments is unspecified. 
                                     //This noncompliant code example exhibits unspecified behavior but not undefined behavior

uint8_t *h(void)
{
  return malloc(0x10);
}

int32_t g(void)
{
  uint8_t *p = h();
  return p[100]; // Single fail fo heap
}
//cstat !ATH-div-0-unchk-global
#pragma cstat_disable="ATH-div-0-unchk-global"
int j=0;
void div0_test(void)
{
  int32_t i=5;
  
  j = i / j;  
}

void conv_test()
{
  int32_t i=5;
  uint8_t ch=0x50;
  
  ch+=0x105;                      // overflow     
  ch = (uint8_t) ( i * 100);    //conversion error
}

void switch_test(void)
{
  uint8_t ch=250;
  int32_t i;
  
  switch(ch)
  {
  case 0: i = 3; break;
  case 5: i = 2; break;
  }
  i++;
}

void shift_test(void)
{
  
  int32_t i=0x0000FFFF;
  int8_t loop;
  
  for(loop=0;loop<16;loop++)
  {
      i=i<<1;         // failure if i>15
  }
 
}

int32_t f(void)
{
  int32_t i;
  i =Arr[2];            // Double fail global
//  i = Arr[ArrI + 1];    // Double fail global
  
//  i += Arr[ArrI + 2];
  return i;
}

//#pragma cstat_enable="SPC-uninit-var-some"
int32_t cov_test(int32_t a){
  int32_t result;
  if(a){
  result = 0;
  }
  result++;
  return result;
}


void crun(void)
{
  cov_test(0);
  div0_test();           // division by 0
  conv_test();          // integer conversion resulting in change of value
  switch_test();        // unhandled case in switch
  shift_test();         // bit loss in shift 
  cert3("Test login");
  
  
}
//CSTAT_ON // enables all C-STAT rules that were activated in the project option. 
