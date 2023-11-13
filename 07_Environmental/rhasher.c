#define  _GNU_SOURCE
#include <ctype.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "rhash.h"
#include "config.h"

#ifdef HAVE_LIBREADLINE

#include <readline/readline.h>
#include <readline/history.h>

#endif

struct wordHashIDPair {
    char* word;
    int hashID;
};

struct cmd {
    int hashID;
    bool isLowercase;
    bool valid;
};

struct cmd parseCmdWord(char* word) {
    struct wordHashIDPair mapping[] = {
        {"MD5", RHASH_MD5},
        {"SHA1", RHASH_SHA1},
        {"TTH", RHASH_TTH},
        {NULL, 0},
    };
    for (int i = 0;; ++i) {
        if (!mapping[i].word) {
            return (struct cmd){
                .valid=false,
            };
        }
        if (strcasecmp(word, mapping[i].word) == 0) {
            return (struct cmd){
                .hashID=mapping[i].hashID,
                .isLowercase=islower(word[0]),
                .valid=true,
            };
        }
    }
}

char *getLine() {
#ifdef HAVE_LIBREADLINE
    return readline(NULL);
#else
    char *line = NULL;
    size_t n = 0;
    if (getline(&line, &n, stdin) == -1) {
        free(line);
        return NULL;
    }
    return line;
#endif
}

int main(void) {
    rhash_library_init();

    while(true) {
        char *line = getLine();
        if (line == NULL) {
            return 0;
        }

        char *first = strtok(line, " \n");
        char *second = strtok(NULL, " \n");

        struct cmd parsedCmd = parseCmdWord(first);
        if (!parsedCmd.valid) {
            fprintf(stderr, "ERROR: unrecognized command: %s\n", first);
            free(line);
            continue;
        }

        if (!second) {
            fprintf(stderr, "ERROR: no string/filename provided\n");
            free(line);
            continue;
        }


        bool isFilename = *second != '"';

        unsigned char digest[64];
        char output[130];

        if (isFilename) {
            int res = rhash_file(parsedCmd.hashID, second, digest);
            if (res < 0) {
                fprintf(stderr, "ERROR: librhash error: %s: %s\n", second, strerror(errno));
                free(line);
                continue;
            }
        } else {
            second++;
            int res = rhash_msg(parsedCmd.hashID, second, strlen(second), digest);
            if (res < 0) {
                fprintf(stderr, "ERROR: librhash message digest calculation error\n");
                free(line);
                continue;
            }
        }
        rhash_print_bytes(output, digest, rhash_get_digest_size(parsedCmd.hashID), (parsedCmd.isLowercase?RHPR_HEX:RHPR_BASE64));
        printf("%s\n", output);

        free(line);
    }
}