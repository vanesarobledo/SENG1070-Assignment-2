/*
* FILE			: test_harness.c
* PROJECT		: SENG1070 Assignment 2 - Error Logging and Test Harness Development
* PROGRAMMER	: Vanesa Robledo
* FIRST VERSION : 2025-02-15
* DESCRIPTION	: This program implements a logging system and test harness for validating the
*				  functionality of a simple C program - basic math operations.
* This file contains the test harness that automates execution of test cases.
*/

// Toggle test logging

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
	printf("=====================================================================================================\n");
	printf("%-25s%-15s%-15s%-20s%-20s%-20s\n", "Test Name", "Param1", "Param2", "Expected Output", "Actual Output", "Result");
	printf("=====================================================================================================\n");
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
	// INITIALIZE DATA
	bool result = FAIL; // Initialize test result
	int actualResult = 0; // Store numerical results of function
	char actualOutput[OUTPUT_SIZE] = ""; // Store actual output in string
	char resultDescription[RESULT_SIZE] = ""; // Store string of PASS/FAIL for test log

	// Print details of test
	printf("%-25s%-15d%-15d%-20d", testName, param1, param2, expectedOutput);

	// RUN DIVIDE BY ZERO TEST
	if ((*test) == testDivideByZero) {
		if ((*function) == divide) {
			// Conduct test & store actual result
			result = test((*function), param1, param2, expectedOutput, &actualResult);
			if (result == PASS) {
				storeActualOutput(actualOutput, "0");
			}
			else {
				storeActualOutput(actualOutput, "Wrong Result");
			}
		}
		// Wrong function was called for test - print result
		else {
			storeActualOutput(actualOutput, "Wrong Function");
		}
	}

	// RUN OTHER TESTS
	else {
		// Conduct test & store actual result
		result = test((*function), param1, param2, expectedOutput, &actualResult);

		// Copy numerical result to actual output
		sprintf_s(actualOutput, OUTPUT_SIZE, "%d", actualResult);
	}

	// TEST RESULTS
	// Print actual output of test
	printf("%-20s", actualOutput);

	// Print whether test passed or failed to console in coloured text (thanks Tyler for mentioning it) and stores the result in a string for test log
	// Reference: https://www.theurbanpenguin.com/4184-2/

	if (result == PASS) { 
		printf("\033[0;32m"); // Green
		printf("PASS\n");
		printf("\033[0m");
		storeResult(resultDescription, "PASS");
	}
	else if (result == FAIL) { 
		printf("\033[0;31m"); // Red
		printf("FAIL\n");
		printf("\033[0m");
		storeResult(resultDescription, "FAIL");
	}

	// LOG TEST RESULTS
	// Store result of test in string
	char message[LOG_MESSAGE_SIZE] = "";
	sprintf_s(message, LOG_MESSAGE_SIZE, "Test Ran\nTest Name: %s\nParameters: %d, %d\nExpected Output: %d\nActual Output: %s\nResult: %s", testName, param1, param2, expectedOutput, actualOutput, resultDescription);

	// Log message and then close the logger
	logMessage(TEST, LOG_INFO, message);
	closeLogger();
}

//
// FUNCTION		: testHarnessBoundary
// DESCRIPTION	: Prints the result of boundary test case
//				  (Formatting of console message based on UnitTestExample from PROG1175)
// PARAMETERS	: int (*function)(int, int)	:	Function to test all boundaries
// RETURNS		: void
//
void testHarnessBoundary(int (*function)(int, int)) {
	// ADD
	if (*function == add) {
		// TEST Minimum Value
		testHarness("add() Boundary", INT_MIN, 1, -2147483647, add, testCase);
		// TEST Maximum Value
		testHarness("add()  Boundary", 2147483646, 1, INT_MAX, add, testCase);
	}
	// SUBTRACT
	else if (*function == subtract) {
		// TEST Minimum Value
		testHarness("subtract() Boundary", -2147483647, 1, INT_MIN, subtract, testCase);
		// TEST Maximum Value
		testHarness("subtract() Boundary", INT_MAX, 1, 2147483646, subtract, testCase);
	}
	// MULTIPLY
	else if (*function == multiply) {
		// TEST Positive Values
		testHarness("multiply() Boundary", INT_MAX, 1, INT_MAX, multiply, testCase);
		testHarness("multiply() Boundary", INT_MIN, 1, INT_MIN, multiply, testCase);
		// TEST Negative Values
		testHarness("multiply() Boundary", -2147483647, -1, INT_MAX, multiply, testCase);
		testHarness("multiply() Boundary", INT_MAX, -1, -2147483647, multiply, testCase);
	}
	// DIVIDE
	else if (*function == divide) {
		// TEST Positive Values
		testHarness("divide() Boundary", INT_MIN, INT_MIN, 1, divide, testCase);
		testHarness("divide() Boundary", INT_MAX, INT_MAX, 1, divide, testCase);
		// TEST Negative Values
		testHarness("divide() Boundary", INT_MIN, 2147483647, -1, divide, testCase);
		testHarness("divide() Boundary", INT_MAX, -2147483647, -1, divide, testCase);
	}
}

//
// FUNCTION		: testHarnessException
// DESCRIPTION	: Prints the result of exception test cases (input is floating-point values)
//				  (Formatting of console message based on UnitTestExample from PROG1175)
// PARAMETERS	: char* testName		:	Description of test being conducted
//				  float param1			:	First input parameter
//				  float param2			:	Second input parameter
//				  int expectedOutput	:	Expected output
//				  int (*function)(int, int)		: Function to be tested
//				  bool (*test)(int, int, int)	: Test case function
// RETURNS		: void
//
void testHarnessException(char* testName, float param1, float param2, int expectedOutput, int (*function)(int, int), bool (*test)(int (*function)(int, int), int, int, int, int*)) {
	// INITIALIZE DATA
	bool result = FAIL; // Initialize test result
	int actualResult = 0; // Store numerical results of function
	char actualOutput[OUTPUT_SIZE] = ""; // Store actual output in string
	char resultDescription[RESULT_SIZE] = ""; // Store string of PASS/FAIL for test log

	// Print test details
	printf("%-25s%-15.4f%-15.4f%-20d", testName, param1, param2, expectedOutput);

	// RUN EXCEPTION (NEGATIVE) TESTS
	result = test((*function), param1, param2, expectedOutput, &actualResult);

	// Copy numerical result to actual output
	sprintf_s(actualOutput, OUTPUT_SIZE, "%d", actualResult);

	// TEST RESULTS
	// Print actual output of test
	printf("%-20s", actualOutput);

	// Print whether test passed or failed to console in coloured text (thanks Tyler for mentioning it) and stores the result in a string for test log
	// Reference: https://www.theurbanpenguin.com/4184-2/

	if (result == PASS) {
		printf("\033[0;32m"); // Green
		printf("PASS\n");
		printf("\033[0m");
		storeResult(resultDescription, "PASS");
	}
	else if (result == FAIL) {
		printf("\033[0;31m"); // Red
		printf("FAIL\n");
		printf("\033[0m");
		storeResult(resultDescription, "FAIL");
	}

	// LOG TEST RESULTS
	// Store result of test in string
	char message[LOG_MESSAGE_SIZE] = "";
	sprintf_s(message, LOG_MESSAGE_SIZE, "Test Ran\nTest Name: %s\nParameters: %f, %f\nExpected Output: %d\nActual Output: %s\nResult: %s", testName, param1, param2, expectedOutput, actualOutput, resultDescription);

	// Log message and then close the logger
	logMessage(TEST, LOG_INFO, message);
	closeLogger();
}

//
// FUNCTION		: storeResult
// DESCRIPTION	: Copies string of test result into actualOutput
// PARAMETERS	: char* actualOutput	:	String storing output of result
//				  char* result			:	String containing non-numerical output
// RETURNS		: void
//
void storeActualOutput(char* actualOutput, char* result) {
	strncpy_s(actualOutput, OUTPUT_SIZE, result, OUTPUT_SIZE);
	actualOutput[strlen(actualOutput)] = '\0'; // Ensure null-termination after strncpy
}

//
// FUNCTION		: storeResult
// DESCRIPTION	: Copies string of test result into resultDescription
// PARAMETERS	: char* resultDescription	:	String storing description of result (PASS/FAIL)
//				  char* result				:	String containing PASS or FAIL
// RETURNS		: void
//
void storeResult(char* resultDescription, char* result) {
	strncpy_s(resultDescription, RESULT_SIZE, result, RESULT_SIZE);
	resultDescription[strlen(resultDescription)] = '\0'; // Ensure null-termination after strncpy
}

// FUNCTIONAL (POSITIVE) TEST

//
// FUNCTION		: testCase
// DESCRIPTION	: Contains test case for a given function
// PARAMETERS	: int (*function)(int, int)	:	Function to be tested
//				  int param1				:	First input parameter
//				  int param2				:	Second input parameter
//				  int expectedOutput		:	Expected output
//				  int* actual				:	Pointer to integer storing actual result
// RETURNS		: bool
//
bool testCase(int (*function)(int, int), int num1, int num2, int expected, int* actual) {
	// Store actual output of function
	*actual = (*function)(num1, num2);

	// Assert the test result
	assert(expected == *actual);
	
	// Return whether actual output matches expected output
	if (expected == *actual) {
		return PASS;
	}
	else {
		return FAIL;
	}
}

// EXCEPTION (NEGATIVE) TESTS

//
// FUNCTION		: testDivideByZero
// DESCRIPTION	: Tests division by zero
// PARAMETERS	: int (*function)(int, int)	:	Function to be tested
//				  int param1				:	First input parameter
//				  int param2				:	Second input parameter
//				  int expectedOutput		:	Expected output
//				  int* actual				:	Pointer to integer storing actual result
// RETURNS		: bool
//
bool testDivideByZero(int (*function)(int, int), int num1, int num2, int expected, int* actual) {
	*actual = divide(num1, num2);
	if (*actual == 0) {
		return PASS;
	}
	else {
		return FAIL;
	}
}