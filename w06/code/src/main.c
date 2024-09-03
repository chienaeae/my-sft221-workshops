#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "logger.h"
#include "stringhelp.h"
#include "log4c.h"
#include <string.h>
#include <ctype.h>

struct Log4cStruct logger;

int main(void) {
    logger = l4cOpen("log4c.log", 0);
    l4cInfo(&logger, "Logger initialized");

    char testStr[] = "This is a\n string with embedded newline character and\n12345 numbers inside it as well 67890";
    struct StringIndex index = indexString(testStr);
    int i;
    char buffer[MAX_STRING_SIZE] = {};

    printf("LINES\n");
    for (i = 0; i < index.numLines; i++) {
        printUntil(index.str, index.lineStarts[i], '\n');
        printf("\n");
    }

    printf("\nWORDS\n");
    for (i = 0; i < index.numWords; i++) {
        printUntilSpace(index.str, index.wordStarts[i]);
        printf("\n");
    }

    printf("\nNUMBERS\n");
    for (i = 0; i < index.numNumbers; i++) {
        printUntilSpace(index.str, index.numberStarts[i]);
        printf("\n");
    }

    printf("LINES\n");
    for (i = 0; i < index.numLines; i++) {
        getLine(&index, i);
        printf("\n");
    }

    printf("\nWORDS\n");

    for (i = 0; i < index.numWords; i++) {
        getWord(buffer, &index, i);
        printf("\n");
    }

    printf("\nNUMBERS\n");
    for (i = 0; i < index.numNumbers; i++) {
        getNumber(buffer, &index, i);
        printf("\n");
    }

    l4cClose(&logger);
    return 0;
}
