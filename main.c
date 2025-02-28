/*
* FILE			: main.c
* PROJECT		: SENG1070 Assignment 2 - Error Logging and Test Harness Development
* PROGRAMMER	: Vanesa Robledo
* FIRST VERSION : 2025-02-15
* DESCRIPTION	: This program implements a logging system and test harness for validating the
*				  functionality of a simple C program - basic math operations.
* This file contains the main function and user menu.
*/

#include <stdio.h>
#include <stdbool.h>

// Define macros
#define INPUT_SIZE	100

// Types of functions for menu operation
#define	ADD_FUNCTION	'+'
#define	SUBTRACT_FUNCTION	'-'
#define	MULTIPLY_FUNCTION	'*'
#define	DIVIDE_FUNCTION	'/'
#define	ALL_FUNCTIONS	'?'

#include "logger.h"
#include "math_library.h"
#include "test_harness.h"

// Function Prototypes
void menu();
void menuTest();
void menuFunctions();
void menuFile();
void runTest(int, char);
void getMenuOperation(int*);
char getChar();

// Commands for menu operation
enum commands {
	TEST_CASE,
	TEST_HARNESS,
	VIEW_LOG_FILES,
	EXIT
} operations;

// Types of tests for menu operation {
enum tests {
	FUNCTIONAL,
	BOUNDARY,
	EXCEPTION,
	ALL_TESTS
} testoperations;

// Types of tests for file operations {
enum files {
	PROGRAM_LOG,
	TEST_LOG,
	BOTH,
	CANCEL
} fileoperations;

int main(void)
{
	logMessage(PROGRAM, LOG_INFO, "Program started");
	closeLogger();

	// Initialize data
	int menuOperation = 0; // Store menu operation
	int menuTestOperation = 0; // Store test menu operation
	int menuFileOperation = 0; // Store file menu operation
	bool loop = true; // Flag to loop menu
	char choice = '0'; // Store user choice of function
	bool validChoice = false; // Flag for valid user input
	FILE* logFile = NULL; // Store pointer to log file

	header();

	while (loop) {
		// Get menu operation from user
		menu();
		getMenuOperation(&menuOperation);
		operations = menuOperation - 1;
		switch (operations)
		{
		case TEST_CASE:
			logMessage(PROGRAM, LOG_INFO, "User selected to run individual test cases from main menu");
			closeLogger();

			// Get type of test to run from user
			menuTest();
			getMenuOperation(&menuTestOperation);
			testoperations = menuTestOperation - 1;

			// Get user input for function to test
			menuFunctions();
			while (!validChoice) {
				printf("Select function to test: ");
				choice = getChar();

				switch (choice) {
				case ADD_FUNCTION:
					runTest(testoperations, ADD_FUNCTION);
					validChoice = true;
					break;
				case SUBTRACT_FUNCTION:
					runTest(testoperations, SUBTRACT_FUNCTION);
					validChoice = true;
					break;
				case MULTIPLY_FUNCTION:
					runTest(testoperations, MULTIPLY_FUNCTION);
					validChoice = true;
					break;
				case DIVIDE_FUNCTION:
					runTest(testoperations, DIVIDE_FUNCTION);
					validChoice = true;
					break;
				case ALL_FUNCTIONS:
					runTest(testoperations, ALL_FUNCTIONS);
					validChoice = true;
					break;
				default:
					printf("Invalid input. Please enter a valid option.\n");
					break;
				}
			}
			validChoice = false; // Reset valid choice flag
			break;

		case TEST_HARNESS:
			logMessage(PROGRAM, LOG_INFO, "User selected to run every test harness from main menu");
			closeLogger();
			runTest(ALL_TESTS, ALL_FUNCTIONS);
			break;

		case VIEW_LOG_FILES:
			logMessage(PROGRAM, LOG_INFO, "User selected to view log files from main menu");
			closeLogger();

			// Get user input of file to view
			menuFile();
			getMenuOperation(&menuFileOperation);
			fileoperations = menuFileOperation - 1;
			switch (fileoperations)
			{
			case PROGRAM_LOG:
				viewFile(logFile, PROGRAM);
				break;
			case TEST_LOG:
				viewFile(logFile, TEST);
				break;
			case BOTH:
				viewFile(logFile, PROGRAM);
				viewFile(logFile, TEST);
				break;
			case CANCEL:
			default:
				break;
			}
			break;

		case EXIT:
			logMessage(PROGRAM, LOG_INFO, "User selected to exit the program from main menu");
			logMessage(PROGRAM, LOG_INFO, "Program exited");
			closeLogger();
			printf("Exiting program...\n");
			exit(EXIT_SUCCESS);
			break;

		default:
			logMessage(PROGRAM, LOG_WARNING, "User inputted invalud selection in main menu");
			closeLogger();
			printf("Please select a valid menu operation.\n");
			break;
		}
	}
	logMessage(PROGRAM, LOG_INFO, "Program exited");
	closeLogger();
	return EXIT_SUCCESS;
}

//
// FUNCTION		: header
// DESCRIPTION	: Prints header of program to the screen
// PARAMETERS	: none
// RETURNS		: void
//
void header(void) {
	printf("==================================================================\n");
	printf("SENG1070 Assignment 2 - Error Logging and Test Harness Development\n");
	printf("by Vanesa Robledo\n");
	printf("==================================================================");
}

//
// FUNCTION		: menu
// DESCRIPTION	: Prints menu of functions to the screen
// PARAMETERS	: none
// RETURNS		: void
//
void menu(void) {
	printf("\nMenu Operations\n");
	printf("[ 1 ] Run individual test case\n");
	printf("[ 2 ] Run all tests in test harness\n");
	printf("[ 3 ] View log files\n");
	printf("[ 4 ] Exit\n");
}

//
// FUNCTION		: menuTest
// DESCRIPTION	: Prints menu of test harness functions to the screen
// PARAMETERS	: none
// RETURNS		: void
//
void menuTest(void) {
	printf("\nTypes of Tests:\n");
	printf("[ 1 ] Functional Tests\n");
	printf("[ 2 ] Boundary Tests\n");
	printf("[ 3 ] Exception Tests\n");
	printf("[ 4 ] All Tests\n");
}

//
// FUNCTION		: menuFunctions
// DESCRIPTION	: Prints menu of test harness functions to the screen
// PARAMETERS	: void
// RETURNS		: void
//
void menuFunctions(void) {
	printf("\nFunctions:\n");
	printf("[ + ] add() \n");
	printf("[ - ] subtract()\n");
	printf("[ * ] multiply()\n");
	printf("[ / ] divide()\n");
	printf("[ ? ] All Functions\n");
}

//
// FUNCTION		: menuFile
// DESCRIPTION	: Prints menu of available log files to view to screen
// PARAMETERS	: void
// RETURNS		: void
//
void menuFile(void) {
	printf("\nFiles:\n");
	printf("[ 1 ] program.log - View program log\n");
	printf("[ 2 ] test.log - View all test results log \n");
	printf("[ 3 ] test.log and program.log - View both files \n");
	printf("[ 4 ] Cancel \n");
}

//
// FUNCTION		: runTest
// DESCRIPTION	: Runs a specified test given test type and function
// PARAMETERS	: int testType	:	Type of test to run
//				  char func		:	Function to run test on
// RETURNS		: void
//
void runTest(int testType, char func) {
	testHeader();
	switch (func) {
	case ADD_FUNCTION:
		switch (testType)
		{
		case FUNCTIONAL:
			logMessage(PROGRAM, LOG_INFO, "User selected to run functional test cases on add() function");
			closeLogger();
			testHarness("Add two numbers", 2, 3, 5, add, testCase);
			break;
		case BOUNDARY:
			logMessage(PROGRAM, LOG_INFO, "User selected to run boundary test case on add() function");
			closeLogger();
			testHarnessBoundary(add);
			break;
		case EXCEPTION:
			logMessage(PROGRAM, LOG_INFO, "User selected to run exception test cases on add() function");
			closeLogger();
			testHarnessException("add() Floats", 1.5, 2.5, 3, add, testCase);
			break;
		case ALL_TESTS:
			logMessage(PROGRAM, LOG_INFO, "User selected to run all test cases on add() function");
			closeLogger();
			testHarness("Add two numbers", 2, 3, 5, add, testCase);
			testHarnessBoundary(add);
			testHarnessException("add() Floats", 1.5, 2.5, 3, add, testCase);
			break;
		default:
			break;
		}
		break;
	case SUBTRACT_FUNCTION:
		switch (testType)
		{
		case FUNCTIONAL:
			logMessage(PROGRAM, LOG_INFO, "User selected to run functional test cases subtract() function");
			closeLogger();
			testHarness("Subtract two numbers", 10, 2, 8, subtract, testCase);
			break;
		case BOUNDARY:
			logMessage(PROGRAM, LOG_INFO, "User selected to run boundary test cases subtract() function");
			closeLogger();
			testHarnessBoundary(subtract);
			break;
		case EXCEPTION:
			logMessage(PROGRAM, LOG_INFO, "User selected to run exception test cases subtract() function");
			closeLogger();
			testHarnessException("subtract() Floats", 9.9, 1.2, 8, subtract, testCase);
			break;
		case ALL_TESTS:
			logMessage(PROGRAM, LOG_INFO, "User selected to run all test cases on subtract() function");
			closeLogger();
			testHarness("Subtract two numbers", 10, 2, 8, subtract, testCase);
			testHarnessBoundary(subtract);
			testHarnessException("subtract() Floats", 9.9, 1.2, 8, subtract, testCase);
			break;
		default:
			break;
		}
		break;
	case MULTIPLY_FUNCTION:
		switch (testType)
		{
		case FUNCTIONAL:
			logMessage(PROGRAM, LOG_INFO, "User selected to run functional test cases multiply() function");
			closeLogger();
			testHarness("Multiply two numbers", 7, 7, 49, multiply, testCase);
			break;
		case BOUNDARY:
			logMessage(PROGRAM, LOG_INFO, "User selected to run boundary test cases multiply() function");
			closeLogger();
			testHarnessBoundary(multiply);
			break;
		case EXCEPTION:
			logMessage(PROGRAM, LOG_INFO, "User selected to run exception test cases multiply() function");
			closeLogger();
			testHarnessException("multiply() Floats", 10.10, 20.20, 200, multiply, testCase);
			break;
		case ALL_TESTS:
			logMessage(PROGRAM, LOG_INFO, "User selected to run all test cases on multiply() function");
			closeLogger();
			testHarness("Multiply two numbers", 7, 7, 49, multiply, testCase);
			testHarnessBoundary(multiply);
			testHarnessException("multiply() Floats", 10.10, 20.20, 200, multiply, testCase);
			break;
		default:
			break;
		}
		break;
	case DIVIDE_FUNCTION:
		switch (testType)
		{
		case FUNCTIONAL:
			logMessage(PROGRAM, LOG_INFO, "User selected to run functional test cases on divide() function");
			closeLogger();
			testHarness("Divide two numbers", 10, 2, 5, divide, testCase);
			testHarness("Divide two numbers", 20, 3, 6, divide, testCase);
			break;
		case BOUNDARY:
			logMessage(PROGRAM, LOG_INFO, "User selected to run boundary test cases on divide() function");
			closeLogger();
			testHarnessBoundary(divide);
			break;
		case EXCEPTION:
			logMessage(PROGRAM, LOG_INFO, "User selected to run exception test cases on divide() function");
			closeLogger();
			testHarnessException("Divide() Floats", 100.0001, 3, 33, divide, testCase);
			testHarness("Divide by zero", 10, 0, 0, divide, testDivideByZero);
			break;
		case ALL_TESTS:
			logMessage(PROGRAM, LOG_INFO, "User selected to run all test cases on divide() function");
			closeLogger();
			testHarness("Divide two numbers", 10, 2, 5, divide, testCase);
			testHarnessBoundary(divide);
			testHarnessException("Divide() Floats", 100.0001, 3, 33, divide, testCase);
			testHarness("Divide by zero", 10, 0, 0, divide, testDivideByZero);
			break;
		default:
			break;
		}
		break;
	case ALL_FUNCTIONS:
		switch (testType)
		{
		case FUNCTIONAL:
			logMessage(PROGRAM, LOG_INFO, "User selected to run functional test cases on all functions");
			closeLogger();
			printf("FUNCTIONAL TESTS\n");
			testHarness("Add two numbers", 2, 3, 5, add, testCase);
			testHarness("Subtract two numbers", 10, 2, 8, subtract, testCase);
			testHarness("Multiply two numbers", 7, 7, 49, multiply, testCase);
			testHarness("Divide two numbers", 10, 2, 5, divide, testCase);
			testHarness("Divide two numbers", 20, 3, 6, divide, testCase);
			break;
		case BOUNDARY:
			logMessage(PROGRAM, LOG_INFO, "User selected to run boundary test cases on all functions");
			closeLogger();
			printf("BOUNDARY TESTS\n");
			testHarnessBoundary(add);
			testHarnessBoundary(subtract);
			testHarnessBoundary(multiply);
			testHarnessBoundary(divide);
			break;
		case EXCEPTION:
			logMessage(PROGRAM, LOG_INFO, "User selected to run exception test cases on all functions");
			closeLogger();
			printf("EXCEPTION TESTS\n");
			testHarnessException("add() Floats", 1.5, 2.5, 3, add, testCase);
			testHarnessException("subtract() Floats", 9.9, 1.2, 8, subtract, testCase);
			testHarnessException("multiply() Floats", 10.10, 20.20, 200, multiply, testCase);
			testHarnessException("divide() Floats", 100.0001, 3, 33, divide, testCase);
			testHarness("Divide by zero", 10, 0, 0, divide, testDivideByZero);
			break;
		case ALL_TESTS:
			logMessage(PROGRAM, LOG_INFO, "User selected to run all test cases on all functions");
			closeLogger();
			printf("\nFUNCTIONAL TESTS\n");
			testHarness("Add two numbers", 2, 3, 5, add, testCase);
			testHarness("Subtract two numbers", 10, 2, 8, subtract, testCase);
			testHarness("Multiply two numbers", 7, 7, 49, multiply, testCase);
			testHarness("Divide two numbers", 10, 2, 5, divide, testCase);
			testHarness("Divide two numbers", 20, 3, 6, divide, testCase);
			printf("\nBOUNDARY TESTS\n");
			testHarnessBoundary(add);
			testHarnessBoundary(subtract);
			testHarnessBoundary(multiply);
			testHarnessBoundary(divide);
			printf("\nEXCEPTION TESTS\n");
			testHarnessException("add() Floats", 1.5, 2.5, 3, add, testCase);
			testHarnessException("subtract() Floats", 9.9, 1.2, 8, subtract, testCase);
			testHarnessException("multiply() Floats", 10.10, 20.20, 200, multiply, testCase);
			testHarnessException("divide() Floats", 100.0001, 3, 33, divide, testCase);
			testHarness("Divide by zero", 10, 0, 0, divide, testDivideByZero);
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}

//
// FUNCTION		: getMenuOperation
// DESCRIPTION	: Valids numerical input for menu operation
// PARAMETERS	: int* menuOperation	:	Pointer to integer containing menuOperation
// RETURNS		: void
//
void getMenuOperation(int* menuOperation) {
	char buffer[INPUT_SIZE] = ""; // Buffer to store input
	char extraChar = '0'; // Store extraneous user input
	bool valid = false; // Valid menu operation
	const int kStart = 1; // Menu start number

	// Ask user for menu number
	while (!valid) {
		printf("Select option: ");
		fgets(buffer, sizeof(buffer), stdin);
		buffer[strlen(buffer) - 1]; // Remove trailing newline character from buffer

		// Validate input
		// Check conversion to integer without extraneous characters
		if (sscanf_s(buffer, "%d %c", menuOperation, &extraChar, (unsigned int)sizeof(extraChar)) != 1) {
			printf("Please enter a valid integer.\n");
		} // Check range of value
		else if (*menuOperation < kStart && *menuOperation > EXIT) {
			printf("Please enter a valid option from the menu.\n");
		} // Input is valid, break loop
		else {
			valid = true;
		}
	}
}

//
// FUNCTION		: getChar
// DESCRIPTION	: Gets character from user input and validates it
// PARAMETERS	: void
// RETURNS		: char
//
char getChar(void) {
	char buffer[INPUT_SIZE] = ""; // Buffer to store input
	char choice = '0'; // Store user choice
	char extraChar = '0'; // Store extraneous user input
	bool valid = false; // Valid menu operation

	// Ask user for menu number
	while (!valid) {
		fgets(buffer, sizeof(buffer), stdin);
		buffer[strlen(buffer) - 1]; // Remove trailing newline character from buffer

		// Validate input
		// Check conversion to integer without extraneous characters
		if (sscanf_s(buffer, "%c %c", &choice, (unsigned int)sizeof(choice), &extraChar, (unsigned int)sizeof(extraChar)) != 1) {
			printf("Please enter a valid input.\n");
		}
		else {
			valid = true;
		}
	}
	return choice;
}