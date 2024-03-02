/*  Advent of Code 2023 Day 11 Part 1
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

void doublecol(int col, char *m[], int row);

int main(void)
{
    FILE *f = fopen("example1.txt", "r");
    if (f == NULL) {
        printf("File not found!\n");
        return -1;
    }
    int r = 0;
    char *m[MAXROWS] = {};
    char line[MAXCHAR] = {};
    while (fgets(line, MAXCHAR, f) != NULL) {
        char *p = strtok(line, "\n");
        m[r] = (char*)malloc(strlen(p) + 1);
        strcpy(m[r++], p);
    }

    int i, j, k, nog;
    int length = strlen(m[0]);
    // Look for rows with no galaxy and double it.
    printf("Total rows: %i\n", r);
    for (i = 0; i < r; i++) {
        for (j = 0; j < length; j++) {
            if (*(m[i] + j) != '.') {
                break;
            }
            if (j == length - 1) {
                // Move the rows one line bellow.
                m[r] = (char*)malloc(length);
                for (k = r; k > i; k--) {
                    strcpy(m[k], m[k - 1]);
                }
                r++;
                i++;
            }
        }
    }

    // Check for columns with galaxy.
    for (j = 0; j < length; j++) {
        for (i = 0; i < r; i++) {
            if (*(m[i] + j) != '.') {
                break;
            }
            if (i == r - 1) {
                //printf("Cols w/ no galaxy %i\n", j);
                // Double column to right direction.
                //printf("%s", m[0]);
                doublecol(j, m, r);
                j++;
                length++;
            }
        }
    }

    for (i = 0; i < r; i++) {
        printf("%s\n", m[i]);
    }




}

void doublecol(int col, char *m[], int row)
{
    int i, j;
    int length = strlen(m[0]);
    for (i = 0; i < row; i++) {
        for (j = length - 1; j >= col; j--) {
            m[i][j + 1] = m[i][j];
        }
    }
}