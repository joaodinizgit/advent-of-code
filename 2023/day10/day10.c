/*  Advent of Code Day 10 Part 1
    Author: João Diniz.
    joaodiniz@msn.com
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum {
    MAXCHAR = 1000,
    MAXROWS = 140
};

void rush(int *r, int *c, char *map[], char *d);

int main(void)
{
    FILE *f = fopen("input.txt", "r");
    if (f == NULL) {
        printf("File not foud!\n");
        return 1;
    }

    char *line;
    char *map[MAXROWS] = {};
    int nrows = 0;
    int i, j;

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
    int row = 0;
    int col = 0;
    int srow = 0; // Position of S
    int scol = 0; // Position of S
    for (i = 0; i < nrows; i++) {
        for (j = 0; j < strlen(map[i]); j++) {
            if (map[i][j] == 'S') {
                row = i;
                col = j;
                srow = i;
                scol = j;
                break;
            }
        }
    }
    char dir[1];    // Direction
    printf("%c at map[%i][%i] \n" , map[row][col], row, col); // Start point.
    int counter = 0;
    rush(&row, &col, map, dir);
    while (row != srow || col != scol) {
        printf("map[%i][%i] %c \n", row, col, map[row][col]);
        rush(&row, &col, map, dir);
        counter++;
    }
    printf("Steps are: %i\n", counter + 1);
    printf("Answer Part 1. Steps are: %i\n", counter/2 + 1);
}

void rush(int *r, int *c, char *map[], char *d)
{
    char tile   = map[*r][*c];
    //char teast  = map[*r][*c + 1];
    //char tsouth = map[*r + 1][*c];
    //char twest  = map[*r][*c - 1];
    //char tnorth = map[*r - 1][*c];
    //printf("%c\n", *d);

    // S will have exactly two connected pipes
    if (tile == 'S' && (map[*r - 1][*c] == '7' || map[*r - 1][*c] == '|' || map[*r - 1][*c] == 'F')) {
        printf("Start at NORTH\n");
        *r = *r - 1;
        *d = 'N';
    } else if (tile == 'S' && (map[*r][*c + 1] == '-' || map[*r][*c + 1] == '7' || map[*r][*c + 1] == 'J')) {
        printf("Start at EAST\n");
        *c = *c + 1;
        *d = 'E';
    } else if (tile == 'S' && (map[*r + 1][*c] == '|' || map[*r + 1][*c] == 'J' || map[*r + 1][*c] == 'L')) {
        printf("Start at SOUTH\n");
        *r = *r + 1;
        *d = 'S';
    } else if (tile == 'S' && (map[*r][*c - 1] == '-' || map[*r][*c - 1] == 'L' || map[*r][*c - 1] == 'F')) {
        printf("Start at WEST\n");
        *c = *c - 1;
        *d = 'W';
    } else if (tile == '-' && *d == 'E') {
        *c = *c + 1;
        *d = 'E';
    } else if (tile == '-' && *d == 'W') {
        *c = *c - 1;
        *d = 'W';
    } else if (tile == '7' && *d == 'E') {
        *r = *r + 1;
        *d = 'S';
    } else if (tile == '7' && *d == 'N') {
        *c = *c - 1;
        *d = 'W';
    } else if (tile == '|' && *d == 'S') {
        *r = *r + 1;
        *d = 'S';
    } else if (tile == '|' && *d == 'N') {
        *r = *r - 1;
        *d = 'N';
    } else if (tile == 'J' && *d == 'S') {
        *c = *c - 1;
        *d = 'W';
    } else if (tile == 'J' && *d == 'E') {
        *r = *r - 1;
        *d = 'N';
    } else if (tile == 'L' && *d == 'W') {
        *r = *r - 1;
        *d = 'N';
    } else if (tile == 'L' && *d == 'S') {
        *c = *c + 1;
        *d = 'E';
    } else if (tile == 'F' && *d == 'W') {
        *r = *r + 1;
        *d = 'S';
    } else if (tile == 'F' && *d == 'N') {
        *c = *c + 1;
        *d = 'E';
    }



}