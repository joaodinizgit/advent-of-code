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
    char *d = malloc(MAXCHAR * sizeof(char));
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
    free(line);

    int steps = 0;
    int index = fe("AAA", c, n);
    if (index == -1) {
        printf("No direction found! \n");
        return 1;
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
            steps++;
        }
        printf("Answer Part 1: %i \n", steps);
    }

    int ewa[10];    // End With A.
    int na = 0;     // Qty numbers end with A.
    for (int i = 0; i < c; i++) {
        if (n[i].name[2] == 'A') {
            ewa[na++] = i;
        }
    }

    int rep[na]; // Repetion.
    int t, i;
    i = t = index = steps = 0;
    while (t < na) {
        for (int k = 0; k < na; k++) {
            if (d[i] == 'L') {
                index = fe(n[ewa[k]].left, c, n);
                if (n[index].name[2] == 'Z') {
                    t++;
                    rep[k] = steps + 1;
                }
                ewa[k] = index;
            } else if (d[i] == 'R') {
                index = fe(n[ewa[k]].right, c, n);
                if (n[index].name[2] == 'Z') {
                    t++;
                    rep[k] = steps + 1;
                }
                ewa[k] = index;
            }
        }
        if (i == strlen(d) - 1) {
            i = 0;
        } else {
            i++;
        }
        steps++;
    }

    for (i = 0; i < c; i++) {
        free(n[i].name);
        free(n[i].left);
        free(n[i].right);
    }
    free(d);

    // Calc the LCM(Least Common Multiple).
    long result1 = lcm(rep[0], rep[1]);
    long result2 = lcm(result1, rep[2]);
    long result3 = lcm(result2, rep[3]);
    long result4 = lcm(result3, rep[4]);
    printf("Answer Part 2: %li \n", lcm(result4, rep[5]));
    return 0;
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

/*  Answer Part 1: 19637
    Answer Part 2: 8811050362409
*/