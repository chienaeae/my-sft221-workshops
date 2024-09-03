//
// Created by mac on 2024/5/13.
//
#include <gtest/gtest.h>


extern "C" {
#include <stringhelp.h>
}

// Test suite for nextWhite function
class NextWhiteTest : public ::testing::Test {
};

TEST_F(NextWhiteTest, NullInput) {
    EXPECT_EQ(nextWhite(NULL), -1);
}

TEST_F(NextWhiteTest, NoWhiteSpace) {
    EXPECT_EQ(nextWhite("HelloWorld"), 10);
}

TEST_F(NextWhiteTest, WhiteSpaceInMiddle) {
    EXPECT_EQ(nextWhite("Hello World"), 5);
}

TEST_F(NextWhiteTest, WhiteSpaceAtStart) {
    EXPECT_EQ(nextWhite(" HelloWorld"), 0);
}

TEST_F(NextWhiteTest, WhiteSpaceAtEnd) {
    EXPECT_EQ(nextWhite("HelloWorld "), 10);
}
