#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum {
    MAXCHAR = 1000,
    MAXROWS = 40,
    MAXCOLS = 40
};

int fhorizontal(int linen, char *pattern[], int r);
int reflecth(char *pattern[], int *range, int *rtmp);
int fvert(int linen, char *pattern[]);
int isvequality(int linen, char *pattern[], int left, int right, int row);
int reflectv(int linen, char *pattern[], int left, int right, int *minpair);

int totalp1 = 0;

int main(void)
{
    FILE *f = fopen("input.txt", "r");
    if (f == NULL) {
        printf("File not Found!\n");
        return(-1);
    }

    char line[MAXCHAR] = {};
    int linen = 0;
    char *pattern[MAXROWS] = {};
    int r = 0, i = 0, j = 0;
    while (fgets(line, MAXCHAR, f) != NULL) {
        if (line[0] != '\n') {
            char *p = strtok(line, "\n");
            pattern[r] = (char*)malloc(strlen(p));
            if (pattern[r] == NULL) {
                printf("Failed in allocation memory.\n");
            }
            strcpy(pattern[r], p);
            printf("%s\n", pattern[r]);
            r++;
            linen++;
        } else if (line[0] == '\n') {
            fhorizontal(linen, &pattern[0], r);
            fvert(r, &pattern[0]);
            r = 0;
            linen = 0;
        }
    }
    // Last line of file
    fhorizontal(linen, &pattern[0], r);
    fvert(linen, &pattern[0]);
    r = 0;
    linen = 0;
    // printf("%i", linen);

    printf("TOTAL SUM %i \n", totalp1);
    return 0;
}

int fhorizontal(int linen, char *pattern[], int r)
{
    // printf("The above pattern have %i lines and length %i\n", linen, strlen(pattern[0]));

    int i = 0, j = 0, k = 0, sum_h = 0;
    int atmp[10][2] = {};

    for (i = 1; i < r; i++) {
        if (strcmp(pattern[0], pattern[i]) == 0)  {
            // printf("HOR Equal top-bottom  %i %i\n", 0, i);
            atmp[j][0] = 0;
            atmp[j][1] = i;
            int rtmp[2] = {};
            if (reflecth(&pattern[0], &atmp[j][0], &rtmp[0]) == 0) {
                    printf("HOR Perfect at: %i %i \n", rtmp[0], rtmp[1]);
                    totalp1 += 100 * (rtmp[0] + 1);
                    printf("PARCIAL TOTAL %i\n", totalp1);

                }
            j++;
        }
    }

    int lastrown = r - 1;
    int hasequal = 0;
    for (i = 0; i < lastrown; i++) {
        hasequal = 0;
        if (strcmp(pattern[lastrown], pattern[i]) == 0) {
            // printf("HOR Equal bottom-top  %i and %i\n", lastrown, i);
            // Check if value already in top-bottom
            for (k = 0; k < j; k++) {
                if (atmp[k][0] == i && atmp[k][1] == lastrown) {
                    printf("Equal range, don't send!\n");
                    hasequal = 1;
                }
            }

            if (hasequal == 0) {
                int arr[] = {i, lastrown};
                int rtmp[2] = {};
                if (reflecth(&pattern[0], &arr[0], &rtmp[0]) == 0) {
                    printf("HOR Perfect at: %i %i \n", rtmp[0], rtmp[1]);
                    totalp1 += 100 * (rtmp[0] + 1);
                    printf("PARCIAL TOTAL %i\n", totalp1);
                }
            }
        }
    }
}


int reflecth(char *pattern[], int *range, int *rtmp)
{
    if ((range[1] - range[0]) % 2 == 0) {
        return 1;
    }

    if (range[0] >= range[1]) {
        // printf("Perfect at: %i %i \n", range[0], range[1]);
        rtmp[0] =  range[0] - 1;
        rtmp[1] =  range[1] + 1;
        return 0;
    }

    if (strcmp(pattern[range[0]], pattern[range[1]]) == 0) {
        int r[2] = {range[0] + 1, range[1] - 1};
        return reflecth(pattern, r, rtmp);
    }

    return 1;
    // printf("Range to check: %i %i\n", *range, *(range + 1));
}


int fvert(int linen, char *pattern[])
{
    // Compare the first and last col equality
    int i = 0, j = 0, k = 0;
    int minpair[2] = {};
    int pairtmp[10][2] = {};
    int linelen = strlen(pattern[0]);
    for (i = 1; i < linelen ; i++) {
        if (isvequality(linen, &pattern[0], 0, i, 0) == 0) {
            // printf("VERT First to Last They are equal %i %i \n", 0, i);
            pairtmp[j][0] = 0;
            pairtmp[j][1] = i;
            printf("VERT equal first-last %i %i \n", pairtmp[j][0], pairtmp[j][1]);
            // Find the root reflection

            if (reflectv(linen, &pattern[0], 0, i, &minpair[0]) == 0) {
                printf("VERT perfect at %i %i \n", minpair[0], minpair[1]);
                totalp1 += (minpair[0] + 1);
                printf("PARCIAL TOTAL %i\n", totalp1);
            }
            j++;
        }
    }

    // Compare from last to first
    int lastchar = linelen - 1;
    int hasequal = 0;

    for (i = 0; i < lastchar; i++) {
        if (isvequality(linen, &pattern[0], i, lastchar, 0) == 0) {
            printf("VERT equal last to first %i %i \n", lastchar, i);

            // Check if pair existed from left to right
            for (k = 0; k < j; k++) {
                if (pairtmp[k][0] == i && pairtmp[k][1] == lastchar) {
                    printf("VERT already existed in vertical dont send \n");
                    hasequal = 1;
                    break;
                }
            }

            // Find the root reflection
            if (hasequal == 0 && (reflectv(linen, &pattern[0], i, lastchar, &minpair[0]) == 0)) {
                printf("VERT2 perfect at %i %i \n", minpair[0], minpair[1]);
                totalp1 += (minpair[0] + 1);
                printf("PARCIAL TOTAL %i\n", totalp1);

            }

            hasequal = 0;

        }
    }

}

// Check if two columns are equal, for vertical.
int isvequality(int linen, char *pattern[], int left, int right, int row)
{
    if (row >= linen) {
        return 0;
    }

    if (pattern[row][left] == pattern[row][right]) {
        return isvequality(linen, pattern, left, right,  row + 1);
    }

    return 1;
}


int reflectv(int linen, char *pattern[], int left, int right, int *minpair)
{
    if ((right - left) % 2 == 0) {
        return 1;
    }

    if (left > right) {
        minpair[0] = left - 1;
        minpair[1] = right + 1;
        return 0;
    }

    if (isvequality(linen, pattern, left, right, 0) == 0) {
        return reflectv(linen, pattern, left + 1, right - 1, minpair);
    }


}