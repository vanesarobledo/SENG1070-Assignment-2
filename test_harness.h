#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

// Define pass/fail test
#define PASS 0
#define	FAIL 1

#define	RESULT_SIZE	5
#define	OUTPUT_SIZE	100
#define	LOG_MESSAGE_SIZE	256

// Function Prototypes - Test Harnesses

void testHeader();
void testHarness(char* testName, int param1, int param2, int expectedOutput, int (*function)(int, int), bool (*test)(int (*function)(int, int), int, int, int, int*));
void storeActualOutput(char* actualOutput, char* result);
void storeResult(char* resultDescription, char* result);

// Functional Test
bool testFunctional(int (*function)(int, int), int num1, int num2, int expected, int* actual);

// Boundary Test
bool testFunctional(int (*function)(int, int), int num1, int num2, int expected, int* actual);

// Exception Tests
//void testException();
bool testDivideByZero(int (*function)(int, int), int num1, int num2, int expected, int* actual);
