#include <gtest/gtest.h>

extern "C" {
#include "lib.h"
}

class InputTest : public ::testing::Test {
   protected:
    void SetUp() override {
        originalStdin = dup(STDIN_FILENO);
    }

    void TearDown() override {
        dup2(originalStdin, STDIN_FILENO);
        close(originalStdin);
    }

    int originalStdin;
};

// Helper function to set stdin to a string
void setStdin(const char* input) {
    int fds[2];
    pipe(fds);
    write(fds[1], input, strlen(input));
    write(fds[1], "\n", 1);
    close(fds[1]);
    dup2(fds[0], STDIN_FILENO);
    close(fds[0]);
}

TEST_F(InputTest, BlackBoxTestInputString) {
    char prompt[] = "Enter your name: ";
    char result[MAX_NAME_LENGTH];
    setStdin("John");
    inputString(result, prompt);
    EXPECT_STREQ(result, "John");
}

TEST_F(InputTest, BlackBoxTestInputStringWithRetry) {
    char prompt[] = "Enter your name: ";
    char result[MAX_NAME_LENGTH];
    setStdin("\nJohn");
    inputString(result, prompt);
    EXPECT_STREQ(result, "John");
}

TEST_F(InputTest, WhiteBoxTestClearInputBuffer) {
    char prompt[] = "Enter your name: ";
    char result[MAX_NAME_LENGTH];
    char longInput[MAX_NAME_LENGTH * 2];

    memset(longInput, 'a', sizeof(longInput) - 1);
    longInput[sizeof(longInput) - 1] = '\0';

    setStdin(longInput);
    inputString(result, prompt);

    EXPECT_NE(strlen(result), strlen(longInput));
    EXPECT_STRNE(result, longInput);
}

TEST_F(InputTest, BlackBoxTestInputCustomer) {
    struct Customer customer;
    setStdin("John\nSmith\n25 Elm St.\nToronto\nON\nm2e 4x4");
    inputCustomer(&customer);
    EXPECT_STREQ(customer.firstName, "John");
    EXPECT_STREQ(customer.lastName, "Smith");
    EXPECT_STREQ(customer.streetAddress, "25 Elm St.");
    EXPECT_STREQ(customer.city, "Toronto");
    EXPECT_STREQ(customer.province, "ON");
    EXPECT_STREQ(customer.postalCode, "M2E 4X4");
}

TEST_F(InputTest, WhiteBoxTestInputCustomerWithRetry) {
    struct Customer customer;

    setStdin("John\nSmith\n25 Elm St.\nToronto\nON\ninvalid\nM2E 4X4");
    inputCustomer(&customer);
    EXPECT_STREQ(customer.firstName, "John");
    EXPECT_STREQ(customer.lastName, "Smith");
    EXPECT_STREQ(customer.streetAddress, "25 Elm St.");
    EXPECT_STREQ(customer.city, "Toronto");
    EXPECT_STREQ(customer.province, "ON");
    EXPECT_STREQ(customer.postalCode, "M2E 4X4");
}

TEST_F(InputTest, BlackBoxTestCheckPostalCode) {
    char postalCode[MAX_NAME_LENGTH];

    strcpy(postalCode, "A1A 1A1");
    EXPECT_TRUE(checkPostalCode(postalCode));
    EXPECT_STREQ(postalCode, "A1A 1A1");

    strcpy(postalCode, "a1a 1a1");
    EXPECT_TRUE(checkPostalCode(postalCode));
    EXPECT_STREQ(postalCode, "A1A 1A1");

    strcpy(postalCode, "a1a1a1");
    EXPECT_TRUE(checkPostalCode(postalCode));
    EXPECT_STREQ(postalCode, "A1A 1A1");

    strcpy(postalCode, "a 1 a 1 a 1 ");
    EXPECT_TRUE(checkPostalCode(postalCode));
    EXPECT_STREQ(postalCode, "A1A 1A1");

    strcpy(postalCode, "a1a2a3a4a5");
    EXPECT_FALSE(checkPostalCode(postalCode));

    strcpy(postalCode, "abc123abc123");
    EXPECT_FALSE(checkPostalCode(postalCode));

    strcpy(postalCode, "invalid");
    EXPECT_FALSE(checkPostalCode(postalCode));
}

TEST_F(InputTest, WhiteBoxTestCheckPostalCode) {
    char postalCode[MAX_NAME_LENGTH];

    strcpy(postalCode, "123 456");
    EXPECT_FALSE(checkPostalCode(postalCode));

    strcpy(postalCode, "aaa aaa");
    EXPECT_FALSE(checkPostalCode(postalCode));
}
