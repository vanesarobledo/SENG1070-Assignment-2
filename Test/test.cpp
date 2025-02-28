#include "../math_library.h"
#include "../math_library.c"

#include "pch.h"

// ADD TESTS
TEST(AddTest, HandlesPositiveInput) {
  EXPECT_EQ(5, add(2, 3));
  // Handles floating-point values
  EXPECT_EQ(5, add(2.55, 3.7));
}

TEST(AddTest, HandlesNegativeInput) {
	EXPECT_EQ(-5, add(-2, -3));
	// Handles floating-point values
	EXPECT_EQ(-5, add(-2.55, -3.7));
}

TEST(AddTest, Boundary) {
	EXPECT_EQ(-2147483647, add(INT_MIN, 1));
	EXPECT_EQ(INT_MAX, add(2147483646, 1));
}

// SUBTRACT TESTS
TEST(SubtractTest, HandlesPositiveInput) {
	EXPECT_EQ(10, subtract(15, 5));
	// Handles floating-point values
	EXPECT_EQ(10, subtract(15.5, 5.2));
}

TEST(SubtractTest, HandlesNegativeInput) {
	EXPECT_EQ(-5, subtract(-10, -5));
	// Handles floating-point values
	EXPECT_EQ(-5, subtract(-10.005, -5.21));
}

TEST(SubtractTest, Boundary) {
	EXPECT_EQ(INT_MIN, subtract(-2147483647, 1));
	// Handles floating-point values
	EXPECT_EQ(2147483646, subtract(INT_MAX, 1));
}

// MULTIPLY TESTS
TEST(MultiplyTest, HandlesPositiveInput) {
	EXPECT_EQ(50, multiply(10, 5));
	// Handles floating-point values
	EXPECT_EQ(50, multiply(10.0001, 5.9999));
}

TEST(MultiplyTest, HandlesNegativeInput) {
	EXPECT_EQ(-50, multiply(-10, 5));
	// Handles floating-point values
	EXPECT_EQ(-50, multiply(-10.0001, 5.9999));
}

TEST(MultiplyTest, Boundary) {
	EXPECT_EQ(INT_MAX, multiply(INT_MAX, 1));
	EXPECT_EQ(INT_MIN, multiply(INT_MIN, 1));
	EXPECT_EQ(INT_MAX, multiply(-2147483647, -1));
	EXPECT_EQ(INT_MAX, multiply(-2147483647, -1));
}

// DIVIDE TESTS
TEST(DivideTest, HandlesPositiveInput) {
	EXPECT_EQ(3, divide(6, 2));
	// Handles floating-point values
	EXPECT_EQ(3, divide(6.2, 2.3));
	// Handles answers that are floating-point values
	EXPECT_EQ(33, divide(100, 3));
}

TEST(DivideTest, HandlesNegativeInput) {
	EXPECT_EQ(45, divide(-90, -2));
	EXPECT_EQ(45, divide(-90.88, -2.233));
}

TEST(DivideTest, Boundary) {
	EXPECT_EQ(1, divide(INT_MIN, INT_MIN));
	EXPECT_EQ(1, divide(INT_MAX, INT_MAX));
	EXPECT_EQ(-1, divide(INT_MIN, INT_MAX));
	EXPECT_EQ(-1, divide(INT_MAX, -2147483647));
}

TEST(DivideTest, DivideByZero) {
	EXPECT_EQ(0, divide(5,0));
}
