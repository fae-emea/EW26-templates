/*
* Copyright (c) 2019-2026 IAR Systems AB
*/

#include "dut.h"

uint8_t dut(uint8_t in_value)
{
	// do some calculation and verify the results via the C-SPY macro
	uint8_t ret_value = (uint8_t) ((in_value + 5) / 3);
	
	// branch to different functions based on the 3 LSB of 'in_value' to show code coverage
	switch (in_value % 8)
	{
	case 0:
		dut0();
		break;
		
	case 1:
		dut1();
		break;
		
	case 2:
		dut2();
		break;
		
	case 3:
		dut3();
		break;
		
	case 4:
		dut4();
		break;
		
	case 5:
		dut5();
		break;
		
	case 6:
		dut6();
		break;
		
	case 7:
		dut7();
		break;
		
	default:
		break;
	}
	
	return ret_value;
}

// some functions to show code coverage...
void dut0(void)
{
	// do some stuff here...
	__no_operation();
}

void dut1(void)
{
	// do some stuff here...
	__no_operation();
}

void dut2(void)
{
	// do some stuff here...
	__no_operation();
}

void dut3(void)
{
	// do some stuff here...
	__no_operation();
}

void dut4(void)
{
	// do some stuff here...
	__no_operation();
}

void dut5(void)
{
	// do some stuff here...
	__no_operation();
}

void dut6(void)
{
	// do some stuff here...
	__no_operation();
}

void dut7(void)
{
	// do some stuff here...
	__no_operation();
}
