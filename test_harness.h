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
#define	LOG_MESSAGE_SIZE	256

// Function Prototypes - Test Harnesses

void testHeader();
void testHarness(char* testName, int param1, int param2, int expectedOutput, int (*function)(int, int), bool (*test)(int (*function)(int, int), int, int, int, int*));
void storeResult(char* resultDescription, char* result);

// Functional Tests
bool testFunctional(int (*function)(int, int), int num1, int num2, int expected, int* actual);

// Exception Tests
void test_add_exception();
void test_subtraction_exception();
void test_multiply_exception();
void test_divide_exception();
void test_divide_by_zero();

// Boundary Tests
void test_add_boundary();
void test_subtract_boundary();
void test_multiply_boundary();
void test_divide_boundary();

