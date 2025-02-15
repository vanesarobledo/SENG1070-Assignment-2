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
//				  (Formatting based on UnitTestExample from PROG1175)
// PARAMETERS	: void
// RETURNS		: void
//
void testHeader(void) {
	printf("===========================================================================================\n");
	printf("%-25s%-10s%-10s%-20s%-20s%-20s\n", "Test Name", "Param1", "Param2", "Expected Output", "Actual Output", "Result");
	printf("===========================================================================================\n");
}

//
// FUNCTION		: testHarness
// DESCRIPTION	: Prints the result of test case
//				  (Formatting of console message based on UnitTestExample from PROG1175)
// PARAMETERS	: char* testName		:	Description of test being conducted
//				  int param1			:	First input parameter
//				  int param2			:	Second input parameter
//				  int expectedOutput	:	Expected output
//				  int (*function)(int, int)		: Function to be tested
//				  bool (*test)(int, int, int)	: Test case function
// RETURNS		: void
//
void testHarness(char* testName, int param1, int param2, int expectedOutput, int (*function)(int, int), bool (*test)(int (*function)(int, int), int, int, int, int*)) {
	int actualOutput = 0; // Store actual result
	char resultDescription[RESULT_SIZE] = ""; // Store string for test log
	bool result = FAIL; // Initialize test result

	// Conduct test & store actual output
	result = test((*function), param1, param2, expectedOutput, &actualOutput);

	// Print result of test to console
	printf("%-25s%-10d%-10d%-20d%-20d", testName, param1, param2, expectedOutput, actualOutput);

	// Print whether test passed or failed to console in coloured text (thanks Tyler for mentioning it)
	// and stores the result in a string for test log
	// REFERENCE: https://www.theurbanpenguin.com/4184-2/
	if (result == PASS) { 
		printf("\033[0;32m"); // Green
		printf("PASS\n");
		printf("\033[0m");
		storeResult(resultDescription, "PASS");
	}
	else { 
		printf("\033[0;31m"); // Red
		printf("FAIL\n");
		printf("\033[0m");
		storeResult(resultDescription, "FAIL");
	}

	// Log test results
	// Store result of test in string
	char message[LOG_MESSAGE_SIZE] = "";
	sprintf_s(message, LOG_MESSAGE_SIZE, "Test Ran\nTest Name: %s\nParameters: %d, %d\nExpected Output: %d\nActual Output: %d\nResult: %s", testName, param1, param2, expectedOutput, actualOutput, resultDescription);

	// Log message and then close the logger
	logMessage(TEST, LOG_INFO, message);
	closeLogger();
}

//
// FUNCTION		: storeResult
// DESCRIPTION	: Copies string of test result into resultDescription
// PARAMETERS	: char* resultDescription	:	String storing descriiption of result (PASS/FAIL)
//				  char* result				:	String containing PASS or FAIL
// RETURNS		: void
//
void storeResult(char* resultDescription, char* result) {
	strncpy_s(resultDescription, RESULT_SIZE, result, RESULT_SIZE);
	resultDescription[RESULT_SIZE - 1] = '\0'; // Ensure null-termination after strncpy
}

// Functional Test (Positive Tests)

//
// FUNCTION		: testFunctional
// DESCRIPTION	: Contains functional test case for given function
// PARAMETERS	: void
// RETURNS		: bool
//
bool testFunctional(int (*function)(int, int), int num1, int num2, int expected, int* actual) {
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