/*
* Copyright (c) 2019-2026 IAR Systems AB
*/

// simple demo to show code coverage in the simulator
//
// by switching the configurations between 'Default' and 'Code_Coverage', a single run
// with 'input = 0' or a complete run with all 2^8 input values can be selected

#include <stdio.h>
#include <stdint.h>

#include "dut.h"

volatile uint8_t input = 0;		// input value for 'device under test' function
volatile uint8_t result = 0;		// calculation result of 'device under test' function
volatile uint8_t temp1 = 0;		// placeholder to trigger the macro that reads the input values from test_data.txt
volatile uint8_t temp2 = 0;		// placeholder to trigger the macro that compares the results

int main()
{
#ifdef CODE_COVERAGE
	uint8_t counter = 0;
	
	do
	{
		temp1 = temp1 + 1;		// read-access of 'temp1' triggers Input_Data() macro that reads the input value
#endif
		
		result = dut(input);		// Call 'device under test'
		
#ifdef CODE_COVERAGE
		temp2 = temp2 + 1;		// read-access of 'temp2' triggers Output_Data() macro that verifys the result
		counter++;
	}
	while(counter != 0);
#endif	
	return 0;
}
