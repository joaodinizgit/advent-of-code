/*  Advent of Code 2023 Day 15 Part 1.
    Author: João Diniz.
    joaodiniz@msn.com
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum {
    MAXCHARS = 30000,
    ASCII0 = 48,
    TOTALBOXES = 256,
};

struct node{
    char label[30];
    int focal;
    struct node *next;
}node;

struct node *box[TOTALBOXES] = {};



int hash(char *word);
void addup(const char *step);
void sub(const char *step);
void showmaps(void);

unsigned int sfpower = 0;


int main(void)
{
    FILE *f = fopen("input.txt", "r");
    if (f == NULL) {
        printf("File not found!\n");
        return(-1);
    }

    // Part 1
    char linebuf[MAXCHARS];
    char linebuf2[MAXCHARS];
    int totalsum = 0;

    while(fgets(linebuf, MAXCHARS, f) != NULL) {
        // printf("%s\n", linebuf);
        strcpy(linebuf2, linebuf); // For part 2.
        char *p = strtok(linebuf, ",");
        // printf("%s\n", p);
        while(p != NULL) {
            // printf("%s\n", p);
            totalsum += hash(p);
            p = strtok(NULL, ",");
        }
    }

    // strcpy(linebuf2, linebuf);
    printf("%i\n", totalsum);
    fclose(f);


    // Part 2
    printf("SECOND PART\n");
    // printf("%s\n", linebuf2);
    char *p = strtok(linebuf2, ",");
    printf("%s\n", p);
    while(p != NULL) {
        // printf("%s %i ", p, strlen(p));
        int lenp = strlen(p);

        // Find operation
        int i = 0;
        for (i = 0; i < lenp; i++) {
            if (p[i] == '='){
                // printf("Add or update\n");
                // printf("%s\n", p);
                addup(p);
                // showmaps();
                break;

            } else if (p[i] == '-') {
                // printf("Found - Sub\n");
                // printf("%s\n", p);
                // Subtract from a linked list.
                sub(p);
                // showmaps();
                break;
            }
        }
        p = strtok(NULL, ",");
    }

    printf("LIST BOXS\n");
    struct node *ptr2 = NULL;
    int i = 0;
    int slotposition = 0;
    for (i = 0; i < TOTALBOXES; i++) {
        slotposition = 0;
        ptr2 = box[i];
        while(ptr2 != NULL) {
            printf("[%s %i BOX %i] ", ptr2->label, ptr2->focal, i);
            slotposition++;
            sfpower += ((i + 1) * ((slotposition) * (ptr2->focal)));
            ptr2 = ptr2->next;
        }
    }

    printf("Answer Part 2: %i\n", sfpower);

}


int hash(char *word)
{
    // printf("%s\n", word);
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


void addup(const char *step)
{
    int i = 0;
    int tmpfocal = 0;
    char tmplabel[30]={};
    struct node *n = NULL;

    while (*(step + i) != '=') {
        tmplabel[i] = step[i];
        i++;
    }
    tmpfocal = step[i + 1] - ASCII0;
    // printf("Len %s and focal %i\n", tmplabel, tmpfocal);
    // Cal the hash to insert in a specific box from 0 to 255.
    int b = hash(tmplabel);
    printf("++Add %s %i in BOX: %i\n", tmplabel, tmpfocal, b);

    // Add in Linked list accordin to the Box.
    n = malloc(sizeof(node));
    strcpy(n->label, tmplabel);
    n->focal = tmpfocal;
    n->next = NULL;

    if (box[b] == NULL) {
        box[b] = n;
    } else {
        for(struct node *ptr = box[b]; ptr != NULL; ptr = ptr->next) {
            // Update focal length If already exist
            if (strcmp(ptr->label, tmplabel) == 0) {
                ptr->focal = tmpfocal;
                break;
            }

            // Insert
            if (ptr->next == NULL) {
                ptr->next = n;
                break;
            }
        }
    }
}

void sub(const char *step)
{
    int i = 0;
    char tmplabel[20]={};
    struct node *n = NULL;

    while (*(step + i) != '-') {
        tmplabel[i] = step[i];
        i++;
    }

    int b = hash(tmplabel);
    printf("--Sub %s from BOX: %i\n", tmplabel, b);

    struct node *deltemp = NULL;

    for(struct node *ptr = box[b]; ptr != NULL; ptr = ptr->next) {
        // Test: Trying to exclude number insert are equal
         if (ptr->next != NULL && (strcmp(ptr->next->label, tmplabel) == 0)) {
        //     printf("The next will be equal to find\n");
        //     // Exclude node.
            deltemp = ptr->next;

            ptr->next = ptr->next->next;
            free(deltemp);
            deltemp = NULL;
            break;
        }

        // // Condition for the first number
        if (((strcmp(ptr->label, tmplabel) == 0))) {
            deltemp = ptr;
            box[b] = ptr->next;
            // printf("Number exist!\n");
            free(n);
            n = NULL;
            free(deltemp);
            deltemp = NULL;
            break;
        }
    }


    // }





}


void showmaps(void)
{
    struct node *ptr2 = NULL;
    int i = 0;
    int z = 0;
    unsigned int slotposition = 0;
    for (i = 0; i < 256; i++) {
        ptr2 = box[i];
        while(ptr2 != NULL) {
            printf("[%s %i BOX %i] ", ptr2->label, ptr2->focal, i);
            ptr2 = ptr2->next;
        }
    }
    printf("\n");
}
