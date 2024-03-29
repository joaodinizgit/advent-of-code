/*  Advent of Code 2023 Day 13 Part 1 and 2.
    Author: João Diniz.
    joaodiniz@msn.com
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum {
    MAXCHAR = 1000,
    MAXROWS = 40,
};

int fhori(char *pattern[], int r);
int fvert(int linen, char *pattern[]);

int eqpairh(char *pattern[],int lenline, int r, int perf1, int perf2, char type, int diflim);
int expandheq(char *pattern[], int a, int b, int r, int lenline, int dif, int diflim);

int eqpairv(char *pattern[], int lenline, int r, int perf1, int perf2, char type, int diflim);
int expandhev(char *pattern[], int a, int b, int r, int lenline, int dif, int diflim);

int onedifh = 0;
int totalp1 = 0;
int totalp2 = 0;

int perf1h = 0;
int perf2h = 0;

int perf1v = 0;
int perf2v = 0;


int main(void)
{
    FILE *f = fopen("input.txt", "r");
    if (f == NULL) {
        printf("File not Found!\n");
        return(-1);
    }

    char line[MAXCHAR] = {};
    char *pattern[MAXROWS] = {};
    int r = 0, i = 0, j = 0;
    while (fgets(line, MAXCHAR, f) != NULL) {
        if (line[0] != '\n') {
            char *p = strtok(line, "\n");
            pattern[r] = (char*)malloc(strlen(p) + 1);
            if (pattern[r] == NULL) {
                printf("Failed in allocation memory.\n");
            }
            strcpy(pattern[r], p);
            printf("%s\n", pattern[r]);
            r++;
        } else if (line[0] == '\n') {
            if (fhori(&pattern[0], r) != 0) {
                fvert(r, &pattern[0]);
            }

            for (i = 0; i < r; i++) {
                free(pattern[i]);
            }

            r = 0;
        }
    }
    // Last line of file.
    if (fhori(&pattern[0], r) != 0) {
        fvert(r, &pattern[0]);
    }

    for (i = 0; i < r; i++) {
        free(pattern[i]);
    }

    r = 0;

    fclose(f);
    printf("TOTAL SUM Part 1: %i \n", totalp1);
    printf("TOTAL SUM part 2: %i \n", totalp2);
    return 0;
}


int fhori(char *pattern[], int r)
{
    int lenline = strlen(pattern[0]);
    int perf = -1; // Use for first perfect pair that not exist.
    if (eqpairh(&pattern[0], lenline, r, perf, perf, 'h', 0) == 0) {
        /* Part 2 - Find another equal pair columns or rows that are different
        from found in part 1 with at least one diffrent symbol.*/
        if (eqpairh(&pattern[0], lenline, r, perf1h, perf2h, 'h', 1) == 0) {
            return 0;
        } else if (eqpairv(&pattern[0],lenline, r, perf1h, perf2h, 'h', 1) == 0) {
            return 0;
        }
        return 0;
    }
    return 1;
}


int fvert(int linen, char *pattern[])
{
    int linelen = strlen(pattern[0]);
    int perf = -1;
    if (eqpairv(&pattern[0],linelen, linen, perf, perf, 'v', 0) == 0) {
        /* Find another equal pair columns or rows that are different from found.
        with at least one diffrent symbol. PART 2*/
        if (eqpairh(&pattern[0], linelen, linen, perf1v, perf2v, 'v', 1) == 0) {
            return 0;
        } else if (eqpairv(&pattern[0],linelen, linen, perf1v, perf2v, 'v', 1) == 0) {
            return 0;
        }
        return 0;
    }
    return 1;
}


int eqpairh(char *pattern[],int lenline, int r, int perf1, int perf2, char type, int diflim)
{
    int i = 0, j = 0;
    for (i = 0; i < r - 1; i++) {
        onedifh = 0;
        j = 0;

        while (((pattern[i][j] == pattern[i + 1][j]) || onedifh <= diflim ) && j < lenline) {
            if (pattern[i][j] != pattern[i + 1][j]) {
                onedifh++;
            }
            j++;
        }

        if (onedifh <= diflim) {
            // Use only the diferent from perf1 and perf2.
            if ((perf1 != i) || (perf2 != i + 1) || type != 'h') {
                printf("**EQUA HORIZ %i (%i, %i)\n", onedifh, i, i + 1);
                // Check expand rows equality
                int a = i;
                int b = i + 1;

                if (expandheq(&pattern[0], a, b, r, lenline, 0, diflim) == 0) {
                    if (diflim == 1) {
                        printf("***NEW REFLECT HORIZON (%i, %i)\n", i, i + 1);
                        totalp2 += 100 * (i + 1);
                    } else if (diflim == 0) {
                        printf("***NEW REFLECT HORIZON (%i, %i)\n", i, i + 1);
                        perf1h = i;
                        perf2h = i + 1;
                        totalp1 += 100 * (i + 1);
                    }
                    return 0;
                }
            }
        }
    }
    return 1;
}


int expandheq(char *pattern[], int a, int b, int r, int lenline, int dif, int diflim)
{
    int i = 0, j = 0;

    if (a < 0 || b >= r) {
        return 0;
    }

    while (((pattern[a][i] == pattern[b][i]) || dif <= 1) && pattern[a][i] != '\0' ) {
        if (pattern[a][i] != pattern[b][i]) {
            dif++;
        }
        i++;
    }

    if (dif <= diflim) {
        return expandheq(pattern, a - 1, b + 1, r, lenline, dif, diflim);
    }

    return 1;
}


int eqpairv(char *pattern[], int lenline, int r, int perf1, int perf2, char type, int diflim)
{
    int dif = 0;
    int i = 0;
    int row = 0;

    for (i = 0; i < lenline - 1; i++) {
        dif = 0;
        row = 0;
        while (row < r && ((pattern[row][i] == pattern[row][i + 1]) || dif <= 1)) {
            if (pattern[row][i] != pattern[row][i + 1]) {
                dif++;
            }
            row++;
        }

        if (dif <= diflim) {
            if (perf1 != i || perf2 != i + 1 || type != 'v'){
                printf("**EQUAL VERT IN (%i, %i) \n", i, i + 1);

                // Check equality for expanded.
                if (expandhev(&pattern[0], i, i + 1, r, lenline, 0, diflim) == 0) {
                    if (diflim == 1) {
                        printf("***NEW REFLEC VERT (%i, %i)\n", i, i + 1);
                        totalp2 += i + 1;
                    } else if (diflim == 0) {
                        printf("***NEW REFLEC VERT (%i, %i)\n", i, i + 1);
                        totalp1 += i + 1;
                        perf1v = i;
                        perf2v = i + 1;
                    }
                    return 0;
                }
            }
        }
    }
}


int expandhev(char *pattern[], int a, int b, int r, int lenline, int dif, int diflim)
{

    if (a < 0 || b >= lenline) {
        return 0;
    }

    int row = 0;
    int i = 0;

    for (i = 0; i < lenline; i++) {
        while (row < r && ((pattern[row][a] == pattern[row][b]) || dif <= 1)) {
            if (pattern[row][a] != pattern[row][b]) {
                dif++;
            }
            row++;
        }

        if (dif <= diflim) {
            return expandhev(pattern, a - 1, b + 1, r, lenline, dif, diflim);
        }
    }

    return 1;
}
// Answers for input.txt: P1: 27505, P2: 22906.