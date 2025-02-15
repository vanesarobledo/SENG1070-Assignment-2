#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// Function Prototypes - Test Harnesses

// Functional Tests
void test_sum();
void test_subtract();
void test_multiply();
void test_divide();

// Exception Tests
void test_sum_exception();
void test_subtraction_exception();
void test_multiple_exception();
void test_divide_exception();
void test_divide_by_zero();

// Boundary Tests
void test_sum_boundary();
void test_subtract_boundary();
void test_multiply_boundary();
void test_divide_boundary();

