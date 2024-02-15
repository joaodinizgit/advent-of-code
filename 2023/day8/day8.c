/*  Advent of Code 2023, Day8 Part 1
    Author: João Diniz.
    joaodiniz@msn.com
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXCHAR     1000


int main(void)
{
    char *line = malloc(1000 * sizeof(char));

    // Read data from file.
    FILE *f = fopen("input.txt", "r");
    if (f == NULL) {
        printf("FILE NOT FOUND! \n");
        return 0;
    }

    // First line will take the RLs.
    fgets(line, MAXCHAR, f);
    strtok(line, "\n");
    char *rl = malloc(strlen(line) * sizeof(char));
    strcpy(rl, line);
    printf("%s", rl);
    free(line);







}