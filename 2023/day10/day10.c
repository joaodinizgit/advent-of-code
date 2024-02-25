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
void rush(int *r, int *c, char *map[], char *d);
int isnotpp(point p, point *polygon, int limit);


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
        map[nrows] = malloc((strlen(p) + 1) * sizeof(char));
        strcpy(map[nrows], p);
        nrows++;
    }
    ncols = strlen(map[0]);

    free(line);
    fclose(f);

    int row = 0;
    int col = 0;
    point s = {};
    for (i = 0; i < nrows; i++) {
        for (j = 0; j < ncols; j++) {
            if (map[i][j] == 'S') {
                row = i;
                col = j;
                s.x = i;
                s.y = j;
                i += nrows;
                break;
            }
        }
    }

    char mapvisual[nrows][ncols];
    for (i = 0; i < nrows; i++) {
        for (j = 0; j < ncols; j++) {
            mapvisual[i][j] = 'O';
        }
    }

    char dir[1];    // Direction
    int npoints = 0;

    point polygon[MAXPOINTS] = {};
    polygon[npoints].x = row;
    polygon[npoints].y = col;
    mapvisual[row][col] = map[row][col];
    rush(&row, &col, map, dir);

    npoints++;
    // Will flow through all points ultil return to S point.
    while (row != s.x || col != s.y) {
        polygon[npoints].x = row;
        polygon[npoints].y = col;
        mapvisual[row][col] = map[row][col];
        rush(&row, &col, map, dir);
        npoints++;
    }
    printf("Answer Part 1. Steps are: %i\n", npoints/2);

    int ptsin = 0;
    for (i = 0; i < nrows; i++) {
        for (j = 0; j < ncols; j++) {
            point p = {i, j};
            // Check if the point is inside the polygon.
            if (isnotpp(p, polygon, npoints) && (isinpolygon(polygon, npoints, p))) {
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


// This function will find the next point and direction.
void rush(int *r, int *c, char *map[], char *d)
{
    char tile = map[*r][*c];
    /*  r: row,
        c: column,
        d: direction
    */

    // S will have exactly two connected pipes.
    if (tile == 'S' && ((*r - 1) >= 0) && (map[*r - 1][*c] == '7' || map[*r - 1][*c] == '|' || map[*r - 1][*c] == 'F')) {
        // Start to North direction.
        *r = *r - 1;
        *d = 'N';
    } else if (tile == 'S' && ((*c + 1) <= strlen(map[0])) && (map[*r][*c + 1] == '-' || map[*r][*c + 1] == '7' || map[*r][*c + 1] == 'J')) {
        // Start to East direction.
        *c = *c + 1;
        *d = 'E';
    } else if (tile == 'S' && ((*c - 1) >= 0) && (map[*r][*c - 1] == '-' || map[*r][*c - 1] == 'L' || map[*r][*c - 1] == 'F')) {
        // Start to West direction.
        *c = *c - 1;
        *d = 'W';
    } else if (tile == 'S' && (map[*r + 1][*c] == '|' || map[*r + 1][*c] == 'J' || map[*r + 1][*c] == 'L')) {
        // Start to South direction.
        *r = *r + 1;
        *d = 'S';
    } else if (tile == '-' && *d == 'E') {
        *c = *c + 1;
    } else if (tile == '-' && *d == 'W') {
        *c = *c - 1;
    } else if (tile == '7' && *d == 'E') {
        *r = *r + 1;
        *d = 'S';
    } else if (tile == '7' && *d == 'N') {
        *c = *c - 1;
        *d = 'W';
    } else if (tile == '|' && *d == 'S') {
        *r = *r + 1;
    } else if (tile == '|' && *d == 'N') {
        *r = *r - 1;
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
int isnotpp(point p, point *polygon, int limit)
{
    int i;
    for (i = 0; i < limit; i++) {
        if ((p.x == polygon[i].x) && (p.y == polygon[i].y)) {
            return 0;
        }
    }
    return 1;
}

/*  Answers for "input.txt":
    Part 1: 6867
    Part 2: 595
*/