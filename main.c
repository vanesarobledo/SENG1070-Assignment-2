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

#include "logger.h"
#include "math_library.h"
#include "test_harness.h"

// Function Prototypes
void menu();

// Commands for menu operation
enum commands {
	TEST_CASE,
	TEST_HARNESS,
	VIEW_LOG_FILES,
	EXIT
};

int main(void)
{

	return EXIT_SUCCESS;
}

//
// FUNCTION		: menu
// DESCRIPTION	: Prints menu of functions to the screen
// PARAMETERS	: none
// RETURNS		: void
//
void menu(void) {
	printf("Menu.\n");
}