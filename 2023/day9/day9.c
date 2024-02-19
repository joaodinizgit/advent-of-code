/*  Advent of Code 2023 Day 9 Part 1
    Author: João Diniz
    joaodiniz@msn.com
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {
    MAXCHAR = 1000

};

int nextval(int *p, int limit);

int total = 0;

int main(void)
{
    // Copy data of file in a variable.
    FILE *f = fopen("example.txt", "r");
    char *line;
    int hist[200][30];
    int lc = 0;     // Line count;
    int nvals;
    int i, j;
    int sexv = 0;

    line = malloc(MAXCHAR * sizeof(char));
    while (fgets(line, MAXCHAR, f)) {
        nvals = 0;
        char *p;
        p = strtok(line, " ");
        //printf("Line %s \n", p);
        hist[lc][nvals] = atoi(p);
        nvals++;
        while (p != NULL) {
            p = strtok(NULL, " ");
            if (p != NULL) {
                //printf("%s \n", p);
                hist[lc][nvals] = atoi(p);
                nvals++;
            }
        }
        lc++;
    }

    printf("There are: %i lines, nvalues %i\n", lc, nvals);
    for (i = 0; i < lc; i++) {
        //for (j = 0; j < nvals; j++) {
            //printf("%i\n", hist[i][j]);
            nextval(hist[i], nvals);
        //}
    }

    printf("TOTAL IS %i", total);

}

int nextval(int *p, int limit) {
    int i, j, dif;
    int tmp[limit];
    j = 0;
    for (i = 0; i < limit - 1 ; i++) {
        //printf("%i ", *(p + i));
        // Subtract each one with the previous
        dif = *(p + i + 1) - *(p + i);
        //printf("Difference %i \n", dif);
        tmp[j] = dif;
        j++;
    }
    printf("\n");

    // Sum the last temp with the last of p
    total += *(p + limit - 1);
    for (i = 0; i < j; i++) {
        printf("%i ", tmp[i]);
    }
    printf("\n");

    for (i = 0; i < j; i++) {
        if (tmp[i] > 0) {
            nextval(tmp, j);
            break;
        }
    }
}
