//
// Created by mac on 2024/5/13.
//
#include <gtest/gtest.h>
#include <lib.h>

// Declare a test
TEST(MultiplyTest, PositiveNos) {
    // Check single statement
    ASSERT_EQ(6, multiply(2, 3));

    // Can also do multiple checks
    EXPECT_EQ(12, multiply(3, 4));
    EXPECT_EQ(72, multiply(9, 8));
}

// Declare another test
TEST(MultiplyTest, Zero) {
    EXPECT_EQ(0, multiply(2, 0));
    EXPECT_EQ(0, multiply(0, 10));
}
