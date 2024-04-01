/*  Advent of Code 2023 Part 1 and 2.
    Author: João Diniz.
    joaodiniz@msn.com
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum {
    MAXCOLS = 200,
    MAXROWS = 200,
    MAXCYCLES = 300,
    LINEBUF = 10010
};

void mvnorth(char (*platform)[MAXCOLS], int x, int y);
void mvwest(char (*platform)[MAXCOLS], int x, int y);
void mvsouth(char (*platform)[MAXCOLS], int x, int y, int row);
void mveast(char (*platform)[MAXCOLS], int x, int y, int row);


int main(void)
{

    FILE *f = fopen("input.txt", "r");
    if (f == NULL) {
        printf("File not found!\n");
        return(-1);
    }

    int row = 0;
    char line[MAXCOLS] = {};
    char platform[MAXROWS][MAXCOLS] = {};

    while (fgets(line, MAXCOLS, f) != NULL) {
        strtok(line, "\n");
        strcpy(platform[row], line);
        row++;
    }

    fclose(f);
    int lenline = strlen(platform[0]);
    int j = 0;
    // Scan through rows looking for "O".
    int repc = 0;
    int flag_found = 0;

    struct repbuf {
        char line[LINEBUF];
        int repn;
        int tnorth;
        int lastcycle;
    }repbuf[200];

    // Start cycle.
    int linerecn = 0;
    int cycle = 0;
    for (cycle = 0; cycle < MAXCYCLES; cycle++) {
        // Move to north.
        for (int i = 0; i < row; i++) {
            for (j = 0; j < lenline; j++) {
                if (platform[i][j] == 'O') {
                    // Up the O until # or first row.
                    mvnorth(&platform[0], i, j);
                }
            }
        }

        // Move to west.
        for (int i = 0; i < row; i++) {
            for (j = 0; j < lenline; j++) {
                if (platform[i][j] == 'O') {
                    mvwest(&platform[0], i, j);
                }
            }
        }

        // Move to south.
        for (int i = row; i >= 0; i--) {
            for (j = 0; j < lenline; j++) {
                if (platform[i][j] == 'O') {
                    mvsouth(&platform[0], i, j, row);
                }
            }
        }

        // Move to east.
        for (int i = 0; i < row; i++) {
            for (j = lenline - 1; j >= 0; j--) {
                if (platform[i][j] == 'O') {
                    mveast(&platform[0], i, j, row);
                }
            }
        }

        // Store all rows platform in one line to look for repetition.
        char buftocmp[LINEBUF] = {};
        for (int i = 0; i < row; i++) {
            strcat(buftocmp, platform[i]);
        }

        // Check if line already stored.
        flag_found = 0;
        for (int i = 0; i < repc; i++) {
            if (strcmp(repbuf[i].line, buftocmp) == 0) {
                repbuf[i].repn++;
                flag_found = 1;
                repbuf[i].lastcycle = cycle;
                break;
            }
        }

        // If not, store it.
        if (flag_found == 0) {
            strcpy(repbuf[repc].line, buftocmp);
            linerecn++;
            repbuf[repc].lastcycle = cycle;
        }

        int totalp1 = 0;
        int obyline = 0;

        // North
        // Count O per row and multiply by rown number.
        for (int i = 0; i < row; i++) {
            for (j = 0; j < lenline; j++) {
                if (platform[i][j] == 'O') {
                    obyline++;
                }
            }
            totalp1 += obyline * (row - i);
            obyline = 0;
        }

        if (flag_found == 0) {
            repbuf[repc].tnorth = totalp1;
        }

        repc++;
    }

    int counter = 0;
    // Calculate interval of repetition.
    for (int i = 0; i < linerecn; i++) {
        if (repbuf[i].repn > 0) {
            ++counter;
        }
    }

    for (int i = 0; i < linerecn; i++) {
        if (repbuf[i].repn > 0) {
            int eqbi = (1000000000 - (repbuf[i].lastcycle + 1)) % counter;
            if (eqbi == 0) {
                printf("Answer P2: %i\n", repbuf[i].tnorth);
                // break;
                return 0;
            }
        }
    }
    return 0;
}


void mvnorth(char (*platform)[MAXCOLS], int x, int y)
{
    if (x <= 0 || platform[x - 1][y] == '#' || platform[x - 1][y] == 'O') {
        return;
    }

    if (platform[x - 1][y] == '.') {
        platform[x][y] = '.';
        platform[x - 1][y] = 'O';
        return mvnorth(platform, x - 1, y);
    }
}


void mvwest(char (*platform)[MAXCOLS], int x, int y)
{
    if (y <= 0 || platform[x][y - 1] == '#' || platform[x][y - 1] == 'O') {
        return;
    }

    if (platform[x][y - 1] == '.') {
        platform[x][y - 1] = 'O';
        platform[x][y] = '.';
        return mvwest(platform, x, y - 1);
    }
}


void mvsouth(char (*platform)[MAXCOLS], int x, int y, int row)
{
    if (x > row || platform[x + 1][y] == '#' || platform[x + 1][y] == 'O') {
        return;
    }

    if (platform[x + 1][y] == '.') {
        platform[x + 1][y] = 'O';
        platform[x][y] = '.';
        return mvsouth(platform, x + 1, y, row);
    }

}


void mveast(char (*platform)[MAXCOLS], int x, int y, int row)
{
    if (x > row || platform[x][y + 1] == '#' || platform[x][y + 1] == 'O') {
        return;
    }

    if (platform[x][y + 1] == '.') {
        platform[x][y + 1] = 'O';
        platform[x][y] = '.';
        return mveast(platform, x, y + 1, row);
    }
}
// Answer Part 1: 109755, Part 2: 90928.