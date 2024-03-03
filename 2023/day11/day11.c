/*  Advent of Code 2023 Day 11 Part 1.
    Author: João Diniz.
    joaodiniz@msn.com
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum {
    MAXCHAR = 1000,
    MAXROWS = 200
};

struct galaxy {
    int n; // number.
    int r; // row.
    int c; // column.
};

void dcol(int col, char *m[], int row, int len);
int sub(int a, int b);


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
    int length = strlen(m[0]);
    // Look for rows with no galaxy and double it.
    for (i = 0; i < r; i++) {
        for (j = 0; j < length; j++) {
            if (*(m[i] + j) != '.') {
                break;
            }
            if (j == length - 1) {
                // Move the rows one line bellow.
                m[r] = (char*)malloc(2 * length);
                for (k = r; k > i; k--) {
                    strcpy(m[k], m[k - 1]);
                }
                r++;
                i++;
            }
        }
    }

    /* Check for columns with no galaxy
       duplicate if found. */
    for (j = 0; j < length; j++) {
        for (i = 0; i < r; i++) {
            if (*(m[i] + j) != '.') {
                break;
            }
            if (i == r - 1) {
                dcol(j, m, r, length);
                j++;
                length++;
            }
        }
    }

    /* We don't need to re-draw the map
       with numbers, we need to know
       how much # are and where.*/

    // Count #.
    int gn = 0;
    struct galaxy g[300] = {};
    for (i = 0; i < r; i++) {
        for (j = 0; j < length; j++) {
            if (m[i][j] == '#') {
                gn++;
                g[gn].n = gn;
                g[gn].r = i;
                g[gn].c = j;
            }
        }
    }
    printf("There are %i galaxies\n", gn);

    // Generate all pair points;
    int tpairs = 0;
    int sumatp = 0;
    for (i = 1; i <= gn; i++) {
        for (j = i + 1; j <= gn; j++) {
            //printf("%i %i \n", i, j);
            sumatp += (sub(g[i].r, g[j].r) + sub(g[i].c, g[j].c));
            tpairs++;
        }
    }
    printf("Sum of lengths: %i", sumatp);
}


int sub(int a, int b)
{
    return (a > b) ? (a - b) : (b - a);
}


// dcol: Double column with no galaxy.
void dcol(int col, char *m[], int row, int len)
{
    int i, j;
    for (i = 0; i < row; i++) {
        for (j = len - 1; j >= col; j--) {
            m[i][j + 1] = m[i][j];
        }
    }
}
