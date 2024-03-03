/*  Advent of Code 2023 Day 11 Part 1.
    Author: João Diniz.
    joaodiniz@msn.com
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum {
    MAXCHAR = 1000,
    MAXROWS = 200,
    FACTOR = 999999
    //FACTOR = 999999
};

struct galaxy {
    int n; // number.
    unsigned long r; // row.
    unsigned long c; // column.
};

unsigned long long sub(unsigned long long a, unsigned long long b);


int main(void)
{
    FILE *f = fopen("input.txt", "r");
    if (f == NULL) {
        printf("File not found!\n");
        return -1;
    }
    int r = 0;
    char *m[MAXROWS] = {};
    char line[MAXCHAR] = {};
    while (fgets(line, MAXCHAR, f) != NULL) {
        char *p = strtok(line, "\n");
        m[r] = (char*)malloc(2 * (strlen(p) + 1));
        strcpy(m[r++], p);
    }
    fclose(f);

    int i, j, k, nog;
    int rowsnogalaxy[100] = {};
    int length = strlen(m[0]);
    int nrows = 0;
    // Look for rows with no galaxy.
    for (i = 0; i < r; i++) {
        for (j = 0; j < length; j++) {
            if (*(m[i] + j) != '.') {
                break;
            }
            if (j == length - 1) {
                rowsnogalaxy[nrows++] = i;
                printf("row %i\n", i);
                /* Rows 3 and 7 */
                // Move the rows one line bellow.
                /*m[r] = (char*)malloc(2 * length);
                for (k = r; k > i; k--) {
                    strcpy(m[k], m[k - 1]);
                } */
                //r++;
                //i++;
            }
        }
    }

    int colsnogalaxy[100] = {};
    int ncols = 0;
    // Check for columns with no galaxy.
    for (j = 0; j < length; j++) {
        for (i = 0; i < r; i++) {
            if (*(m[i] + j) != '.') {
                break;
            }
            if (i == r - 1) {
                printf("Columns with no galaxy %i\n", j);
                /* Cols 2, 5, 8*/
                colsnogalaxy[ncols++] = j;
                //dcol(j, m, r, length);
                //j++;
                //length++;
            }
        }
    }

    /* We don't need to re-draw the map
       with numbers, we need to know
       how much # are and where.*/

    // Count #.
    int gn = 0;
    struct galaxy g[500] = {};
    for (i = 0; i < r; i++) {
        for (j = 0; j < length; j++) {
            if (m[i][j] == '#') {
                //printf("%s", m[i]);
                gn++;
                // galaxy
                g[gn].n = gn;

                // row
                int add = 0;
                for (int a = 0; a < nrows; a++) {
                    if (i > rowsnogalaxy[a]) {
                        add += FACTOR;
                    }
                }
                g[gn].r = i + add ;

                add = 0;
                for (int a = 0; a < ncols; a++) {
                    if (j > colsnogalaxy[a]) {
                        add += FACTOR;
                    }
                }
                //col
                g[gn].c = j + add;
            }
        }
    }
    printf("There are %i galaxies\n", gn);

    // Generate all pair points;
    int tpairs = 0;
    unsigned long long sumatp = 0;
    for (i = 1; i <= gn; i++) {
        for (j = i + 1; j <= gn; j++) {
            //printf("%i %i \n", i, j);
            sumatp += (sub(g[i].r, g[j].r) + sub(g[i].c, g[j].c));
            tpairs++;
        }
    }
    printf("Sum of lengths: %llu", sumatp);
}


unsigned long long sub(unsigned long long a, unsigned long long b)
{
    return (a > b) ? (a - b) : (b - a);
}

