#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum {
    MAXCHAR = 1000,
    MAXROWS = 40,
    MAXCOLS = 40
};

int fhorizontal(char *pattern[], int r);
int reflecth(char *pattern[], int *range, int *rtmp);
int fvert(int linen, char *pattern[]);
int isvequality(int linen, char *pattern[], int left, int right, int row);
int reflectv(int linen, char *pattern[], int left, int right, int *minpair);

// For Part 2
int eqpairh(char *pattern[],int lenline, int r, int perf1, int perf2, char type);
int expandheq(char *pattern[], int a, int b, int r, int lenline, int dif);

int eqpairv(char *pattern[], int lenline, int r, int perf1, int perf2, char type);
int expandhev(char *pattern[], int a, int b, int r, int lenline, int dif);

int onedifh = 0;
int totalp1 = 0;
int totalp2 = 0;


int main(void)
{
    FILE *f = fopen("input.txt", "r");
    if (f == NULL) {
        printf("File not Found!\n");
        return(-1);
    }

    char line[MAXCHAR] = {};
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
        } else if (line[0] == '\n') {
            if (fhorizontal(&pattern[0], r) != 0) {
                fvert(r, &pattern[0]);
            }

            r = 0;
        }
    }
    // Last line of file
    if (fhorizontal(&pattern[0], r) != 0) {
        fvert(r, &pattern[0]);
    }

    r = 0;

    printf("TOTAL SUM Part 1: %i \n", totalp1);
    printf("TOTAL SUM part 2: %i \n", totalp2);

    return 0;
}

int fhorizontal(char *pattern[], int r)
{
    int i = 0, j = 0, k = 0;
    int atmp[10][2] = {};
    int lenline = strlen(pattern[0]);

    for (i = 1; i < r; i++) {
        if (strcmp(pattern[0], pattern[i]) == 0)  {
            printf("HOR Equal top-bottom  %i %i\n", 0, i);
            atmp[j][0] = 0;
            atmp[j][1] = i;
            int rtmp[2] = {};
            if (reflecth(&pattern[0], &atmp[j][0], &rtmp[0]) == 0) {
                printf("HOR Perfect at: %i %i \n", rtmp[0], rtmp[1]);
                totalp1 += 100 * (rtmp[0] + 1);
                // printf("PARCIAL TOTAL %i\n", totalp1);

                /* Part 2 - Find another equal pair columns or rows that are different
                from found in part 1 with at least one diffrent symbol.*/
                if (eqpairh(&pattern[0], lenline, r, rtmp[0], rtmp[1], 'h') == 0) {
                    return 0;
                } else {
                    printf("CHECK IN VERTICAL\n");
                    if (eqpairv(&pattern[0],lenline, r, rtmp[0], rtmp[1], 'h') == 0) {
                        return 0;
                    }
                }
                return 0;
            }
            j++;
        }
    }

    int lastrown = r - 1;
    int hasequal = 0;
    for (i = 0; i < lastrown; i++) {
        hasequal = 0;
        if (strcmp(pattern[lastrown], pattern[i]) == 0) {
            printf("HOR Equal bottom-top  %i and %i\n", lastrown, i);
            // Check if value already found from top-bottom.
            for (k = 0; k < j; k++) {
                if (atmp[k][0] == i && atmp[k][1] == lastrown) {
                    hasequal = 1;
                    break;
                }
            }

            if (hasequal == 0) {
                int arr[] = {i, lastrown};
                int rtmp[2] = {};
                if (reflecth(&pattern[0], &arr[0], &rtmp[0]) == 0) {
                    printf("HOR Perfect at: %i %i \n", rtmp[0], rtmp[1]);
                    totalp1 += 100 * (rtmp[0] + 1);

                    /* Part 2 - Find another equal pair columns or rows that are different
                    from found in part 1 with at least one diffrent symbol.*/
                    // Check for horizontal equality.
                    if (eqpairh(&pattern[0], lenline, r, rtmp[0], rtmp[1], 'h') == 0) {
                        return 0;
                    } else {
                        // Check for vertical equality.
                        if (eqpairv(&pattern[0],lenline, r, rtmp[0], rtmp[1], 'h') == 0) {
                            return 0;
                        }
                    }
                    return 0;
                }
            }
        }
    }
    return 1;
}


int reflecth(char *pattern[], int *range, int *rtmp)
{
    if ((range[1] - range[0]) % 2 == 0) {
        return 1;
    }

    if (range[0] >= range[1]) {
        rtmp[0] =  range[0] - 1;
        rtmp[1] =  range[1] + 1;
        return 0;
    }

    if (strcmp(pattern[range[0]], pattern[range[1]]) == 0) {
        int r[2] = {range[0] + 1, range[1] - 1};
        return reflecth(pattern, r, rtmp);
    }

    return 1;
}


int fvert(int linen, char *pattern[])
{
    int i = 0, j = 0, k = 0;
    int minpair[2] = {};
    int pairtmp[10][2] = {};
    int linelen = strlen(pattern[0]);
    for (i = 1; i < linelen ; i++) {
        if (isvequality(linen, &pattern[0], 0, i, 0) == 0) {
            pairtmp[j][0] = 0;
            pairtmp[j][1] = i;
            printf("VERT equal first-last %i %i \n", pairtmp[j][0], pairtmp[j][1]);

            if (reflectv(linen, &pattern[0], 0, i, &minpair[0]) == 0) {
                printf("VERT perfect at %i %i \n", minpair[0], minpair[1]);
                totalp1 += (minpair[0] + 1);
                printf("PARCIAL TOTAL %i\n", totalp1);

                /* Find another equal pair columns or rows that are different from found.
                with at least one diffrent symbol. PART 2*/
                if (eqpairh(&pattern[0], linelen, linen, minpair[0], minpair[1], 'v') == 0) {
                    return 0;
                } else if (eqpairv(&pattern[0],linelen, linen, minpair[0], minpair[1], 'v') == 0) {
                    return 0;
                }
                return 0;
            }
            j++;
        }
    }

    // Compare from last to first.
    int lastchar = linelen - 1;
    int hasequal = 0;

    for (i = 0; i < lastchar; i++) {
        if (isvequality(linen, &pattern[0], i, lastchar, 0) == 0) {
            printf("VERT equal last to first %i %i \n", lastchar, i);

            // Check if pair existed from left to right
            for (k = 0; k < j; k++) {
                if (pairtmp[k][0] == i && pairtmp[k][1] == lastchar) {
                    hasequal = 1;
                    break;
                }
            }

            // Find the root reflection
            if (hasequal == 0 && (reflectv(linen, &pattern[0], i, lastchar, &minpair[0]) == 0)) {
                printf("VERT perfect at %i %i \n", minpair[0], minpair[1]);
                totalp1 += (minpair[0] + 1);
                printf("PARCIAL TOTAL %i\n", totalp1);

                /* Find another equal pair columns or rows that are different from found.
                with at least one diffrent symbol. PART 2*/
                if (eqpairh(&pattern[0], linelen, linen, minpair[0], minpair[1], 'v') == 0) {
                    return 0;
                } else if (eqpairv(&pattern[0],linelen, linen, minpair[0], minpair[1], 'v') == 0) {
                    return 0;
                }
                return 0;
            }
            hasequal = 0;
        }
    }
    return 1;
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


// Find adjacent equal pair line horizontal with at least one different symbol.
int eqpairh(char *pattern[],int lenline, int r, int perf1, int perf2, char type)
{
    int i = 0, j = 0;

    for (i = 0; i < r - 1; i++) {
        onedifh = 0;
        j = 0;

        while (((pattern[i][j] == pattern[i + 1][j]) || onedifh <= 1 ) && j < lenline) {
            if (pattern[i][j] != pattern[i + 1][j]) {
                onedifh++;
            }
            j++;
        }

        if (onedifh <= 1) {
            // Use only the diferent from perf1 and perf2.
            if ((perf1 != i) || (perf2 != i + 1) || type != 'h') {
                printf("**EQUA HORIZ %i (%i, %i)\n", onedifh, i, i + 1);
                // Check expand rows equality
                int a = i;
                int b = i + 1;

                if (expandheq(&pattern[0], a, b, r, lenline, 0) == 0) {
                    printf("***NEW REFLECT HORIZON (%i, %i)\n", i, i + 1);
                    totalp2 += 100 * (i + 1);
                    return 0;
                }
            }
        }
    }
    return 1;
}


int expandheq(char *pattern[], int a, int b, int r, int lenline, int dif)
{
    int i = 0, j = 0;

    if (a < 0 || b >= r) {
        return 0;
    }

    while (((pattern[a][i] == pattern[b][i]) || dif <= 1) && pattern[a][i] != '\0' ) {
        if (pattern[a][i] != pattern[b][i]) {
            dif++;
        }
        i++;
    }

    if (dif <= 1) {
        return expandheq(pattern, a - 1, b + 1, r, lenline, dif);
    }

    return 1;
}


int eqpairv(char *pattern[], int lenline, int r, int perf1, int perf2, char type)
{
    int dif = 0;
    int i = 0, j = 0;
    int row = 0;

    for (i = 0; i < lenline - 1; i++) {
        dif = 0;
        row = 0;
        while (row < r && ((pattern[row][i] == pattern[row][i + 1]) || dif <= 1)) {
            if (pattern[row][i] != pattern[row][i + 1]) {
                dif++;
            }
            row++;
        }

        if (dif <= 1) {
            if (perf1 != i || perf2 != i + 1 || type != 'v'){
                printf("**EQUAL VERT IN (%i, %i) \n", i, i + 1);

                // Check equality for expanded.
                if (expandhev(&pattern[0], i, i + 1, r, lenline, 0) == 0) {
                    printf("***NEW REFLEC VERT (%i, %i)\n", i, i + 1);
                    totalp2 += i + 1;
                    return 0;
                }
            }
        }
    }
}


int expandhev(char *pattern[], int a, int b, int r, int lenline, int dif)
{

    if (a < 0 || b >= lenline) {
        return 0;
    }

    int row = 0;
    int i = 0;

    for (i = 0; i < lenline; i++) {
        while (row < r && ((pattern[row][a] == pattern[row][b]) || dif <= 1)) {
            if (pattern[row][a] != pattern[row][b]) {
                dif++;
            }
            row++;
        }

        if (dif <= 1) {
            return expandhev(pattern, a - 1, b + 1, r, lenline, dif);
        }
    }

    return 1;
}