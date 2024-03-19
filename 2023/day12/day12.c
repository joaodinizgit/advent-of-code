/*  Advent of Code 2023 Day 12 Part 1.
    Author: João Diniz.
    joaodiniz@msn.com
*/
#include <stdio.h>
#include <string.h>

enum {
    MAXCHAR = 1000,
};

int main(void)
{
    FILE *f = fopen("example1.txt", "r");
    if (f == NULL) {
        printf("File not found!\n");
        return(-1);
    }
    char line[1000] = {};
    while (fgets(line, MAXCHAR, f) != NULL) {
        //printf("%s", line);
        char *p = strtok(line, "\n");
        p = strtok(line, " ");
        while (p != NULL) {
            printf("%s\n", p);
            p = strtok(NULL, "");
        }
    }
}