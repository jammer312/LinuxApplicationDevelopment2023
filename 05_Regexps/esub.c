#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define SUBMATCHES 10

void printSubstring(char *from, int begin, int end) {
    char tmp = from[end];
    from[end] = 0;
    fputs(from+begin, stdout);
    from[end] = tmp;
}

int findUnescapedOffset(char needle, char *haystack) {
    int ret = 0;
    bool escaped = false;
    for (; *haystack; ++haystack, ++ret) {
        if (escaped) {
            escaped = false;
            continue;
        }
        if (*haystack == needle) {
            return ret;
        }
        if (*haystack == '\\') {
            escaped = true;
            continue;
        }
    }
    return -1;
}

int countSubmatches(char *regexp) {
    int ret = 0;
    bool escaped = false;
    for (; *regexp; ++regexp) {
        if (escaped) {
            escaped = false;
            continue;
        }
        if (*regexp == '\\') {
            escaped = true;
            continue;
        }
        if (*regexp == '(') {
            ++ret;
            continue;
        }
        if (*regexp == '[') {
            int offset = findUnescapedOffset(']', regexp);
            if (offset == -1) {
                exit(1); //should not ever happen if countSubmatches runs on compileable regexp and there are no bugs (and if there are - ¯\_(ツ)_/¯)
            }
            regexp += offset;
            continue;
        }
    }
    return ret;
}

int main(int argc, char *argv[]) {
    if (argc < 4) {
        fprintf(stderr, "Usage: %s <regexp> <substitution> <string>\n", argv[0]);
        return 1;
    }

    int retCode;
    char msgBuf[256];
    regex_t regex;
    retCode = regcomp(&regex, argv[1], REG_EXTENDED);
    if (retCode) {
        regerror(retCode, &regex, msgBuf, sizeof(msgBuf));
        fprintf(stderr, "Coudln't compile regular expression: %s\n", msgBuf);
        return 1;
    }

    int submatchNum = countSubmatches(argv[1]);
    regmatch_t matches[SUBMATCHES];
    retCode = regexec(&regex, argv[3], SUBMATCHES, matches, 0);
    if (retCode) {
        regerror(retCode, &regex, msgBuf, sizeof(msgBuf));
        regfree(&regex);
        fprintf(stderr, "Coudln't match input string using provided regular expression: %s\n", msgBuf);
        return 1;
    }
    regfree(&regex);

    if (matches[0].rm_so == -1) {
        fputs(argv[3], stdout);
        return 0;
    }
    
    printSubstring(argv[3], 0, matches[0].rm_so);

    bool escaped = false;
    for (char *c = argv[2]; *c; ++c) {
        if (*c == '\\') {
            if (escaped) {
                putc('\\', stdout);
                escaped = false;
                continue;
            }
            escaped = true;
            continue;
        }
        if (!escaped) {
            putc(*c, stdout);
            continue;
        }
        escaped = false;
        int digit = *c - '0';
        bool isDigit = digit >= 0 && digit <= 9;
        if (isDigit) {
            if (digit > submatchNum) {
                fprintf(stderr, "Invalid reference to submatch #%d\n", digit);
                return 1;
            }
            if (matches[digit].rm_so == -1) {
                continue;
            }
            printSubstring(argv[3], matches[digit].rm_so, matches[digit].rm_eo);
        } else {
            putc('\\', stdout);
            putc(*c, stdout);
        }
    }

    fputs(argv[3]+matches[0].rm_eo, stdout);

    return 0;
}
