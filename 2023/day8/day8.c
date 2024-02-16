/*  Advent of Code 2023, Day8 Part 1
    Author: João Diniz.
    joaodiniz@msn.com
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXCHAR     500
#define CHARNODE    20      // "AAA = (BBB, CCC)\n\0"

typedef struct node {
    char *name;
    char *left;
    char *right;
}node;

int fe(char *c, int limit, node *n);

int main(void)
{
    FILE *f = fopen("input.txt", "r");
    if (f == NULL) {
        printf("FILE NOT FOUND! \n");
        return 0;
    }

    char *line = malloc(MAXCHAR * sizeof(char));
    fgets(line, MAXCHAR, f);
    strtok(line, "\n");
    char *d = malloc(strlen(line) * sizeof(char));
    strcpy(d, line);
    free(line);

    node n[700] = {};

    line = malloc(CHARNODE * sizeof(char));
    int c = 0;
    while (fgets(line, CHARNODE, f)) {
        if (*line != '\n' && *line != ' ' && *line != '\t') {
            //printf("LINE ");
            // AAA = (BBB, CCC)
            char *p;
            p = strtok(line, " = ");
            n[c].name = malloc(4 * sizeof(char));
            strcpy(n[c].name, p);
            p = strtok(NULL, " = (,");
            n[c].left = malloc(4 * sizeof(char));
            strcpy(n[c].left, p);
            p = strtok(NULL, " )");
            n[c].right = malloc(4 * sizeof(char));
            strcpy(n[c].right, p);
            c++;
        }
    }

    int counter = 0;
    int index = fe("AAA", c, n);
    int i = 0;
    while (strcmp(n[index].name, "ZZZ") != 0) {
        if (d[i] == 'L') {
            index = fe(n[index].left, c, n);
        } else if (d[i] == 'R') {
            index = fe(n[index].right, c, n);
        }
        if (i == strlen(d) - 1) {
            i = 0;
        } else {
            i++;
        }
        counter++;
    }
    printf("COUNTER %i", counter);
}

int fe(char *c, int limit, node *n)
{
    int i;
    for (i = 0; i < limit; i++) {
        if (strcmp(n[i].name, c) == 0) {
            return i;
        }
    }
}

