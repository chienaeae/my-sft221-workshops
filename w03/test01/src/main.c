//
// Created by mac on 2024/5/13.
//

#include <stdio.h>

#include "lib.h"

int main() {
    struct Customer customer;
    inputCustomer(&customer);

    printf("You entered:\n");
    printf("%s %s\n", customer.firstName, customer.lastName);
    printf("%s,\n", customer.streetAddress);
    printf("%s, %s,\n", customer.city, customer.province);
    printf("%s\n", customer.postalCode);
    printf("\n");

    return 0;
}
