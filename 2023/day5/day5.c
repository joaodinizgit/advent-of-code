/*  Advent of Code 2023, Day 5 Part 1 and 2.
    Author: João Diniz
    joaodiniz@msn.com
*/
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXCHAR         300
#define SENTINEL        -1
#define IN              1
#define OUT             0
#define MAXROWS         50
#define MAXCOL          3
#define MAXSEEDS        20
#define SIZENUMBER      20
#define MAXSAMPLES      20000

void fvalues(char ln[100]);
void ftitle(char line[100]);
void low_loc_nums(unsigned int seed, int i, unsigned int *ptr[2]);
void lower_number(unsigned int *arr[2], int limit, unsigned int *lowest_pair[2]);

char title[20];
unsigned int temporary[20];

unsigned int seeds[MAXSEEDS];
unsigned int maps[7][MAXROWS][MAXCOL];
unsigned int low_numbers[MAXSEEDS];

int main(void)
{
    char c;
    char line[MAXCHAR];
    int i, j, k, m, status;

    FILE *f;
    f = fopen("input.txt", "r");

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

        } else if (isblank(*line) | *line == '\n') {
            if (status == IN) {
                ++m;
                k = 0;
                status = OUT;
            }
        }
    }

    // For Part 1:
    unsigned int *low_numb[2];
    low_numb[0] = (unsigned int *)malloc(20 * sizeof(unsigned int));
    low_numb[1] = (unsigned int *)malloc(20 * sizeof(unsigned int));

    for (i = 0; i < MAXSEEDS; ++i) {
        low_loc_nums(seeds[i], i, low_numb);
    }

    unsigned int *low_n[2];
    low_n[0] = (unsigned int *)malloc(sizeof(unsigned int));
    low_n[1] = (unsigned int *)malloc(sizeof(unsigned int));

    // Find the lower number.
    lower_number(low_numb, MAXSEEDS, low_n);
    printf("Part 1: \n");
    printf("Lower Number is: %lu\n", *low_n[0]);

    free(low_numb[0]);
    free(low_numb[1]);
    free(low_n[0]);
    free(low_n[1]);

    // For part 2
    // Create the ranges.
    unsigned int ranges[10][2];
    j = 0;
    for (i = 0; i < MAXSEEDS; ++i) {
        ranges[j][0] = seeds[i];
        ranges[j][1] = seeds[i] + seeds[i + 1];
        ++i;
        ++j;
    }

    unsigned int *nums[2];
    unsigned int iter;
    unsigned int *ten_lowers[2];
    unsigned int *lowest_pair[2];

    ten_lowers[0] = (unsigned int *)malloc(10 * sizeof(unsigned int));
    ten_lowers[1] = (unsigned int *)malloc(10 * sizeof(unsigned int));

    for (i = 0; i < 10; ++i) {
        j = 0;
        for (iter = ranges[i][0]; iter <= ranges[i][1]; iter += MAXSAMPLES) {
            ++j;
        }

        // nums[0] are the numbers that will be tested and
        // nums[1] are the equivalent seed.
        nums[0] = (unsigned int *)malloc(j * sizeof(unsigned int));
        nums[1] = (unsigned int *)malloc(j * sizeof(unsigned int));

        j = 0;
        for (iter = ranges[i][0]; iter <= ranges[i][1]; iter += MAXSAMPLES) {
            low_loc_nums(iter, j, nums);
            ++j;
        }

        // lowest_pair[0] store the lowest location and
        // lowest_pair[1], the equivalent seed.
        lowest_pair[0] = (unsigned int *)malloc(sizeof(unsigned int));
        lowest_pair[1] = (unsigned int *)malloc(sizeof(unsigned int));

        lower_number(nums, j, lowest_pair);

        *(ten_lowers[0] + i) = *lowest_pair[0];
        *(ten_lowers[1] + i) = *lowest_pair[1];
    }

    free(nums[0]);
    free(nums[1]);
    free(lowest_pair[0]);
    free(lowest_pair[1]);

    printf("Part 2: \n");
    printf("Ten Lowest Pairs: \n");
    printf("Lower Location  \t Seed \n");
    for (i = 0; i < 10; ++i) {
        printf("%lu \t\t %lu\n", *(ten_lowers[0] + i), *(ten_lowers[1] + i));
    }

    // lowest_pair[0] store the lowest location and
    // lowest_pair[1], the equivalent seed.
    lowest_pair[0] = (unsigned int *)malloc(2* sizeof(unsigned int));
    lowest_pair[1] = (unsigned int *)malloc(2* sizeof(unsigned int));

    lower_number(ten_lowers, 10, lowest_pair);
    printf("The approximated lower number is: %lu, with seed: %lu \n", *lowest_pair[0], *lowest_pair[1]);

    //Find the range of the number found
    unsigned int start_range;
    for (i = 0; i < 10; ++i) {
        if (ten_lowers[0][i] == *lowest_pair[0]) {
            printf("The number is in Range: index(%i) %lu %lu\n", i, ranges[i][0], ranges[i][1]);
            start_range = ranges[i][0];
            break;
        }
    }
    // Find the new lowest number with it's equivalent seed
    unsigned int new_limit;
    new_limit = *lowest_pair[1] - start_range;
    //printf("Limit is: %lu\n", new_limit);
    unsigned int h;
    h = 0;

    nums[0] = (unsigned int *)malloc(1000 * sizeof(unsigned int));
    nums[1] = (unsigned int *)malloc(1000 * sizeof(unsigned int));

    for (iter = *lowest_pair[1]; iter > start_range; --iter) {
        low_loc_nums(iter, h, nums);

        if (*(nums[0] + h) > *lowest_pair[0]) {
            printf("The lower Location numbers is: %lu \n",*(nums[0] + h - 1));
            break;
        }
        ++h;
    }
    free(lowest_pair[0]);
    free(lowest_pair[1]);
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
void low_loc_nums(unsigned int seed, int index, unsigned int *ptr[2])
{
    int map, line, j;
    unsigned int seed_before;
    seed_before = seed;
    for (map = 0; map < 7; ++map){
        line = 0;
        while (maps[map][line][0] != SENTINEL) {
            if (seed >= maps[map][line][1] && seed < maps[map][line][1] + maps[map][line][2]) {
                seed = seed - maps[map][line][1] + maps[map][line][0];
                break;
            }
            ++line;
        }
    }
    *(ptr[0] + index) = seed;
    *(ptr[1] + index) = seed_before;
}

void lower_number(unsigned int *arr[2], int limit, unsigned int *lowest_pair[2])
{
    unsigned int lower, j, seed;
    lower = 4294967295;
    for (j = 0; j < limit; ++j) {
        if (*arr[0] <= *(arr[0] + j) && *(arr[0]) < lower) {
            lower = *arr[0];
            seed = *arr[1];
        } else if (*(arr[0] + j) < lower) {
            lower = *(arr[0] + j);
            seed = *(arr[1] + j);
        }
    }
    *lowest_pair[0] = lower;
    *lowest_pair[1] = seed;
}

/*  The answers from the input.txt file are:
    Part 1: 650599855
    Part 2: 1240035
*/