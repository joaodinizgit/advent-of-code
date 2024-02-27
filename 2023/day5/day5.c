/*  Advent of Code 2023, Day 5 Part 1 and 2.
    Author: João Diniz
    joaodiniz@msn.com
*/
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

enum {
    MAXCHAR     = 300,
    SENTINEL    = -1,
    IN          = 1,
    OUT         = 0,
    MAXMAPS     = 7,
    MAXROWS     = 50,
    MAXCOLS      = 3,
    MAXSEEDS    = 20,
    MAXSAMPLES  = 20000
};

struct pair{
    unsigned int *seedn;
    unsigned int *locn;
} pair;

void fvalues(char ln[]);
void ftitle(char line[]);
void fnd_locs(unsigned int seed, unsigned int i, struct pair *lns);
void fnd_lowest_loc(struct pair *arr, int limit, struct pair *ln);

char title[20];
unsigned int tmp[20];
unsigned int seeds[MAXSEEDS];
unsigned int maps[MAXMAPS][MAXROWS][MAXCOLS];
unsigned int low_numbers[MAXSEEDS];


int main(void)
{
    char c;
    char line[MAXCHAR] = {};
    int i, j, k, m, status;

    FILE *f = fopen("input.txt", "r");
    if (f == NULL) {
        printf("File not found\n");
        return 1;
    }

    m = 0;
    k = 0;
    status = OUT;

    while (fgets(line, MAXCHAR, f)) {
        if (isalnum(*line)) {
            ftitle(line);

            if (strcmp(title, "seeds") == 0) {
                fvalues(line);
                for (i = 0; i < MAXSEEDS; i++) {
                    seeds[i] = tmp[i];
                }
            } else if (isdigit(*line)) {
                status = IN;
                fvalues(line);
                for (i = 0; i < MAXCOLS; i++) {
                    maps[m][k][i] = tmp[i];
                }
                maps[m][k+1][0] = SENTINEL;
                ++k;
                }

        } else if (isblank(*line) || *line == '\n') {
            if (status == IN) {
                m++;
                k = 0;
                status = OUT;
            }
        }
    }
    fclose(f);

    struct pair lower_ns;
    lower_ns.seedn = malloc(MAXSEEDS * sizeof(unsigned int));
    lower_ns.locn = malloc(MAXSEEDS * sizeof(unsigned int));

    for (i = 0; i < MAXSEEDS; i++) {
        fnd_locs(seeds[i], i, &lower_ns);
    }

    struct pair lower_n;
    lower_n.seedn = malloc(sizeof(unsigned int));
    lower_n.locn = malloc(sizeof(unsigned int));

    fnd_lowest_loc(&lower_ns, MAXSEEDS, &lower_n);

    printf("Answer Part 1 - Lowest Location Number is: %lu\n", *lower_n.locn);

    free(lower_ns.seedn);
    free(lower_ns.locn);
    free(lower_n.seedn);
    free(lower_n.locn);

    unsigned int ranges[10][2] = {};
    j = 0;
    for (i = 0; i < MAXSEEDS; i++) {
        ranges[j][0] = seeds[i];
        ranges[j][1] = seeds[i] + seeds[i + 1];
        i++;
        j++;
    }

    struct pair ten_lowers;
    unsigned int iter = 0;

    ten_lowers.seedn = malloc(10 * sizeof(unsigned int));
    ten_lowers.locn = malloc(10 * sizeof(unsigned int));

    for (i = 0; i < 10; i++) {
        j = 0;
        for (iter = ranges[i][0]; iter <= ranges[i][1]; iter += MAXSAMPLES) {
            j++;
        }

        lower_ns.seedn = malloc(j * sizeof(unsigned int));
        lower_ns.locn = malloc(j * sizeof(unsigned int));

        j = 0;
        for (iter = ranges[i][0]; iter <= ranges[i][1]; iter += MAXSAMPLES) {
            fnd_locs(iter, j, &lower_ns);
            j++;
        }

        lower_n.seedn = malloc(sizeof(unsigned int));
        lower_n.locn = malloc(sizeof(unsigned int));

        fnd_lowest_loc(&lower_ns, j, &lower_n);

        *(ten_lowers.seedn + i) = *lower_n.seedn;
        *(ten_lowers.locn + i) = *lower_n.locn;

        free(lower_n.seedn);
        free(lower_n.locn);
        free(lower_ns.seedn);
        free(lower_ns.locn);
    }

    printf("Ten lowest: Location / Seed \n");
    for (i = 0; i < 10; i++) {
        printf("%lu \t\t %lu\n", *(ten_lowers.locn + i), *(ten_lowers.seedn + i));
    }

    lower_n.seedn = malloc(2* sizeof(unsigned int));
    lower_n.locn = malloc(2* sizeof(unsigned int));

    fnd_lowest_loc(&ten_lowers, 10, &lower_n);
    printf("The approximated lower number is: %lu, with seed: %lu \n", *lower_n.locn, *lower_n.seedn);

    unsigned int start_range;
    for (i = 0; i < 10; i++) {
        if (*(ten_lowers.locn + i) == *lower_n.locn) {
            printf("The number is in range: index(%i) %lu %lu\n", i, ranges[i][0], ranges[i][1]);
            start_range = ranges[i][0];
            break;
        }
    }

    // Find the new lowest locations numbers.
    unsigned int h = 0;
    lower_ns.seedn = malloc(1000 * sizeof(unsigned int));
    lower_ns.locn = malloc(1000 * sizeof(unsigned int));

    for (i = *lower_n.seedn; i > start_range; i--) {
        fnd_locs(i, h, &lower_ns);
        if (*(lower_ns.locn + h) > *lower_n.locn) {
            printf("Answer Part 2 - The lower location number is: %lu \n",*(lower_ns.locn + h - 1));
            break;
        }
        h++;
    }

    free(lower_n.seedn);
    free(lower_n.locn);
    free(lower_ns.seedn);
    free(lower_ns.locn);
    free(ten_lowers.locn);
    free(ten_lowers.seedn);
    return 0;
}


// Find title of values in file.
void ftitle(char line[])
{
    int i, j, status;
    j = 0;
    status = OUT;
    for (i = 0; i < strlen(line); i++) {
        if (isalpha(line[i])) {
            status = IN;
            title[j] = line[i];
            j++;
        } else if (status == IN && line[i] == ' ') {
            title[j] = '\0';
            return;
        }
    }
    return;
}

// Find file's values numbers.
void fvalues(char line[])
{
    char buffer[15];
    int i, j, k, status;
    j = k = 0;
    status = OUT;
    for (i = 0; i < strlen(line); i++) {
        if (line[i] != '\n') {
            if (isdigit(line[i])) {
                buffer[j] = line[i];
                status = IN;
                j++;
            } else if (status == IN){
                buffer[j] = '\0';
                j = 0;
                tmp[k] = atol(buffer);
                k++;
                status = OUT;
            }
        }
    }
    if (status == IN) {
        buffer[j] = line[i];
        tmp[k] = atol(buffer);
        j = 0;
        k = 0;
    }
}


// Find the locations numbers.
void fnd_locs(unsigned int seed, unsigned int i, struct pair *lns)
{
    int map, row;
    unsigned int seedsrc;
    seedsrc = seed;
    for (map = 0; map < MAXMAPS; map++){
        row = 0;
        while (maps[map][row][0] != SENTINEL) {
            if (seed >= maps[map][row][1] && seed < maps[map][row][1] + maps[map][row][2]) {
                seed = seed - maps[map][row][1] + maps[map][row][0];
                break;
            }
            row++;
        }
    }
    *(lns->seedn + i) = seedsrc;
    *(lns->locn + i) = seed;
}


// Find the lowest location number.
void fnd_lowest_loc(struct pair *arr, int limit, struct pair *ln)
{
    unsigned int i, lower, seed;
    lower = 4294967295;
    for (i = 0; i < limit; i++) {
        if ((*arr->locn) <= *(arr->locn + i) && *(arr->locn) < lower) {
            lower = *arr->locn;
            seed = *arr->locn;
        } else if (*(arr->locn + i) < lower) {
            lower = *(arr->locn + i);
            seed = *(arr->seedn + i);
        }
    }
    *ln->seedn = seed;
    *ln->locn = lower;
}

/*  The answers to input.txt file are:
    Part 1: 650599855
    Part 2: 1240035
*/