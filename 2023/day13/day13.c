#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum {
    MAXCHAR = 1000,
    MAXROWS = 40,
    MAXCOLS = 40
};

int fvertical(int linen, char *pattern[], int r);

int main(void)
{
    FILE *f = fopen("input.txt", "r");
    if (f == NULL) {
        printf("File not Found!\n");
        return(-1);
    }

    char line[MAXCHAR];
    int linen = 0;
    char *pattern[MAXROWS] = {};
    int r = 0;
    int i = 0, j = 0;
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
            fvertical(linen, &pattern[0], r);
            r = 0;
            linen = 0;
        }
    }
    // Last line of file
    fvertical(linen, &pattern[0], r);
    r = 0;
    linen = 0;
    printf("%i", linen);

    return 0;
}

int fvertical(int linen, char *pattern[], int r)
{
    // Stop Copy and analyze the mirrors
    printf("The above patter have %i lines and length %i\n", linen, strlen(pattern[0]));

    // Analyze horizontal reflect
    // Take the first row and compare with above until r
    // From top to bottom
    int i = 0;
    for (i = 1; i < r; i++) {
        if (strcmp(pattern[0], pattern[i]) == 0)  {
            printf("EQUAL TOP-BOTTOM  %i %i\n", 0, i);
            // TODO Send to a recursive function to check all reflection on vertical within these range

        }
        // printf("%i", i);
    }
    // From bottom to top
    int lastrown = r - 1;
    for (i = 0; i < lastrown; i++) {
        if (strcmp(pattern[lastrown], pattern[i]) == 0) {
            printf("EQUAL BOTTOM-TOP  %i and %i\n", lastrown, i);
            // TODO Send to a recursive function to check all reflection on vertical within these range

        }
        // printf("%i", i);
    }

    // Analyze vertical reflect



    // return 0;


}