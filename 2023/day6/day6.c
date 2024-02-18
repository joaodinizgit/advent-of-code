/*  Advent of Code 2023, Day 6 Part 1 and 2.
    Author: João Diniz.
    joaodiniz@msn.com
*/
#include <stdio.h>

enum {
    MAXROW = 2,
    MAXCOL = 4
};


unsigned long long pways(int t, unsigned long long d);

int f[MAXROW][MAXCOL] = {{49, 78, 79, 80}, {298, 1185, 1066, 1181}};
long long g[] = {49787980, 298118510661181};


int main(void)
{
    int i, nways;
    nways = 1;
    for (i = 0; i < MAXCOL; i++) {
        nways *= pways(f[0][i], f[1][i]);
    }
    printf("Answer Part 1: %i \n", nways);

    nways = 1;
    nways *= pways(g[0], g[1]);
    printf("Answer Part 2: %i \n", nways);
}

unsigned long long pways(int t, unsigned long long d)
{
    unsigned int c;
    unsigned long long r, i;
    c = 0;

    for (i = 0; i < t; i++) {
        r = (t - i) * i;
        if (r > d) {
            c++;
        }
    }
    return c;
}

// Answer for Part 1: 2269432.
// Answer for Part 2: 35865985.