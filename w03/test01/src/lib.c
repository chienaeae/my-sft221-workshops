//
// Created by mac on 5/24/24.
//
#include "lib.h"

#include <ctype.h>
#include <stdio.h>
#include <string.h>

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

void inputString(char *str, char *promptText) {
    char buffer[MAX_NAME_LENGTH];
    int flag = 1;
    while (flag) {
        printf("%s", promptText);
        if (fgets(buffer, MAX_NAME_LENGTH, stdin) != NULL) {
            size_t length = strlen(buffer);

            if (length == 1 && buffer[0] == '\n') {
                printf("Invalid Entry: ");
            } else {
                if (buffer[length - 1] == '\n') {
                    buffer[length - 1] = '\0';
                    length--;
                } else {
                    clearInputBuffer();
                }

                strncpy(str, buffer, length + 1);  // +1 to include the null terminator
                flag = 0;
            }
        } else {
            clearInputBuffer();
        }
    }
}

void inputCustomer(struct Customer *customer) {
    inputString(customer->firstName, "Enter your first name: ");
    inputString(customer->lastName, "Enter your last name: ");
    inputString(customer->streetAddress, "Enter your street address: ");
    inputString(customer->city, "Enter your city: ");
    inputString(customer->province, "Enter your province: ");

    int valid = 0;
    do {
        inputString(customer->postalCode, "Enter your postal code: ");
        valid = checkPostalCode(customer->postalCode);
        if (!valid) {
            printf("Invalid Entry: ");
        }
    } while (!valid);
}

int checkPostalCode(char *postalCode) {
    char temp[MAX_NAME_LENGTH];

    int j = 0;
    for (int i = 0; postalCode[i] != '\0'; i++) {
        if (!isspace((postalCode[i]))) {
            if (j < MAX_NAME_LENGTH - 1) {
                temp[j] = (char)toupper(postalCode[i]);
                j++;
            }
        }
    }
    temp[j] = '\0';
    if (strlen(temp) != 6) {
        return 0;
    }
    for (int i = 0; i < 6; i++) {
        if (i % 2 == 0) {
            if (!isalpha(temp[i])) {
                return 0;
            }
        } else {
            if (!isdigit(temp[i])) {
                return 0;
            }
        }
    }

    snprintf(postalCode, MAX_NAME_LENGTH, "%.3s %.3s", temp, temp + 3);
    return 1;
}