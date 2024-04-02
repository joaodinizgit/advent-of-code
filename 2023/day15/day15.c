/*  Advent of Code 2023 Day 15 Part 1.
    Author: João Diniz.
    joaodiniz@msn.com
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum {
    MAXCHARS = 15000
};

int hash(char *word);

int main(void)
{
    FILE *f = fopen("input.txt", "r");
    if (f == NULL) {
        printf("File not found!\n");
        return(-1);
    }

    char linebuf[MAXCHARS];
    int totalsum = 0;

    while(fgets(linebuf, MAXCHARS, f) != NULL) {
        // printf("%s\n", linebuf);
        char *p = strtok(linebuf, ",");
        // printf("%s\n", p);
        while(p != NULL) {
            // printf("%s\n", p);
            totalsum += hash(p);
            p = strtok(NULL, ",");
        }
    }
    printf("%i\n", totalsum);
}


int hash(char *word)
{
    printf("%s\n", word);
    int curvalue = 0;
    int lenw = strlen(word);
    int i = 0;

    for(i = 0; i < lenw; i++) {
        // printf("%c\n", *(word + i));
        curvalue += *(word + i);
        curvalue *= 17;
        curvalue = curvalue % 256;

    }
    // printf("%i\n", curvalue);
    return curvalue;
}
