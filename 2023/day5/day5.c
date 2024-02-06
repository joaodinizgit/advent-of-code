#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXCOL      3
#define MAXCHAR     300
#define SENTINEL    -1

#define IN          1
#define OUT         0

#define MAXLINES    50
#define MAXSEEDS    20

#define SIZENUMBER  20


void fvalues(char ln[100]);
void ftitle(char line[100]);
void lowlocnum(int seed, int i);
unsigned int lower_number();


char title[20];
unsigned int temporary[20];

unsigned int seeds[MAXSEEDS];

unsigned int maps[7][MAXLINES][MAXCOL];
unsigned int low_numbers[MAXSEEDS];


int main(void)
{
    char c;
    char line[MAXCHAR];
    int i, j, k, l, m, n, o, p, q, sm;
    k = 0;
    l = 0;
    m = 0;
    n = 0;
    o = 0;
    p = 0;
    q = 0;
    sm = 0;

    FILE *f;
    f = fopen("input.txt", "r");

    // Read every line from file
    while (fgets(line, MAXCHAR, f)) {
        if (isalnum(*line) > 0) {
            ftitle(line);

            if (strcmp(title, "seeds") == 0) {
                fvalues(line);
                for (i = 0; i < MAXSEEDS; ++i) {
                    seeds[i] = temporary[i];
                }
            } else if (strcmp(title, "seedtosoil") == 0) {
                if (isdigit(*line)) {
                    fvalues(line);
                    for (i = 0; i < MAXCOL; ++i) {
                        maps[0][k][i] = temporary[i];
                    }
                    maps[0][k+1][0] = SENTINEL;
                    ++k;
                }
            } else if (strcmp(title, "soiltofertilizer") == 0) {
                if (isdigit(*line)) {
                    fvalues(line);
                    for (i = 0; i < MAXCOL; ++i) {
                        maps[1][l][i] = temporary[i];
                    }
                    maps[1][l+1][0] = SENTINEL;
                    ++l;
                }
            } else if (strcmp(title, "fertilizertowater") == 0) {
                if (isdigit(*line)) {
                    fvalues(line);
                    for (i = 0; i < MAXCOL; ++i) {
                        maps[2][m][i] = temporary[i];
                    }
                    maps[2][m+1][0] = SENTINEL;
                    ++m;
                }
            } else if (strcmp(title, "watertolight") == 0) {
                if (isdigit(*line)) {
                    fvalues(line);
                    for (i = 0; i < MAXCOL; ++i) {
                        maps[3][n][i] = temporary[i];
                    }
                    maps[3][n+1][0] = SENTINEL;
                    ++n;
                }
            } else if (strcmp(title, "lighttotemperature") == 0) {
                if (isdigit(*line)) {
                    fvalues(line);
                    for (i = 0; i < MAXCOL; ++i) {
                        maps[4][o][i] = temporary[i];
                    }
                    maps[4][o+1][0] = SENTINEL;
                    ++o;
                }
            } else if (strcmp(title, "temperaturetohumidity") == 0) {
                if (isdigit(*line)) {
                    fvalues(line);
                    for (i = 0; i < MAXCOL; ++i) {
                        maps[5][p][i] = temporary[i];
                    }
                    maps[5][p+1][0] = SENTINEL;
                    ++p;
                }
            } else if (strcmp(title, "humiditytolocation") == 0) {
                if (isdigit(*line)) {
                    fvalues(line);
                    for (i = 0; i < MAXCOL; ++i) {
                        maps[6][q][i] = temporary[i];
                    }
                    maps[6][q+1][0] = SENTINEL;
                    ++q;
                }
            }
        }
    }

    // For Part 1:
    for (i = 0; i < MAXSEEDS; ++i) {
        lowlocnum(seeds[i], i);
        printf("%lu ",  seeds[i]);
    }

    printf("Lower Locations:\n");
    for (i = 0; i < 20; ++i) {
        printf("%lu ", low_numbers[i]);
    }
    printf("\n");

    // Find the lower number
    printf("LOWER NUMBER IS: %u\n", lower_number());


    for (k = 0; k < 7; ++k){
        printf("***MAP %d***\n", k);
        i = 0;
        while (maps[k][i][0] != -1) {
            printf("Linha %i: ", i );
            for (j = 0; j < MAXCOL; ++j) {
                printf("%lu ", maps[k][i][j]);
            }
            printf("\n");
            ++i;
        }
    }
}


// Find title of values in file
void ftitle(char line[])
{
    int i, j, status;
    j = 0;
    status = OUT;
    for (i = 0; i < strlen(line); ++i) {
        if (isalpha(line[i])) {
            status = IN;
            title[j] = line[i];
            ++j;
        } else if (status == IN && line[i] == ' ') {
            title[j] = '\0';
            return;
        }
    }
    return;
}

// Find file's values
void fvalues(char ln[])
{
    char buffer[15];
    int i, j, k, status;
    j = k = 0;
    status = OUT;
    for (i = 0; i < strlen(ln); ++i ) {
        if (ln[i] != '\n') {
            if (isdigit(ln[i])) {
                buffer[j] = ln[i];
                status = IN;
                ++j;
            } else if (status == IN){
                buffer[j] = '\0';
                j = 0;
                temporary[k] = atol(buffer);
                ++k;
                status = OUT;
            }
        }
    }
    if (status == IN) {
        buffer[j] = ln[i];
        temporary[k] = atol(buffer);
        j = 0;
        k = 0;
    }
}


// Part 1
void lowlocnum(int seed, int index)
{
    int map, line, j;
    for (map = 0; map < 7; ++map){
        line = 0;
        while (maps[map][line][0] != -1) {
            if (seed >= maps[map][line][1] && seed < maps[map][line][1] + maps[map][line][2]) {
                seed = seed - maps[map][line][1] + maps[map][line][0];
                break;
            }
            ++line;
        }
    }
    low_numbers[index] = seed;
}

unsigned int lower_number()
{
    int i, j;
    unsigned int lower;
    lower = 4294967295;

    for (i = 0; i < 1; ++i) {
        for (j = 0; j < MAXSEEDS; ++j) {
            if (low_numbers[i] <= low_numbers[j] && low_numbers[i] < lower) {
                lower = low_numbers[i];
            } else if (low_numbers[j] < lower) {
                lower = low_numbers[j];
            }
        }
    }
    return lower;
}