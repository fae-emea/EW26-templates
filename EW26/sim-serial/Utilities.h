/*
 * Copyright (c) 1996 - 2026 IAR Systems AB.
 *
 * IAR Embedded Workbench tutorial
 *
 * Utilities.h
 *
 * Utility header file for several tutorials.
 *
 * See the file <target>/doc/licenses/IARSourceLicense.txt for detailed
 * license information.
 *
 * $Revision: 113247 $
 */

#ifndef UTILITIES_H
#define UTILITIES_H

#define MAX_FIB 10

#include <stdint.h>
void InitFib(void);
uint32_t GetFib(uint_fast8_t n);
void PutFib(uint32_t out);

#endif
