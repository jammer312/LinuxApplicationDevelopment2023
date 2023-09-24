#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
        if (argc < 2) {
                fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
                return 1;
        }

        FILE *f = fopen(argv[1], "rb");
        if (f == NULL) {
                fprintf(stderr, "Couldn't open file `%s`\n", argv[1]);
                return 1;
        }

        fseek(f, 0, SEEK_END);
        long fsize = ftell(f);
        fseek(f, 0, SEEK_SET);

        char *fileContents = malloc(fsize + 1);
        fread(fileContents, fsize, 1, f);
        fclose(f);
        fileContents[fsize] = 0;

        int linesCount = 1;
        for (int i = 0; fileContents[i]; i++) {
                if (fileContents[i] == '\n') {
                        linesCount++;
                }
        }
        char **lines = malloc(sizeof(char*) * linesCount);
        lines[0] = strsep(&fileContents, "\n");
        for (int i = 1; i < linesCount; i++) {
                lines[i] = strsep(&fileContents, "\n");
        }


        initscr();
        noecho();
        cbreak();

        printw("File: %s, lines: %d\n", argv[1], linesCount);
        refresh();

        int height = LINES - 1;
        int width = COLS;

        int boxedHeight = height - 2;
        int boxedWidth = width - 2;

        for (int i = 0; i < linesCount; i++) {
                char *line = lines[i];
                if (strlen(line) > boxedWidth) {
                        line[boxedWidth] = 0;
                }
        }

        WINDOW *window = newwin(height, width, 1, 0);

        int lineOffset = 0;

        while (true) {
                wclear(window);
                box(window, 0, 0);
                for (int i = lineOffset; i < linesCount && i < lineOffset + boxedHeight; i++) {
                        mvwprintw(window, 1 + i - lineOffset, 1, "%s", lines[i]);
                }
                wrefresh(window);

                int ch = getch();
                bool endLoop = false;
                switch (ch) {
                case 27:
                        endLoop = true;
                        break;
                case 32:
                        if (lineOffset < linesCount - boxedHeight) {
                                lineOffset++;
                        }
                        break;
                }
                if (endLoop) {
                        break;
                }
        }

        endwin();
        return 0;
}
