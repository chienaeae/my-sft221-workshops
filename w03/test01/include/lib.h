//
// Created by mac on 5/24/24.
//

#
#ifndef UNIT_TEST_LIB_H
#define UNIT_TEST_LIB_H

#define MAX_NAME_LENGTH 20

struct Customer {
    char firstName[MAX_NAME_LENGTH];
    char lastName[MAX_NAME_LENGTH];
    char streetAddress[MAX_NAME_LENGTH];
    char city[MAX_NAME_LENGTH];
    char province[MAX_NAME_LENGTH];
    char postalCode[MAX_NAME_LENGTH];
};

void inputString(char *str, char *promptText);

void inputCustomer(struct Customer *customer);

int checkPostalCode(char *postalCode);

#endif  // UNIT_TEST_LIB_H
