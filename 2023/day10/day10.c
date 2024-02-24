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

// Define a point structure
typedef struct point {
    int x, y;
}point;

int isInsidePolygon(point polygon[], int n, point p);

void rush(int *r, int *c, char *map[], char *d);

int isin(point p, point *polyg, int limit);

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
    int ncols = 0;
    int i, j;

    line = malloc(MAXCHAR * sizeof(char));
    while (fgets(line, MAXCHAR, f) != NULL) {
        char *p;
        p = strtok(line, "\n");
        //printf("%i \n", strlen(p));
        ncols = strlen(p);
        map[nrows] = malloc((strlen(p) + 1) * sizeof(char));

        strcpy(map[nrows], p);
        nrows++;
    }

    //printf("%i", nrows);

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

    int k = 0;
    printf("%c at map[%i][%i] \n" , map[row][col], row, col); // Start point.
    int counter = 0;
    //printf("{%i, %i}, ", row, col);
    point polyg[13734] = {};
    polyg[counter].x = row;
    polyg[counter].y = col;
    counter++;
    rush(&row, &col, map, dir);
    while (row != srow || col != scol) {
        //printf("{%i,%i}, ", row, col);
        // Store the points to use in Part 2.
        polyg[counter].x = row;
        polyg[counter].y = col;
        //printf("map[%i][%i] %c \n", row, col, map[row][col]);
        rush(&row, &col, map, dir);
        //polyg[counter] = {rol, col};
        counter++;
    }
    printf("Steps are: %i\n", counter);
    printf("Answer Part 1. Steps are: %i\n", counter/2);

    /*for (i = 0; i < counter; i++) {
        printf("{%i, %i}, ", polyg[i].x, polyg[i].y);
    }*/



    // PART 2

    // Example: Define a polygon (loop).
    //point polygon[] = {{1, 1}, {1, 2}, {1, 3}, {1, 4}, {1, 5}, {1, 6}, {1, 7}, {1, 8}, {1, 9}, {2, 9}, {3, 9}, {4, 9}, {5, 9}, {6, 9}, {7, 9}, {7, 8}, {7, 7}, {7, 6}, {6, 6}, {5, 6}, {5, 7}, {5, 8}, {4, 8}, {3, 8}, {2, 8}, {2, 7}, {2, 6}, {2,5}, {2,4}, {2,3}, {2,2}, {3,2}, {4,2}, {5,2}, {5,3}, {5,4}, {6,4}, {7,4}, {7,3}, {7,2}, {7,1}, {6,1}, {5,1}, {4,1}, {3,1}, {2,1}};

    int n = sizeof(polyg) / sizeof(polyg[0]);
    printf("%i\n", n);

    int tinside = 0;
    for (i = 0; i < nrows; i++) {
        for (j = 0; j < ncols; j++) {
            point p = {i, j};
            //isin(p);
            // Check if the point is inside the polygon
            if (!isin(p, polyg, counter) && (isInsidePolygon(polyg, n, p))) {
                printf("Point (%i, %i) is inside the polygon.\n", p.x, p.y);
                tinside++;
            }
        }
    }
    printf("Total inside polygon is %i\n", tinside);
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


// Check if a point is inside a polygon
int isInsidePolygon(point polygon[], int n, point p) {
    int i, j, c = 0;
    for (i = 0, j = n - 1; i < n; j = i++) {
        if (((polygon[i].y > p.y) != (polygon[j].y > p.y)) &&
            (p.x < (polygon[j].x - polygon[i].x) * (p.y - polygon[i].y) / (polygon[j].y - polygon[i].y) + polygon[i].x))
            c = !c;
    }
    return c;
}

int isin(point p, point *polyg, int limit)
{
    int i;
    for (i = 0; i < limit; i++) {
        if ((p.x == polyg[i].x) && (p.y == polyg[i].y)) {
            return 1;
        }
    }
    return 0;
}
