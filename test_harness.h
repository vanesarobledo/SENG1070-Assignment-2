#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

// Define macros
#define	RESULT_SIZE	5
#define	OUTPUT_SIZE	100
#define	LOG_MESSAGE_SIZE	256

// Define pass/fail test
#define PASS 0
#define	FAIL 1

// Function Prototypes - Test Harness and Test Cases
void testHeader();
void testHarness(char* testName, int param1, int param2, int expectedOutput, int (*function)(int, int), bool (*test)(int (*function)(int, int), int, int, int, int*));
void testHarnessBoundary(int (*function)(int, int));

void storeActualOutput(char* actualOutput, char* result);
void storeResult(char* resultDescription, char* result);

// Functional Test
bool testCase(int (*function)(int, int), int num1, int num2, int expected, int* actual);

// Exception Tests
bool testDivideByZero(int (*function)(int, int), int num1, int num2, int expected, int* actual);
