/*
* FILE			: math_library.c
* PROJECT		: SENG1070 Assignment 2
* PROGRAMMER	: Vanesa Robledo
* FIRST VERSION : 2025-02-15
* DESCRIPTION	: This program implements a logging system and test harness for validating the
*				  functionality of a simple C program - basic math operations.
* This file contains the basic math operation functions being tested
*/

#include "logger.h"
#include "math_library.h"
#include "test_harness.h"

//
// FUNCTION		: add
// DESCRIPTION	: Returns sum of two integers
// PARAMETERS	: int num1	:	First number
//				  int num2	:	Second number
// RETURNS		: int
//
int add(int num1, int num2) {
	return num1 + num2;
}

//
// FUNCTION		: subtract
// DESCRIPTION	: Returns difference of two integers
// PARAMETERS	: int num1	:	First number
//				  int num2	:	Second number
// RETURNS		: int
//
int subtract(int num1, int num2) {
	return num1 - num2;
}

//
// FUNCTION		: multiply
// DESCRIPTION	: Returns product of two integers
// PARAMETERS	: int num1	:	First number
//				  int num2	:	Second number
// RETURNS		: int
//
int multiply(int num1, int num2) {
	return num1 * num2;
}

//
// FUNCTION		: divide
// DESCRIPTION	: Returns quotient of two numbers
// PARAMETERS	: int dividend	:	Dividend
//				  int divisor	:	Divisor
// RETURNS		: double
//
int divide(int dividend, int divisor) {
	// Check for division by zero
	if (divisor == 0) {
		return 0.0;
	}
	else {
		return dividend / divisor;
	}
}