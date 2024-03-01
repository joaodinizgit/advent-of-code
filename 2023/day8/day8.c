/*  Advent of Code 2023, Day8 Part 1 and 2.
    Author: João Diniz.
    joaodiniz@msn.com
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {
    MAXCHAR  = 500,
    CHARNODE = 20
};

typedef struct node {
    char *name;
    char *left;
    char *right;
}node;

int next(char *name, int limit, node *n);
long lcm(long a, long b);
long gcd(long a, long b);


int main(void)
{
    FILE *f = fopen("input.txt", "r");
    if (f == NULL) {
        printf("File not Found!\n");
        return 1;
    }

    char *line = malloc(MAXCHAR * sizeof(char));
    fgets(line, MAXCHAR, f);
    strtok(line, "\n");
    char *instruction = malloc(MAXCHAR * sizeof(char));
    strcpy(instruction, line);
    free(line);

    node nodes[700] = {};

    line = malloc(CHARNODE * sizeof(char));
    int c = 0;  // Counter of nodes.
    while (fgets(line, CHARNODE, f)) {
        if (*line != '\n' && *line != ' ' && *line != '\t') {
            char *p;
            p = strtok(line, " = ");
            nodes[c].name = malloc(4 * sizeof(char));
            strcpy(nodes[c].name, p);
            p = strtok(NULL, " = (,");
            nodes[c].left = malloc(4 * sizeof(char));
            strcpy(nodes[c].left, p);
            p = strtok(NULL, " )");
            nodes[c].right = malloc(4 * sizeof(char));
            strcpy(nodes[c++].right, p);
        }
    }
    fclose(f);
    free(line);

    int steps = 0;
    int index = next("AAA", c, nodes);
    if (index == -1) {
        printf("No direction found! \n");
        return 1;
    }

    int i = 0;
    while (strcmp(nodes[index].name, "ZZZ") != 0) {
        if (instruction[i] == 'L') {
            index = next(nodes[index].left, c, nodes);
        } else if (instruction[i] == 'R') {
            index = next(nodes[index].right, c, nodes);
        }
        if (i == strlen(instruction) - 1) {
            i = 0;
        } else {
            i++;
        }
        steps++;
    }
    printf("Answer Part 1: %i \n", steps);

    int ewa[10];    // End With A.
    int na = 0;     // Qty of nodes names end with A.
    for (i = 0; i < c; i++) {
        if (nodes[i].name[2] == 'A') {
            ewa[na++] = i;
        }
    }

    int rep[na]; // Repetition.
    int t, k;
    i = t = index = steps = 0;
    while (t < na) {
        for (k = 0; k < na; k++) {
            if (instruction[i] == 'L') {
                index = next(nodes[ewa[k]].left, c, nodes);
                if (nodes[index].name[2] == 'Z') {
                    t++;
                    rep[k] = steps + 1;
                }
                ewa[k] = index;
            } else if (instruction[i] == 'R') {
                index = next(nodes[ewa[k]].right, c, nodes);
                if (nodes[index].name[2] == 'Z') {
                    t++;
                    rep[k] = steps + 1;
                }
                ewa[k] = index;
            }
        }
        if (i == strlen(instruction) - 1) {
            i = 0;
        } else {
            i++;
        }
        steps++;
    }

    for (i = 0; i < c; i++) {
        free(nodes[i].name);
        free(nodes[i].left);
        free(nodes[i].right);
    }
    free(instruction);

    // Calc the LCM(Least Common Multiple).
    long result1 = lcm(rep[0], rep[1]);
    long result2 = lcm(result1, rep[2]);
    long result3 = lcm(result2, rep[3]);
    long result4 = lcm(result3, rep[4]);
    printf("Answer Part 2: %li \n", lcm(result4, rep[5]));
    return 0;
}


// Find the next element and return the index.
int next(char *name, int limit, node *n)
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


/* Find the Greatest Common Divisor
(GCD) using the Euclidean algorithm. */
long gcd(long a, long b) {
    while (b != 0) {
        long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

//  Answers: Part 1: 19637, Part 2: 8811050362409.