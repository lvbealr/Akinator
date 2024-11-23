#ifndef CUSTOM_STRCMP_H_
#define CUSTOM_STRCMP_H_

#include <cstring>
#include <cstdlib>
#include <cctype>

#include "customWarning.h"

static int customStrcmp(const char *firstString, const char *secondString) {
    customWarning(firstString  != NULL, 1);
    customWarning(secondString != NULL, 1);

    size_t firstLen     = strlen(firstString),
           secondLen    = strlen(secondString);

    char *firstStr  = (char *)calloc(firstLen,  sizeof(char));
    char *secondStr = (char *)calloc(secondLen, sizeof(char));

    strcpy(firstStr,  firstString);
    strcpy(secondStr, secondString);

    *(firstStr  + firstLen  - 1)  = EOF;
    *(secondStr + secondLen - 1)  = EOF;

    size_t firstIndex   = 0, secondIndex   = 0;
    int    firstElement = 0, secondElement = 0;

    int asciiDiff = 0;

    #define FREE_() {     \
        *firstStr  = {};  \
        *secondStr = {};  \
        free(firstStr);   \
        free(secondStr);  \
        firstStr  = NULL; \
        secondStr = NULL; \
    }

    while (asciiDiff == 0) {
        firstElement  = firstStr[firstIndex];
        secondElement = secondStr[secondIndex];

        if (firstElement == '\n' || firstElement == EOF) {
            FREE_();
            return (secondElement == '\n' || secondElement == EOF) ? 0 : -1;
        }

        if (secondElement == '\n' || secondElement == EOF) {
            FREE_();
            return 1;
        }

        if (isalpha(firstElement) || firstElement == ' ' || firstElement == '\'') {
            if (isalpha(secondElement) || secondElement == ' ' || secondElement == '\'') {
                asciiDiff += tolower(firstElement) - tolower(secondElement);
                firstIndex++; secondIndex++;
            }

            else {
                secondIndex++;
            }
        }

        else {
            firstIndex++;
        }
    }

    // FREE_(); // TODO

    #undef FREE_

    return asciiDiff;
}

#endif // CUSTOM_STRCMP_H_