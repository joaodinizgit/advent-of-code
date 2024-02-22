/*  Advent of Code Day 10 Part 1
    Author: João Diniz.
    joaodiniz@msn.com
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum {
    MAXCHAR = 1000,
    MAXCOLS = 140
};

int main(void)
{
    FILE *f = fopen("example1.txt", "r");
    if (f == NULL) {
        printf("File not foud!\n");
        return 1;
    }

    char *line;
    char *map[MAXCOLS] = {};
    int nrows = 0;
    int i;

    line = malloc(MAXCHAR * sizeof(char));
    while (fgets(line, MAXCHAR, f) != NULL) {
        char *p;
        p = strtok(line, "\n");
        map[nrows] = malloc((strlen(p) + 1) * sizeof(char));
        strcpy(map[nrows], p);
        nrows++;
    }

    free(line);
    fclose(f);

    for (i = 0; i < nrows; i++) {
        printf("%s \n", map[i]);
    }

}