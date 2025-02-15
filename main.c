/*
* FILE			: main.c
* PROJECT		: SENG1070 Assignment 2
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
#define TESTING	1

#include "logger.h"
#include "math_library.h"
#include "test_harness.h"

// Function Prototypes
void menu();
void getMenuOperation(int*);

// Commands for menu operation
enum commands {
	TEST_CASE,
	TEST_HARNESS,
	VIEW_LOG_FILES,
	EXIT
} operations;

int main(void)
{

#ifdef TESTING
	testHeader();
	testHarness("Add two numbers", 2, 3, 5, add, testFunctional);
	testHarness("Subtract two numbers", 10, 2, 8, subtract, testFunctional);
	testHarness("Multiply two numbers", 7, 7, 49, multiply, testFunctional);
	testHarness("Divide two numbers", 10, 2, 5, divide, testFunctional);
	printf("\n\n");
#endif

	// Initialize data
	int menuOperation = 0; // Store menu operation
	bool loop = true; // Flag to loop menu
	
	while (loop) {
		// Get menu operation from user
		menu();
		getMenuOperation(&menuOperation);
		operations = menuOperation - 1;
		switch (operations)
		{
		case TEST_CASE:
			printf("Call menu to select test cases.\n");
			break;

		case TEST_HARNESS:
			printf("Run every single test harness.\n");
			break;

		case VIEW_LOG_FILES:
			printf("Call menu to view log files.\n");
			break;

		case EXIT:
			printf("Exiting program...\n");
			exit(EXIT_SUCCESS);
			break;

		default:
			printf("Please select a valid menu operation.\n");
			break;
		}
	}
}

//
// FUNCTION		: menu
// DESCRIPTION	: Prints menu of functions to the screen
// PARAMETERS	: none
// RETURNS		: void
//
void menu(void) {
	printf("\Menu Operations\n");
	printf("[ 1 ] Run individual test case\n");
	printf("[ 2 ] Run all tests in test harness\n");
	printf("[ 3 ] View log files\n");
	printf("[ 4 ] Exit\n");
}

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