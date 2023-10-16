#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int begin = 0, end = 0, step = 1;
    if (argc < 2) {
        fprintf(stderr, "Usage:\n\t%s <end>\n\tOR\n\t%s <begin> <end> [step]\n", argv[0], argv[0]);
        return 1;
    }
    end = atoi(argv[1]);
    if (argc > 2) {
        begin = end;
        end = atoi(argv[2]);
    }
    if (argc > 3) {
        step = atoi(argv[3]);
    }

    if (step == 0) {
        step = 1;
    }

    if (step > 0) {
        for (int i = begin; i < end; i += step) {
            printf("%d\n", i);
        }
    } else {
        for (int i = begin; i > end; i += step) {
            printf("%d\n", i);
        }                
    }

    return 0;
}

