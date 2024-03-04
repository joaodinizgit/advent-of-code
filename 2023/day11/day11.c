/*  Advent of Code 2023 Day 11 Part 1 and 2.
    Author: João Diniz.
    joaodiniz@msn.com
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum {
    MAXCHAR = 1000,
    MAXROWS = 200,
    FACTOR = 1000000,
    MAXGALAXS = 500,
    MAXSTORE = 100
};

struct galaxy {
    int r; // row.
    int c; // column.
};

int sub(int a, int b);


int main(void)
{
    FILE *f = fopen("input.txt", "r");
    if (f == NULL) {
        printf("File not found!\n");
        exit(1);
    }

    int r = 0;  // Row.
    char *m[MAXROWS] = {};
    char line[MAXCHAR] = {};
    while (fgets(line, MAXCHAR, f) != NULL) {
        char *p = strtok(line, "\n");
        m[r] = (char*)malloc(strlen(p) + 1);
        if (m[r] == NULL) {
            printf("Failed in allocation memory.\n");
            exit(1);
        }
        strcpy(m[r++], p);
    }
    fclose(f);

    int i, j;
    int rowsnogalaxy[MAXSTORE] = {};
    int length = strlen(m[0]);
    int nrows = 0;
    // Store row number with no galaxy.
    for (i = 0; i < r; i++) {
        for (j = 0; j < length; j++) {
            if (*(m[i] + j) != '.') {
                break;
            }
            if (j == length - 1) {
                rowsnogalaxy[nrows++] = i;
            }
        }
    }

    int colsnogalaxy[MAXSTORE] = {};
    int ncols = 0;
    // Store column number with no galaxy.
    for (j = 0; j < length; j++) {
        for (i = 0; i < r; i++) {
            if (*(m[i] + j) != '.') {
                break;
            }
            if (i == r - 1) {
                colsnogalaxy[ncols++] = j;
            }
        }
    }

    // Count galaxies(#) and store its position.
    int gn = 0;
    struct galaxy g[MAXGALAXS] = {};
    for (i = 0; i < r; i++) {
        for (j = 0; j < length; j++) {
            if (m[i][j] == '#') {
                gn++;
                int add = 0;
                for (int a = 0; a < nrows; a++) {
                    if (i > rowsnogalaxy[a]) {
                        add += FACTOR - 1;
                    }
                }
                g[gn].r = i + add;

                add = 0;
                for (int a = 0; a < ncols; a++) {
                    if (j > colsnogalaxy[a]) {
                        add += FACTOR - 1;
                    }
                }
                g[gn].c = j + add;
            }
        }
    }
    // Calc the distance between all pairs.
    unsigned long long sumlengths = 0;
    for (i = 1; i <= gn; i++) {
        for (j = i + 1; j <= gn; j++) {
            sumlengths += (sub(g[i].r, g[j].r) + sub(g[i].c, g[j].c));
        }
    }
    printf("Sum of lengths: %llu \n", sumlengths);
    for (i = 0; i < r; i++) {
        free(m[i]);
    }
}


int sub(int a, int b)
{
    return (a > b) ? (a - b) : (b - a);
}

// Answers Part 1: 10154062. Part 2: 553083047914.