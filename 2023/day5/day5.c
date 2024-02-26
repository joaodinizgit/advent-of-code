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
    MAXROWS     = 50,
    MAXCOL      = 3,
    MAXSEEDS    = 20,
    SIZENUMBER  = 20,
    MAXSAMPLES  = 20000,
    MAXMAPS     = 7
};

struct pair{
    unsigned int *seedn;
    unsigned int *locn;
} pair;

void fvalues(char ln[]);
void ftitle(char line[]);
void fnd_locs(unsigned int seed, unsigned int index, struct pair *lns);
void fnd_lowest_loc(struct pair *arr, int limit, struct pair *ln);

char title[20];
unsigned int temporary[20];

unsigned int seeds[MAXSEEDS];
unsigned int maps[MAXMAPS][MAXROWS][MAXCOL];
unsigned int low_numbers[MAXSEEDS];

int main(void)
{
    char c;
    char line[MAXCHAR];
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
                for (i = 0; i < MAXSEEDS; ++i) {
                    seeds[i] = temporary[i];
                }
            } else if (isdigit(*line)) {
                status = IN;
                fvalues(line);
                for (i = 0; i < MAXCOL; ++i) {
                    maps[m][k][i] = temporary[i];
                }
                maps[m][k+1][0] = SENTINEL;
                ++k;
                }

        } else if (isblank(*line) || *line == '\n') {
            if (status == IN) {
                ++m;
                k = 0;
                status = OUT;
            }
        }
    }
    fclose(f);

    struct pair lower_ns;
    lower_ns.seedn = malloc(MAXSEEDS * sizeof(unsigned int));
    lower_ns.locn = malloc(MAXSEEDS * sizeof(unsigned int));

    for (i = 0; i < MAXSEEDS; ++i) {
        fnd_locs(seeds[i], i, &lower_ns);
    }

    struct pair lower_n;
    lower_n.seedn = malloc(sizeof(unsigned int));
    lower_n.locn = malloc(sizeof(unsigned int));

    fnd_lowest_loc(&lower_ns, MAXSEEDS, &lower_n);

    printf("Part 1: \n");
    printf("Lower Number is: %lu\n", *lower_n.locn);

    free(lower_ns.seedn);
    free(lower_ns.locn);
    free(lower_n.seedn);
    free(lower_n.locn);

    unsigned int ranges[10][2];
    j = 0;
    for (i = 0; i < MAXSEEDS; ++i) {
        ranges[j][0] = seeds[i];
        ranges[j][1] = seeds[i] + seeds[i + 1];
        ++i;
        ++j;
    }

    //return 0;

    struct pair nums;
    struct pair ten_lowers;
    struct pair lowest_pair;
    unsigned int iter;

    ten_lowers.seedn = malloc(10 * sizeof(unsigned int));
    ten_lowers.locn = malloc(10 * sizeof(unsigned int));

    for (i = 0; i < 10; ++i) {
        j = 0;
        for (iter = ranges[i][0]; iter <= ranges[i][1]; iter += MAXSAMPLES) {
            ++j;
        }

        nums.seedn = malloc(j * sizeof(unsigned int));
        nums.locn = malloc(j * sizeof(unsigned int));

        j = 0;
        for (iter = ranges[i][0]; iter <= ranges[i][1]; iter += MAXSAMPLES) {
            fnd_locs(iter, j, &nums);
            ++j;
        }

        lowest_pair.seedn = malloc(sizeof(unsigned int));
        lowest_pair.locn = malloc(sizeof(unsigned int));

        fnd_lowest_loc(&nums, j, &lowest_pair);

        *(ten_lowers.seedn + i) = *lowest_pair.seedn;
        *(ten_lowers.locn + i) = *lowest_pair.locn;

        free(lowest_pair.seedn);
        free(lowest_pair.locn);
        free(nums.seedn);
        free(nums.locn);
    }

    printf("Part 2: \n");
    printf("Ten Lowest Pairs: \n");
    printf("Lower Location  \t Seed \n");
    for (i = 0; i < 10; ++i) {
        printf("%lu \t\t %lu\n", *(ten_lowers.locn + i), *(ten_lowers.seedn + i));
    }

    lowest_pair.seedn = malloc(2* sizeof(unsigned int));
    lowest_pair.locn = malloc(2* sizeof(unsigned int));

    fnd_lowest_loc(&ten_lowers, 10, &lowest_pair);
    printf("The approximated lower number is: %lu, with seed: %lu \n", *lowest_pair.locn, *lowest_pair.seedn);

    unsigned int start_range;
    for (i = 0; i < 10; ++i) {
        if (*(ten_lowers.locn + i) == *lowest_pair.locn) {
            printf("The number is in Range: index(%i) %lu %lu\n", i, ranges[i][0], ranges[i][1]);
            start_range = ranges[i][0];
            break;
        }
    }


    // Find the new lowest locations numbers.
    unsigned int h = 0;

    nums.seedn = malloc(1000 * sizeof(unsigned int));
    nums.locn = malloc(1000 * sizeof(unsigned int));

    for (iter = *lowest_pair.seedn; iter > start_range; iter--) {
        fnd_locs(iter, h, &nums);

        if (*(nums.locn + h) > *lowest_pair.locn) {
            printf("The lower Location numbers is: %lu \n",*(nums.locn + h - 1));
            break;
        }
        h++;
    }

    free(lowest_pair.seedn);
    free(lowest_pair.locn);
    free(nums.seedn);
    free(nums.locn);
    free(ten_lowers.locn);
    free(ten_lowers.seedn);

}


// Find title of values in file.
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

// Find file's values numbers.
void fvalues(char line[])
{
    char buffer[15];
    int i, j, k, status;
    j = k = 0;
    status = OUT;
    for (i = 0; i < strlen(line); ++i) {
        if (line[i] != '\n') {
            if (isdigit(line[i])) {
                buffer[j] = line[i];
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
        buffer[j] = line[i];
        temporary[k] = atol(buffer);
        j = 0;
        k = 0;
    }
}


// Find locations numbers.
void fnd_locs(unsigned int seed, unsigned int index, struct pair *lns)
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
            ++row;
        }
    }
    *(lns->seedn + index) = seedsrc;
    *(lns->locn + index) = seed;
}


// Find lowest location number.
void fnd_lowest_loc(struct pair *arr, int limit, struct pair *ln)
{
    unsigned int lower, j, seed;
    lower = 4294967295;
    for (j = 0; j < limit; ++j) {
        if (*arr->locn <= *(arr->locn + j) && *(arr->locn) < lower) {
            lower = *arr->locn;
            seed = *arr->locn;
        } else if (*(arr->locn + j) < lower) {
            lower = *(arr->locn + j);
            seed = *(arr->seedn + j);
        }
    }
    *ln->seedn = seed;
    *ln->locn = lower;
}

/*  The answers from the input.txt file are:
    Part 1: 650599855
    Part 2: 1240035
*/