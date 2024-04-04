/*  Advent of Code 2023 Day 15 Part 1 and Part 2.
    Author: João Diniz.
    joaodiniz@msn.com
    Note: For this puzzle I created a Hashmap
    with the boxes, inside the box the lenses were stored
    in a Linked list.
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum {
    MAXCHARS = 23000,
    ASCII0 = 48,
    TOTALBOXES = 256
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

int main(void)
{
    FILE *f = fopen("input.txt", "r");
    if (f == NULL) {
        printf("File not found!\n");
        return(-1);
    }

    // Part 1.
    char linebuf[MAXCHARS];
    char linebuf2[MAXCHARS];
    int totalsum = 0;

    while(fgets(linebuf, MAXCHARS, f) != NULL) {
        strcpy(linebuf2, linebuf); // For part 2.
        char *p = strtok(linebuf, ",");
        while(p != NULL) {
            totalsum += hash(p);
            p = strtok(NULL, ",");
        }
    }

    printf("Answer Part 1: %i\n", totalsum);
    fclose(f);

    // Part 2.
    int sfpower = 0;
    char *p = strtok(linebuf2, ",");
    while(p != NULL) {
        int lenp = strlen(p);
        // Find operation.
        int i = 0;
        for (i = 0; i < lenp; i++) {
            if (p[i] == '='){
                addup(p);
                break;
            } else if (p[i] == '-') {
                sub(p);
                break;
            }
        }
        p = strtok(NULL, ",");
    }

    struct node *ptr2 = NULL;
    int i = 0;
    int slotposition = 0;
    for (i = 0; i < TOTALBOXES; i++) {
        slotposition = 0;
        ptr2 = box[i];
        while(ptr2 != NULL) {
            // printf("[%s %i BOX %i] ", ptr2->label, ptr2->focal, i);
            slotposition++;
            sfpower += ((i + 1) * ((slotposition) * (ptr2->focal)));
            ptr2 = ptr2->next;
        }
    }

    printf("Answer Part 2: %i\n", sfpower);

    // Clear memory to avoid leaks.
    struct node *ptr3 = NULL;
    for (i = 0; i < TOTALBOXES; i++) {
        ptr2 = box[i];
        while(ptr2 != NULL) {
            ptr3 = ptr2->next;
            free(ptr2);
            ptr2 = ptr3;
        }
    }
}


int hash(char *word)
{
    int i = 0;
    int curvalue = 0;
    int lenw = strlen(word);

    for(i = 0; i < lenw; i++) {
        curvalue += *(word + i);
        curvalue *= 17;
        curvalue = curvalue % TOTALBOXES;
    }

    return curvalue;
}


void addup(const char *step)
{
    int i = 0;
    int tmpfocal = 0;
    char tmplabel[20] = {};
    struct node *n = NULL;

    while (*(step + i) != '=') {
        tmplabel[i] = step[i];
        i++;
    }
    tmpfocal = step[i + 1] - ASCII0;
    // Calculate the hash to insert in a specific box from 0 to 255.
    int b = hash(tmplabel);

    // Add in Linked list according to the Box.
    n = malloc(sizeof(node));
    if (n == NULL) {
        printf("No memory available");
        free(n);
        exit(1);
    }

    strcpy(n->label, tmplabel);
    n->focal = tmpfocal;
    n->next = NULL;

    if (box[b] == NULL) {
        box[b] = n;
    } else {
        for(struct node *ptr = box[b]; ptr != NULL; ptr = ptr->next) {
            // Update focal length If lense already exist.
            if (strcmp(ptr->label, tmplabel) == 0) {
                ptr->focal = tmpfocal;
                free(n);
                break;
            }

            // Insert lense.
            if (ptr->next == NULL) {
                ptr->next = n;
                n = NULL;
                break;
            }
        }
    }
}


void sub(const char *step)
{
    int i = 0;
    char tmplabel[20] = {};
    struct node *n = NULL;

    while (*(step + i) != '-') {
        tmplabel[i] = step[i];
        i++;
    }

    int b = hash(tmplabel);

    struct node *deltemp = NULL;

    for(struct node *ptr = box[b]; ptr != NULL; ptr = ptr->next) {
         if (ptr->next != NULL && (strcmp(ptr->next->label, tmplabel) == 0)) {
            deltemp = ptr->next;
            ptr->next = ptr->next->next;
            free(deltemp);
            deltemp = NULL;
            break;
        }

        // Condition for the first node.
        if (strcmp(ptr->label, tmplabel) == 0) {
            deltemp = box[b];
            box[b] = ptr->next;
            free(deltemp);
            deltemp = NULL;
            break;
        }
    }
}
/* Answer Part 1: 514025. Part 2: 244461.*/