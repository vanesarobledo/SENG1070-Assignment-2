#include "../math_library.h"
#include "../math_library.c"

#include "pch.h"


// Add Tests
TEST(AddTest, HandlesPositiveInput) {
  EXPECT_EQ(5, add(2, 3));

}

TEST(AddTest, HandlesNegativeInput) {
	EXPECT_EQ(-5, add(-2, -3));
}

// Subtract Tests
TEST(SubtractTest, HandlesPositiveInput) {
	EXPECT_EQ(10, subtract(15, 5));
}

TEST(SubtractTest, HandlesNegativeInput) {
	EXPECT_EQ(-5, subtract(-10, -5));
}

// Multiply Tests


// Divide Tests
TEST(DivideTest, DivideByZero) {
	EXPECT_EQ(0, divide(5,0));
}
