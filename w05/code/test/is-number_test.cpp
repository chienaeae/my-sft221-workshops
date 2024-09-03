//
// Created by mac on 6/7/24.
//
#include <gtest/gtest.h>


extern "C" {
#include <stringhelp.h>
}

// Test suite for isNumber function
class IsNumberTest : public ::testing::Test {
};

TEST_F(IsNumberTest, NullInput) {
    EXPECT_EQ(isNumber(NULL, 5), -1);
    EXPECT_EQ(isNumber(NULL, 0), -1);
    EXPECT_EQ(isNumber(NULL, -1), -1);
}

TEST_F(IsNumberTest, AllDigits) {
    EXPECT_EQ(isNumber("12345", 5), 1);
}

TEST_F(IsNumberTest, NotAllDigits) {
    EXPECT_EQ(isNumber("123a5", 5), 0);
}

TEST_F(IsNumberTest, EmptyString) {
    EXPECT_EQ(isNumber("", 0), 1);
}

TEST_F(IsNumberTest, PartialDigits) {
    EXPECT_EQ(isNumber("12345abc", 5), 1);
    EXPECT_EQ(isNumber("12345abc", 8), 0);
}
