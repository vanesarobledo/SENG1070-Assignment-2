/*
* FILE			: test_harness.c
* PROJECT		: SENG1070 Assignment 2
* PROGRAMMER	: Vanesa Robledo
* FIRST VERSION : 2025-02-15
* DESCRIPTION	: This program implements a logging system and test harness for validating the
*				  functionality of a simple C program - basic math operations.
* This file contains the test harness that automates execution of test cases.
*/

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
	printf("%-20s%-20s%-20s%-20s%-20s\n", "Test Name", "Input Parameters", "Expected Output", "Actual Output", "Result");
	printf("======================================================================================\n");
}

//
// FUNCTION		: testHarness
// DESCRIPTION	: Prints the result of test case
// PARAMETERS	: char* testName
//				  int param1
//				int param2
//				int expectedOutput
//				bool (*test)(int, int, int)
// RETURNS		: void
//
void testHarness(char* testName, int param1, int param2, int expectedOutput, int (*function)(int, int), bool (*test)(int (*function)(int, int), int, int, int, int*)) {
	// Store actualOutput
	int actualOutput = 0;

	// Store result of test
	bool result = test((*function), param1, param2, expectedOutput, &actualOutput);

	// Print result of test to console
	printf("%-20s%-10d%-10d%-20d%-20d", testName, param1, param2, expectedOutput, actualOutput);

	if (result == PASS) {
		pass();
	}
	else {
		fail();
		//assert(result == expectedOutput && "FAIL\n");
	}


	// Log test results
	//if (result == PASS) {
	//	logMessage(TEST, LOG_INFO, "Test Name: %s\nParameters: %d, %d\nExpected Output: %d\nActual Output: %d\nResult: PASS", testName, param1, param2, expectedOutput, actualOutput);
	//	closeLogger();
	//}
	//else if (result == FAIL) {
	//	logMessage(TEST, LOG_WARNING, "Test Name: %s\nParameters: %d, %d\nExpected Output: %d\nActual Output: %d\nResult: FAIL");
	//	closeLogger();
	//}
}

//
// FUNCTION		: pass
// DESCRIPTION	: Prints PASS in green text
// PARAMETERS	: void
// RETURNS		: void
//
void pass(void) {
	printf("\033[0;32m");
	printf("PASS\n");
	printf("\033[0m");
}

//
// FUNCTION		: fail
// DESCRIPTION	: Prints FAIL in red text
// PARAMETERS	: void
// RETURNS		: void
//
void fail(void) {
	printf("\033[0;31m");
	printf("FAIL\n");
	printf("\033[0m");
}

// Functional Tests (Positive Tests)

//
// FUNCTION		: test_functiona
// DESCRIPTION	: Contains functional test case for given function
// PARAMETERS	: void
// RETURNS		: bool
//
bool test_functional(int (*function)(int, int), int num1, int num2, int expected, int* actual) {
	// Store actual output of function
	*actual = (*function)(num1, num2);

	// Return whether actual output matches expected output
	if (expected == *actual) {
		return PASS;
	}
	else {
		return FAIL;
	}
}