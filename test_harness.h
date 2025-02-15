#pragma once

// Function Prototypes - Test Harnesses

void testHeader();
void testHarness(char* testName, int param1, int param2, int expectedOutput, int (*callback)(int, int));

// Functional Tests
void test_add();
void test_subtract();
void test_multiply();
void test_divide();

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

