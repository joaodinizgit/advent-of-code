/*  Advent of Code 2023 Part 1.
    Author: João Diniz.
    joaodiniz@msn.com
*/
#include <stdio.h>
#include <string.h>

enum {
    MAXCOLS = 1000,
    MAXROWS = 1000
};

void upo(char (*platform)[MAXCOLS], int x, int y, int row, int lenline);


int main(void)
{
    FILE *f = fopen("input.txt", "r");
    if (f == NULL) {
        printf("File not found!\n");
        return(-1);
    }

    int row = 0;
    char line[1000] = {};
    char platform[MAXROWS][MAXCOLS] = {};
    while (fgets(line, MAXCOLS, f) != NULL) {
        char *p = strtok(line, "\n");
        strcpy(platform[row], p);
        row++;
    }

    int lenline = strlen(platform[0]);
    int j = 0;
    // Scan through rows looking for "O".
    for (int i = 0; i < row; i++) {
        for (j = 0; j < lenline; j++) {
            if (platform[i][j] == 'O') {
                // Up the O until # or first row.
                upo(&platform[0], i, j, row, lenline);
            }
        }
    }

    int totalp1 = 0;
    int obyline = 0;

    printf("Rows are: %i, lenline: %i\n", row, lenline);
    // Count O per row and multiply by rown number.
    for (int i = 0; i < row; i++) {
        printf("%s\n", platform[i]);
        for (j = 0; j < lenline; j++) {
            if (platform[i][j] == 'O') {
                obyline++;
            }
        }
        totalp1 += obyline * (row - i);
        obyline = 0;
    }

    printf("Total p1 are: %i\n", totalp1);
}


void upo(char (*platform)[MAXCOLS], int x, int y, int row, int lenline)
{
    if (x <= 0 || platform[x - 1][y] == '#') {
        return;
    }

    if (platform[x - 1][y] == '.') {
        platform[x][y] = '.';
        platform[x - 1][y] = 'O';
        return upo(platform, x - 1, y, row, lenline);
    }
}