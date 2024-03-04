/*  Advent of Code Day 10 Part 1 and 2.
    Author: João Diniz.
    joaodiniz@msn.com
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum {
    MAXCHAR = 1000,
    MAXROWS = 200,
    MAXPOINTS = 15000
};

typedef struct point {
    int x, y;
}point;

int isinpolygon(point *polygon, int n, point p);
void nextpd(int *r, int *c, char *map[], char *d);
int notpp(point p, point *polygon, int limit);


int main(void)
{
    FILE *f = fopen("input.txt", "r");
    if (f == NULL) {
        printf("File not foud!\n");
        exit(1);
    }

    //char *line = NULL;
    char *map[MAXROWS] = {};
    int nrows = 0;
    int ncols = 0;

    char *line = (char*)malloc(MAXCHAR);
    if (line == NULL) {
        printf("Failed in allocation memory.\n");
        exit(1);
    }

    while (fgets(line, MAXCHAR, f) != NULL) {
        char *p = strtok(line, "\n");
        map[nrows] = (char*)malloc(strlen(p) + 1);
        if (map[nrows] == NULL) {
            printf("Failed in allocation memory.\n");
            exit(1);
        }
        strcpy(map[nrows++], p);
    }

    ncols = strlen(map[0]);
    free(line);
    fclose(f);

    int i, j;
    int row, col;
    for (i = 0; i < nrows; i++) {
        for (j = 0; j < ncols; j++) {
            if (map[i][j] == 'S') {
                row = i;
                col = j;
                i += nrows;
                break;
            }
        }
    }

    point s = {row, col};
    char mapvisual[nrows][ncols];
    for (i = 0; i < nrows; i++) {
        for (j = 0; j < ncols; j++) {
            mapvisual[i][j] = 'O';
        }
    }

    char dir[1] = {};    // Direction
    int npoints = 0;

    point polygon[MAXPOINTS] = {};
    polygon[npoints].x = row;
    polygon[npoints].y = col;
    mapvisual[row][col] = map[row][col];
    nextpd(&row, &col, map, dir);
    npoints++;

    while (row != s.x || col != s.y) {
        polygon[npoints].x = row;
        polygon[npoints].y = col;
        mapvisual[row][col] = map[row][col];
        nextpd(&row, &col, map, dir);
        npoints++;
    }
    printf("Answer Part 1. Farthest point: %i\n", npoints/2);

    int ptsin = 0;
    for (i = 0; i < nrows; i++) {
        for (j = 0; j < ncols; j++) {
            point p = {i, j};
            if (notpp(p, polygon, npoints) && (isinpolygon(polygon, npoints, p))) {
                mapvisual[p.x][p.y] = 'I';
                ptsin++;
            }
        }
    }
    printf("Answer Part 2. Total points inside polygon: %i\n", ptsin);

    // Extra: Print all the map.
    for (i = 0; i < nrows; i++) {
        for (j = 0; j < ncols; j++) {
            printf("%c", mapvisual[i][j]);
        }
        printf("\n");
    }

    for (i = 0; i < nrows; i++) {
        free(map[i]);
    }
    return 0;
}


// Find the next point and direction.
void nextpd(int *r, int *c, char *map[], char *d)
{
    char tile = map[*r][*c];
    //  r: row, c: column, d: direction.
    if (tile == 'S') {
        if ((*r - 1) >= 0 && (map[*r - 1][*c] == '7' || map[*r - 1][*c] == '|' || map[*r - 1][*c] == 'F')) {
            --*r;
            *d = 'N';
        } else if (((*c + 1) <= strlen(map[0])) && (map[*r][*c + 1] == '-' || map[*r][*c + 1] == '7' || map[*r][*c + 1] == 'J')) {
            ++*c;
            *d = 'E';
        } else if (((*c - 1) >= 0) && (map[*r][*c - 1] == '-' || map[*r][*c - 1] == 'L' || map[*r][*c - 1] == 'F')) {
            --*c;
            *d = 'W';
        } else if ((map[*r + 1][*c] == '|' || map[*r + 1][*c] == 'J' || map[*r + 1][*c] == 'L')) {
            ++*r;
            *d = 'S';
        }
    } else if (tile == '-') {
        if (*d == 'E') {
            ++*c;
        } else if (*d == 'W') {
            --*c;
        }
    } else if (tile == '7') {
        if (*d == 'E') {
            ++*r;
            *d = 'S';
        } else if (*d == 'N') {
            --*c;
            *d = 'W';
        }
    } else if (tile == '|') {
        if (*d == 'S') {
            ++*r;
        } else if (*d == 'N') {
            --*r;
        }
    } else if (tile == 'J') {
        if (*d == 'S') {
            --*c;
            *d = 'W';
        } else if (*d == 'E') {
            --*r;
            *d = 'N';
        }
    } else if (tile == 'L') {
        if (*d == 'W') {
            --*r;
            *d = 'N';
        } else if (*d == 'S') {
            ++*c;
            *d = 'E';
        }
    } else if (tile == 'F') {
        if (*d == 'W') {
            ++*r;
            *d = 'S';
        } else if (*d == 'N') {
            ++*c;
            *d = 'E';
        }
    }
}


// Check if a point is inside a polygon.
int isinpolygon(point *polygon, int n, point p) {
    int i, j, c = 0;
    for (i = 0, j = n - 1; i < n; j = i++) {
        if (((polygon[i].y > p.y) != (polygon[j].y > p.y)) &&
            (p.x < (polygon[j].x - polygon[i].x) * (p.y - polygon[i].y) / (polygon[j].y - polygon[i].y) + polygon[i].x))
            c = !c;
    }
    return c;
}

// Check if the point is not a polygonal point.
int notpp(point p, point *polygon, int limit)
{
    int i;
    for (i = 0; i < limit; i++) {
        if ((p.x == polygon[i].x) && (p.y == polygon[i].y)) {
            return 0;
        }
    }
    return 1;
}

// Answers for "input.txt": Part 1: 6867. Part 2: 595