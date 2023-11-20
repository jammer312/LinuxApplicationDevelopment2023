#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define DIRECTION_NUM 4

char isVisited(int x, int y, char *visited, int size) {
    return visited[x + y*size];
}

char isOOB(int x, int y, int size) {
    return x < 0 || y < 0 || x >= size || y >= size;
}

void generatePermutation(int* buf, int size) {
    for (int i = 0; i < size; i++) {
        buf[i] = i;
    }
    for (int i = size - 1; i >= 0; i--) {
        int j = rand() % (i+1);
        int tmp = buf[i];
        buf[i] = buf[j];
        buf[j] = tmp;
    }
}

int main(int argc, char *argv[]) {
    int size = 6;
    char cWall = '#';
    char cEmpty = '.';
    unsigned randseed = time(NULL);

    srand(randseed);

    char *hpaths = calloc((size-1)*size, sizeof(char));
    char *vpaths = calloc((size-1)*size, sizeof(char));
    char *visited = calloc(size*size, sizeof(char));

    int *boundary = calloc(size*size, sizeof(int));
    int boundaryLen = 0;
    int orderPermutation[DIRECTION_NUM];

    boundary[boundaryLen++] = rand()%(size*size);
    while (boundaryLen > 0) {
        int chosenPoint = rand()%boundaryLen;
        generatePermutation(orderPermutation, DIRECTION_NUM);

        int startX = boundary[chosenPoint]%size;
        int startY = boundary[chosenPoint]/size;
        int endX = startX;
        int endY = startY;

        char chosenDir = -1;
        for (int i = 0; i < DIRECTION_NUM; i++) {
            endX = startX;
            endY = startY;
            switch(orderPermutation[i]) {
            case 0:
                endX = startX + 1;
                break;
            case 1:
                endY = startY + 1;
                break;
            case 2:
                endX = startX - 1;
                break;
            case 3:
                endY = startY - 1;
                break;
            }
            if (isOOB(endX, endY, size) || isVisited(endX, endY, visited, size)) {
                continue;
            }
            chosenDir = orderPermutation[i];
            break;
        }
        if (chosenDir == -1) {
            boundary[chosenPoint] = boundary[--boundaryLen];
            continue;
        }
        int index = endX + endY*size;
        visited[index] = 1;
        boundary[boundaryLen++] = index;

        switch(chosenDir) {
        case 0:
            hpaths[startX + startY*(size-1)] = 1;
            break;
        case 1:
            vpaths[startY + startX*(size-1)] = 1;
            break;
        case 2:
            hpaths[endX + startY*(size-1)] = 1;
            break;
        case 3:
            vpaths[endY + startX*(size-1)] = 1;
            break;
        }
    }
    free(visited);
    free(boundary);

    for (int Y = 0; Y < size*2+1; Y++) {
        if (Y == 0 || Y == size*2) {
            for (int X = 0; X < size*2+1; X++) {
                putchar(cWall);
            }
            putchar('\n');
            continue;
        }
        int y = (Y - 1) / 2;
        if (Y%2 == 1) {
            for (int X = 0; X < size*2+1; X++) {
                if (X == 0 || X == size*2) {
                    putchar(cWall);
                    continue;
                }
                int x = (X - 1) / 2;
                if (X%2 == 1) {
                    putchar(cEmpty);
                } else {
                    putchar(hpaths[x + y*(size-1)]?cEmpty:cWall);
                }
            }
        } else {
            for (int X = 0; X < size*2+1; X++) {
                if (X%2 == 0) {
                    putchar(cWall);
                    continue;
                }
                int x = (X - 1) / 2;
                putchar(vpaths[y + x*(size-1)]?cEmpty:cWall);
            }
        }
        putchar('\n');
    }

    free(hpaths);
    free(vpaths);

    return 0;
}

