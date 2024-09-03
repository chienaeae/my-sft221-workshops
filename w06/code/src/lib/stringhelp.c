#define _CRT_SECURE_NO_WARNINGS
#include "log4c.h"
#include "logger.h"
#include "stringhelp.h"
#include <ctype.h>
#include <string.h>
#include <stdio.h>

int nextWhite(const char* str) {
    int i, result = -1;
#ifdef DEBUG
    l4cInfo(&logger, "----- Entering nextWhite -----");
#endif

    for (i = 0; result < 0 && str[i] != '\0'; i++) {
        if (str[i] == ' ' || str[i] == '\t') {
            result = i;
        }
    }

#ifdef DEBUG
    l4cPrintf(&logger, L4C_INFO, "nextWhite result: %d", result);
    l4cPrintf(&logger, L4C_INFO, "----- Exiting nextWhite -----");
#endif

    // Bug 1: Logical error in return statement, the result of `(result * -1) != result`
    // are always true and returning `i` is incorrect.
    // Here I fix it by directly returning 'result'
    // return ((result * -1) != result) ? i : result;
    return result;
}

int isNumber(const char* str, const int len) {
    int result;
#ifdef DEBUG
    l4cPrintf(&logger, L4C_INFO, "----- Entering isNumber -----");
    l4cPrintf(&logger, L4C_INFO, "Entering function isNumber to check (%d): %s", len, str);
#endif
    for (result = 1; result <= len && result; result++) {
#ifdef isNumber_VERBOSE_DEBUG
        l4cPrintf(&logger, L4C_INFO, "checking: %c", str[result - 1]);
#endif
        if (!isdigit(str[result - 1])) {
            result = -1;
            // Bug 2: Loop should exit immediately after non-digit is found, added 'break',
            // otherwise the non-digit would be overridden
            break;
        }
    }
#ifdef DEBUG
    l4cPrintf(&logger, L4C_INFO, "isNumber result: %d", result);
    l4cPrintf(&logger, L4C_INFO, "----- Exiting isNumber -----");
#endif
    return result;
}

struct StringIndex indexString(const char* str) {
#ifdef DEBUG
    l4cInfo(&logger, "----- Entering indexString -----");
    l4cPrintf(&logger, L4C_INFO, "indexing string: %s", str);
#endif
    struct StringIndex result = { {0}, {0}, {0}, 0, 0, 0 };
    // Bug 3: Unused variable 'buf', removed
    // char buf[MAX_WORD_SIZE + 1] = {0};
    int i, sp;

    strcpy(result.str, str);
    if (str[0] != '\0') {
        result.lineStarts[0] = 0;
        result.numLines = 1;
#ifdef DEBUG_VERBOSE_indexString
        l4cPrintf(&logger, L4C_INFO, "indexed line at position: %d", 0);
#endif
    }

    for (i = 0; str[i] != '\0'; i++) {
        while (str[i] != '\0' && isspace(str[i])) {
            // Bug 4: Should check for '\n' to handle new lines correctly
            // if (str[i] == '\0') {
            if (str[i] == '\n') {
                result.lineStarts[result.numLines++] = i + 1;
#ifdef DEBUG_VERBOSE_indexString
            l4cPrintf(&logger, L4C_INFO, "indexed line at position: %d", i + 1);
#endif
            }
            i++;
        }
        // Bug 5: Missing handling improper null terminator. If found, it should exit the loop
        if (str[i] == '\0') break;

        for (sp = 0; str[sp + i] != '\0' && !isspace(str[sp + i]); sp++);

#ifdef DEBUG_VERBOSE_indexString
        l4cPrintf(&logger, L4C_INFO, "i, sp: (%d,%d)", i, sp);
#endif

        // Bug 6: Incorrect use of isNumber, should check against -1
        // if (isNumber(str + i, sp)) {
        if (isNumber(str + i, sp) != -1) {
            result.numberStarts[result.numNumbers++] = i;
#ifdef DEBUG_VERBOSE_indexString
            l4cPrintf(&logger, L4C_INFO, "indexed number at position: %d", i);
#endif
        } else {
            result.wordStarts[result.numWords++] = i;
#ifdef DEBUG_VERBOSE_indexString
            l4cPrintf(&logger, L4C_INFO, "indexed word at position: %d", i);
#endif
        }

        i += sp - 1;
    }


#ifdef DEBUG
    l4cPrintf(&logger, L4C_INFO, "indexing string numWords: %d", result.numWords);
    l4cPrintf(&logger, L4C_INFO, "indexing string numNumbers: %d", result.numNumbers);
    l4cPrintf(&logger, L4C_INFO, "indexing string numLines: %d", result.numLines);
    l4cInfo(&logger, "----- Exiting indexString -----");
#endif
    return result;
}

int getNumberLines(const struct StringIndex* idx) {
    return idx->numLines;
}

int getNumberWords(const struct StringIndex* idx) {
    return idx->numWords;
}

int getNumberNumbers(const struct StringIndex* idx) {
    return idx->numNumbers;
}

void getWord(char word[], const struct StringIndex* idx, int wordNum) {
#ifdef DEBUG
    l4cInfo(&logger, "----- Entering getWord -----");
    l4cPrintf(&logger, L4C_INFO, "numberNum: %d", wordNum);
#endif
    int i, sp, start;

    word[0] = '\0';
    if (wordNum < idx->numWords && wordNum >= 0) {
        start = idx->wordStarts[wordNum];
        sp = nextWhite(idx->str + start);

#ifdef DEBUG_VERBOSE_getWord
        l4cPrintf(&logger, L4C_INFO, "start, numberNum: (%d, %d)", start, numberNum);
#endif

        // Bug 7: Missing handling the result from nextWhite could be -1
        if(sp == -1) {
            sp = strlen(idx->str + start);
        }

        for (i = 0; i <= sp; i++) {
            word[i] = idx->str[start + i];
        }
        word[sp] = '\0';
    }
#ifdef DEBUG
    l4cPrintf(&logger, L4C_INFO, "result: %s", word);
    l4cInfo(&logger, "----- Exiting getWord -----");
#endif
}

void getNumber(char word[], const struct StringIndex* idx, int numberNum) {
#ifdef DEBUG
    l4cInfo(&logger, "----- Entering getNumber -----");
    l4cPrintf(&logger, L4C_INFO, "numberNum: %d", numberNum);
#endif
    int i, sp, start;

    word[0] = '\0';
    if (numberNum < idx->numNumbers && numberNum >= 0) {
        start = idx->numberStarts[numberNum];
        sp = nextWhite(idx->str + start);

#ifdef DEBUG_VERBOSE_getNumber
        l4cPrintf(&logger, L4C_INFO, "start, numberNum: (%d, %d)", start, numberNum);
#endif

        // Bug 8: Missing handling the result from nextWhite could be -1
        if(sp == -1) {
            sp = strlen(idx->str + start);
        }

        for (i = 0; i < sp; i++) {
            word[i] = idx->str[start + i];
        }
        word[sp] = '\0';
    }

#ifdef DEBUG
    l4cPrintf(&logger, L4C_INFO, "result: %s", word);
    l4cInfo(&logger, "----- Exiting getNumber -----");
#endif
}

char* getLine(struct StringIndex* idx, int lineNum) {
#ifdef DEBUG
    l4cInfo(&logger, "----- Entering getLine -----");
    l4cPrintf(&logger, L4C_INFO, "lineNum: %d", lineNum);
#endif
    char* result = NULL;
    if (lineNum < idx->numLines && lineNum >= 0) {
        result = idx->str + idx->lineStarts[lineNum];
    }
#ifdef DEBUG
    l4cPrintf(&logger, L4C_INFO, "result: %p", (void*)result);
    l4cInfo(&logger, "----- Exiting getLine -----");
#endif
    return result;
}

void printUntil(const char* s, const int start, const char terminator) {
#ifdef DEBUG
    l4cInfo(&logger, "----- Entering printUntil -----");
#endif
    int i;
    for (i = start; s[i] != '\0' && s[i] != terminator; i++) {
        printf("%c", s[i]);
    }
#ifdef DEBUG
    l4cInfo(&logger, "----- Exiting printUntil -----");
#endif
}

void printUntilSpace(const char* s, const int start) {
#ifdef DEBUG
    l4cInfo(&logger, "----- Entering printUntilSpace -----");
#endif
    int i;
    for (i = start; s[i] != '\0' && !isspace(s[i]); i++) {
        printf("%c", s[i]);
    }
#ifdef DEBUG
    l4cInfo(&logger, "----- Exiting printUntilSpace -----");
#endif
}
