/*  Advent of Code 2023 Day 9 Part 1 and 2.
    Author: João Diniz.
    joaodiniz@msn.com
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {
    MAXCHAR = 1000,
    MAXROWS = 200,
    MAXITEMS = 30
};

void nextval(int *p, int limit);
int first_ext(int *p, int limit);

int left[MAXITEMS] = {};
int nleft = 0;
int sum_right = 0;

int main(void)
{
    // Copy data of file in a variable.
    FILE *f = fopen("input.txt", "r");
    if (f == NULL) {
        printf("File not found!\n");
        return 1;
    }
    char *line;
    int hist[MAXROWS][MAXITEMS];
    int lc = 0;     // Line count;
    int nvals;
    int i, j;

    line = malloc(MAXCHAR * sizeof(char));
    while (fgets(line, MAXCHAR, f)) {
        nvals = 0;
        char *p;
        p = strtok(line, " ");
        hist[lc][nvals] = atoi(p);
        nvals++;
        while (p != NULL) {
            p = strtok(NULL, " ");
            if (p != NULL) {
                hist[lc][nvals] = atoi(p);
                nvals++;
            }
        }
        lc++;
    }

    fclose(f);
    free(line);

    int sum_left = 0;
    for (i = 0; i < lc; i++) {
        nextval(hist[i], nvals);
        sum_left += first_ext(left, nleft);
        nleft = 0;
    }

    printf("Sum of extrapolated right is: %i \n", sum_right);
    printf("Sum of extrapolated left is: %i \n", sum_left);
}

// Sum all right extrapolated values.
void nextval(int *p, int limit) {
    int i, j, dif;
    int tmp[limit];
    j = 0;
    for (i = 0; i < limit - 1 ; i++) {
        dif = *(p + i + 1) - *(p + i);
        tmp[j] = dif;
        j++;
    }

    sum_right += *(p + limit - 1);

    /* Copy all first numbers of all iterations in a array.
       to use to calc the left-most history. */
    left[nleft] = *(p + 0);
    nleft++;

    for (i = 0; i < j; i++) {
        if (tmp[i] != 0) {
            nextval(tmp, j);
            break;
        }
    }
}


// Compute and return the extrapolated first number.
int first_ext(int *p, int limit)
{
    int i;
    int res = 0;
    for (i = limit - 1; i >= 0; i--) {
        res = *(p + i) - res;
    }
    return res;
}


/*  Answer Part 1: 2075724761
    Answer Part 2: 1072
*/