/*  Advent of Code 2023, Day8 Part 1
    Author: João Diniz.
    joaodiniz@msn.com
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXCHAR     500
#define CHARNODE    20      // "AAA = (BBB, CCC)\n\0"

typedef struct node {
    char *name;
    char *left;
    char *right;
}node;

int fe(char *name, int limit, node *n);
long lcm(long a, long b);
long gcd(long a, long b);


int main(void)
{
    FILE *f = fopen("input.txt", "r");
    if (f == NULL) {
        printf("FILE NOT FOUND! \n");
        return 0;
    }

    char *line = malloc(MAXCHAR * sizeof(char));
    fgets(line, MAXCHAR, f);
    strtok(line, "\n");
    char *d = malloc(strlen(line) * sizeof(char));
    strcpy(d, line);
    free(line);

    node n[700] = {};

    line = malloc(CHARNODE * sizeof(char));
    int c = 0;
    while (fgets(line, CHARNODE, f)) {
        if (*line != '\n' && *line != ' ' && *line != '\t') {
            char *p;
            p = strtok(line, " = ");
            n[c].name = malloc(4 * sizeof(char));
            strcpy(n[c].name, p);
            p = strtok(NULL, " = (,");
            n[c].left = malloc(4 * sizeof(char));
            strcpy(n[c].left, p);
            p = strtok(NULL, " )");
            n[c].right = malloc(4 * sizeof(char));
            strcpy(n[c].right, p);
            c++;
        }
    }
    fclose(f);

    int counter = 0;
    int index = fe("AAA", c, n);
    if (index == -1) {
        printf("No direction found! \n");
        //return 1;
    } else {
        int i = 0;
        while (strcmp(n[index].name, "ZZZ") != 0) {
            if (d[i] == 'L') {
                index = fe(n[index].left, c, n);
            } else if (d[i] == 'R') {
                index = fe(n[index].right, c, n);
            }
            if (i == strlen(d) - 1) {
                i = 0;
            } else {
                i++;
            }
            counter++;
        }
        printf("Answer Part 1 Steps: %i \n", counter);
    }


    // For Part 2
    int count = 0;
    int ewa[10];
    int j = 0;
    for (int i = 0; i < c; i++) {
        if (n[i].name[2] == 'A') {
            ewa[j] = i;
            count++;
            j++;
        }
    }

    for (int i = 0; i < count; i++) {
        printf("Index/names end with A: %i %s \n", ewa[i], n[ewa[i]].name);
    }
    //printf("count: %i \n", count);

    int i = 0;
    counter = 0;
    int totalizer = 0;
    int ind;
    int rep[count];
    while (totalizer < count) {
        for (int k = 0; k < count; k++) {
            if (d[i] == 'L') {
                ind = fe(n[ewa[k]].left, c, n);
                if (n[ind].name[2] == 'Z') {
                    totalizer++;
                    rep[k] = counter + 1;
                }
                ewa[k] = ind;
            } else if (d[i] == 'R') {
                ind = fe(n[ewa[k]].right, c, n);
                if (n[ind].name[2] == 'Z') {
                    totalizer++;
                    rep[k] = counter + 1;
                }
                ewa[k] = ind;
            }
        }
        if (i == strlen(d) - 1) {
            i = 0;
        } else {
            i++;
        }
        counter++;
    }

    // Calc the LCM.
    long result1 = lcm(rep[0], rep[1]);
    long result2 = lcm(result1, rep[2]);
    long result3 = lcm(result2, rep[3]);
    long result4 = lcm(result3, rep[4]);
    printf("Answer Part 2: %li \n", lcm(result4, rep[5]));

}

int fe(char *name, int limit, node *n)
{
    int i;
    for (i = 0; i < limit; i++) {
        if (strcmp(n[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

// Function to find the LCM of two numbers.
long lcm(long a, long b) {
    return (a * b) / gcd(a, b);
}

// Function to find the Greatest Common Divisor (GCD) using the Euclidean algorithm.
long gcd(long a, long b) {
    while (b != 0) {
        long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}



/*  Answer Part 1: 19637
    Answer Part 2: 8811050362409
*/