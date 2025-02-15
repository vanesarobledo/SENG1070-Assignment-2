/*
* FILE			: test_harness.c
* PROJECT		: SENG1070 Assignment 2
* PROGRAMMER	: Vanesa Robledo
* FIRST VERSION : 2025-02-15
* DESCRIPTION	: This program implements a logging system and test harness for validating the
*				  functionality of a simple C program - basic math operations.
* This file contains the test harness that automates execution of test cases.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "logger.h"
#include "math_library.h"
#include "test_harness.h"

//
// FUNCTION		: testHeader
// DESCRIPTION	: Prints test header to screen
// PARAMETERS	: void
// RETURNS		: void
//
void testHeader(void) {
	printf("======================================================================================\n");
	printf("%-20s%-20s%-20s%-20s%-20s\n", (char*)"Test Name", (char*)"Input Parameters", (char*)"Expected Output", (char*)"Actual Output", (char*)"Result");
	printf("======================================================================================\n");
}

//
// FUNCTION		: testHarness
// DESCRIPTION	: Prints the result of test case
// PARAMETERS	: void
// RETURNS		: void
//
void testHarness(char* testName, int param1, int param2, int expectedOutput, int (*callback)(int, int)) {
	int result = callback(param1, param2);
	printf("%-20s%d, %-16d %-20d %-20d", testName, param1, param2, expectedOutput, result);

	printf("\033[0;31m");
	assert(result == 5 && "FAIL\n");
	printf("\033[0m");

	printf("\033[0;32m");
	printf("PASS\n");
	printf("\033[0m");
}


// Functional Tests (Positive Tests)
//
// FUNCTION		: test_add
// DESCRIPTION	: Contains functional test cases for add()
// PARAMETERS	: void
// RETURNS		: void
//
void test_add(void) {

}

//
// FUNCTION		: test_subtract
// DESCRIPTION	:
// PARAMETERS	: void
// RETURNS		: void
//
void test_subtract(void) {

}

//
// FUNCTION		: test_multiply
// DESCRIPTION	:
// PARAMETERS	: void
// RETURNS		: void
//
void test_multiply(void) {

}

//
// FUNCTION		: test_divide
// DESCRIPTION	:
// PARAMETERS	: void
// RETURNS		: void
//
void test_divide(void) {

}