/*  Advent of Code 2023, Day 7 Part 1 and 2.
    Author: João Diniz.
    joaodiniz@msn.com
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum {
    MAXCHAR = 20,
    ROWS    = 1000,
    CARDS   = 5,
    LABELS  = 13,
    NCHARS  = 11,
    TYPES   = 7
};

void type(char *h);
void sort(char n[][NCHARS], int rows);
int conv(char card);
int in(int n, int lc[], int limit);

// c[TYPES]: counters of hands by labes.
int c[TYPES] = {};
char m[TYPES][ROWS][NCHARS] = {};

int main(void)
{
    int i, j;
    char line[MAXCHAR] = {};
    char *p;
    char hands[ROWS][NCHARS] = {};

    FILE *f = fopen("input.txt", "r");
    if (f == NULL) {
        printf("FILE NOT FOUND! \n");
        return 0;
    }

    i = 0;
    while (fgets(line, MAXCHAR, f)) {
        p = strtok(line, "\n");
        strcpy(hands[i++], p);
    }

    for (i = 0; i < ROWS; i++) {
        type(hands[i]);
    }

    fclose(f);

    for (i = 0; i < TYPES; i++) {
        if (c[i] > 1) {
            sort(m[i], c[i]);
        }
    }

    int rank = 1;
    char *bid;
    unsigned int twin = 0;
    for (i = 0; i < TYPES; i++) {
        for (j = 0; j < c[i]; j++) {
            bid = strtok(m[i][j], " ");
            bid = strtok(NULL, " ");
            twin += rank * atoi(bid);
            rank++;
        }
    }
    printf("Answer. Total: %i \n", twin);
    return 0;
}

void type(char *h)
{
    // Count the letters of each hand for each label.
    char *lbs = "AKQJT98765432";
    int lc[LABELS] = {};
    int i, j;
    for (i = 0; i < CARDS; i++) {
        for (j = 0; j < LABELS; j++) {
            if (*(h + i) == *(lbs + j)) {
                lc[j]++;
                break;
            }
        }
    }

    // Start - Included to Part 2.
    // Check if there are "J"s:
    if (lc[3] > 0) {
        int hi_card = 0;
        int highest = 0;
        for (j = 0; j < LABELS; j++) {
            if (j == 3) {
                continue;
            }
            if (lc[j] > highest ) {
                highest = lc[j];
                hi_card = j;
            }
        }
        if (highest > 0) {
            // Sum "J" qty to highest_card.
            lc[hi_card] += lc[3];
            lc[3] = 0;
        }
    }
    // End - Included to Part 2.

    if (in(5, lc, LABELS)) {
        // Five of a Kind
        strcpy(m[6][c[6]], h);
        c[6]++;
    } else if (in(4, lc, LABELS)) {
        // Four of a Kind
        strcpy(m[5][c[5]], h);
        c[5]++;
    } else if ((in(3, lc, LABELS) && in(2, lc, LABELS))) {
        // Full House
        strcpy(m[4][c[4]], h);
        c[4]++;
    } else if ((in(3, lc, LABELS) && in(1, lc, LABELS) == 2)) {
        // Three of a kind
        strcpy(m[3][c[3]], h);
        c[3]++;
    } else if ((in(2, lc, LABELS) == 2 && in(1, lc, LABELS) == 1)) {
        // Two Pair
        strcpy(m[2][c[2]], h);
        c[2]++;
    } else if ((in(2, lc, LABELS) == 1 && in(1, lc, LABELS) == 3)) {
        // One Pair
        strcpy(m[1][c[1]], h);
        c[1]++;
    } else if((in(1, lc, LABELS) == 5)) {
        // High Card
        strcpy(m[0][c[0]], h);
        c[0]++;
    }
}


/* Check if a number is in an array and
   return the quantity. */
int in(int n, int lc[], int limit)
{
    int i, c;
    c = 0;
    for (i = 0; i < limit; i++) {
        if (lc[i] == n) {
            c++;
        }
    }
    return c;
}

// Bubble sort.
void sort(char n[][NCHARS], int rows)
{
    int i, a, b, j, changes;
    char tmp[NCHARS] = {};
    do {
        changes = 0;
        for (j = 0; j < rows - 1; j++) {
            for (i = 0; i < CARDS; i++) {
                a = conv(n[j][i]);
                b = conv(n[j + 1][i]);
                if (a > b) {
                    strcpy(tmp, n[j]);
                    strcpy(n[j], n[j + 1]);
                    strcpy(n[j + 1], tmp);
                    changes++;
                    break;
                } else if (a < b) {
                    break;
                }
            }
        }
    } while (changes > 0);
}


int conv(char card)
{
switch(card) {
case 'A':
    return 14;
case 'K':
    return 13;
case 'Q':
    return 12;
case 'J':
    return 1;   // For Part 1 this value should be "11".
case 'T':
    return 10;
case '9':
    return 9;
case '8':
    return 8;
case '7':
    return 7;
case '6':
    return 6;
case '5':
    return 5;
case '4':
    return 4;
case '3':
    return 3;
case '2':
    return 2;
}
}

/* Answer Part 1: 250347426 */
/* Answer Part 2: 251224870 */

/* For Part 2: change conv() case 'J' from
11 to 1 */