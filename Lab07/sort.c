/**
 * File:    sort.c
 *
 * Author:  Taswinder Singh Dhaliwal
 * Date:    Nov 2022
 * Partner: I worked alone
 * Course:  Comp 2510 - Procedural Programming
 *
 * Summary of file:
 *
 *      This file contains code which is called from the main function
 *      in lab7.c and used to parse, sort and filter contents of the input file.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "sort.h"

typedef struct Student {
    char *fName;
    char *lName;
    float gpa;
    char *status;
    int toefl;
    struct Student *next;
} Student;

/**
 *
 * printStudents(Student *list, int o, FILE* fw)
 *
 * Summary of the printStudents function:
 *
 *      The function reads the contents stored in the linked list and
 *      writes to the output text file according to the option selected
 *      as denoted by the integer value passed into the function.
 *
 *  Parameters  :
 *      file pointer: points to the data in the input file for reading.
 *      file pointer: points to the data in the output file for writing.
 *      integer o: the indicated option to filter and write the contents
 *      from the input file to the output file.
 *
 *  Return Value: Nothing -- prints the filtered student data read
 *                from the input file.
 *
 * */

void printStudents(Student *list, int o, FILE* fw) {

    float checkGPA = 3.9;
    int checkTOEFL = 70;

    switch (o){
        case 1:
        case 4:
            while (list != NULL) {
                if (list->gpa > checkGPA){
                    if (list->toefl == -1){
                        fprintf(fw, "%s %s %.2f %s\n",
                                list->fName, list->lName,
                                list->gpa, list->status);
                    }
                }
                list = list->next;
            }
            break;
        case 2:
        case 5:
            while (list != NULL) {
                if (list->gpa > checkGPA){
                    if (list->toefl >= 70){
                        fprintf(fw, "%s %s %.2f %s %d\n",
                                list->fName, list->lName,
                                list->gpa, list->status,
                                list->toefl);
                    }
                }
                list = list->next;
            }
            break;
        case 3:
        case 6:
            while (list != NULL) {
                if (list->gpa > checkGPA){
                    if (list->toefl == -1){
                        fprintf(fw, "%s %s %.2f %s\n",
                                list->fName, list->lName,
                                list->gpa, list->status);
                    } else if (list->toefl >= 70){
                        fprintf(fw, "%s %s %.2f %s %d\n",
                                list->fName, list->lName,
                                list->gpa, list->status,
                                list->toefl);
                    }
                }
                list = list->next;
            }
            break;
    }
}

/**
 *
 * midPoint(struct Student* source, struct Student** first, struct Student** second)
 *
 * Summary of the midPoint function:
 *
 *      The function splits the nodes of the given list into front and back halves,
 *      and return the two lists using the reference parameters.
 *      If the length is odd, the extra node goes in the front list.
 *      Uses the fast/slow pointer strategy.
 *
 *  Parameters  :
 *      struct pointer: points to the head of the source linked list.
 *      struct double pointer: points to the address of the pointer passed into the function.
 *      struct double pointer: points to the address of the pointer passed into the function.
 *
 *  Return Value: Nothing -- splits the source linked list and updates the pointer address
 *                           to the head of each half of the split linked list.
 *
 * */

void midPoint(struct Student* source, struct Student** first, struct Student** second) {
    struct Student* fast;
    struct Student* slow;
    slow = source;
    fast = source->next;

    //Advance 'fast' two nodes, and advance 'slow' one node
    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    //'slow' is at before the midpoint in the list
    // need to disconnect both lists after splitting.
    *first = source;
    *second = slow->next;
    slow->next = NULL;
}

/**
 *
 * struct Student* sortedMerge(struct Student* a, struct Student* b)
 *
 * Summary of the midPoint function:
 *
 *      The function combines the 2 split linked lists while sorting them
 *      according to the requirements.
 *
 *  Parameters  :
 *      struct pointer: points to the head of the first linked list.
 *      struct pointer: points to the head of the second linked list.
 *
 *  Return Value: struct pointer -- a pointer that points to the head of
 *                                  the newly merged and sorted linked list.
 *
 * */

struct Student* sortedMerge(struct Student* a, struct Student* b) {
    struct Student* result = NULL;

    /* Base cases */
    if (a == NULL)
        return (b);
    else if (b == NULL)
        return (a);

    //Check GPA between each student in lists a and b
    if (a->gpa <= b->gpa) {
        //if both GPA are equal
        if (a->gpa == b->gpa){
            //check if both are international students
            if ((a->toefl != -1) && (b->toefl != -1)){

                //if a->toefl is smaller than b->gpa
                if (a->toefl < b->toefl){
                    result = a;
                    result->next = sortedMerge(a->next, b);
                } else if (a->toefl > b->toefl){
                    //if b->gpa is smaller than a->gpa
                    result = b;
                    result->next = sortedMerge(a, b->next);
                } else if (a->toefl == b->toefl){
                    //Check for first name if toefl is equal
                    int fname = strcmp(a->fName, b->fName);
                    if (fname < 0){
                        result = a;
                        result->next = sortedMerge(a->next, b);
                    } else if (fname > 0) {
                        result = b;
                        result->next = sortedMerge(a, b->next);
                        //if both first name are equal
                    } else if (fname == 0) {
                        //check for last name
                        int lname = strcmp(a->lName, b->lName);
                        if (lname < 0) {
                            result = a;
                            result->next = sortedMerge(a->next, b);
                        } else if(lname > 0) {
                            result = b;
                            result->next = sortedMerge(a, b->next);
                        } else if (lname == 0) {
                            result = a;
                            result->next = sortedMerge(a->next, b);
                        }
                    }
                }
            } else {
                //Check for first name if either student
                //does not have a toefl score.
                int fname = strcmp(a->fName, b->fName);
                if (fname < 0){
                    result = a;
                    result->next = sortedMerge(a->next, b);
                } else if (fname > 0) {
                    result = b;
                    result->next = sortedMerge(a, b->next);
                    //if both first name are equal
                } else if (fname == 0) {
                    //check for last name
                    int lname = strcmp(a->lName, b->lName);
                    if (lname < 0) {
                        result = a;
                        result->next = sortedMerge(a->next, b);
                    } else if(lname > 0) {
                        result = b;
                        result->next = sortedMerge(a, b->next);
                    } else if (lname == 0) {
                        result = a;
                        result->next = sortedMerge(a->next, b);
                    }
                }
            }
        } else{
            //if a->gpa is smaller than b->gpa
            result = a;
            result->next = sortedMerge(a->next, b);
        }
    } else {
        //if b->gpa is smaller than a->gpa
        result = b;
        result->next = sortedMerge(a, b->next);
    }
    return (result);
}

/**
 *
 * struct Student* mergeSortList(struct Student** headRef)
 *
 * Summary of the midPoint function:
 *
 *      The function splits the source linked list recursively.
 *      It calls for the midpoint function to do that.
 *      It calls for the sorted merge function to merge the source
 *      linked list that was split using the merge sort algorithm.
 *
 *  Parameters  :
 *      struct double pointer: points to the address of the pointer
 *                             that is the head of each linked list.
 *
 *  Return Value: struct pointer -- a pointer that points to the head of
 *                                  the newly merged and sorted linked list.
 *
 * */

struct Student* mergeSortList(struct Student** headRef) {
    struct Student* head = *headRef;
    struct Student* a;
    struct Student* b;

    //Base case -- length 0 or 1
    if ((head == NULL) || (head->next == NULL)) {
        return head;
    }

    //Split head into 2 parts
    //first is the head of a & second is the head of b
    midPoint(head, &a, &b);

    // Recursively split each half of the list
    mergeSortList(&a);
    mergeSortList(&b);

    //newHead node is based on the merge of 2 sorted lists
    *headRef = sortedMerge(a, b);
    return *headRef;
}

/**
 *
 * int fileParser(FILE *fr, FILE *fw, int o)
 *
 * Summary of the fileParser function:
 *
 *      The function reads the contents stored in the inputfile and
 *      stores each student's data to a node in a linked list.
 *
 *  Parameters  :
 *      file pointer: points to the data in the input file for reading.
 *      file pointer: points to the data in the output file for writing.
 *      integer o: the indicated option to filter and write the contents
 *      from the input file to the output file.
 *
 *  Return Value: Integer number -1 or 0 that denotes if the program runs without errors.
 *
 * */

int fileParser(FILE *fr, FILE *fw, int o) {

    int max = 200;
    char line[max];
    int count = 1;
    Student *head = NULL;
    Student *curr = NULL;
    Student *new = malloc(sizeof(Student));


    while (fscanf(fr, "%s", line) == 1) {
        switch (count) {
            case 1:
                new->fName = (char *) calloc(strlen(line), sizeof(char));
                strcpy(new->fName, line);
                count++;
                break;
            case 2:
                new->lName = (char *) calloc(strlen(line), sizeof(char));
                strcpy(new->lName, line);
                count++;
                break;
            case 3:
                new->gpa = atof(line);
                count++;
                break;
            case 4:
                new->status = (char *) calloc(strlen(line), sizeof(char));
                strcpy(new->status, line);
                count++;
                char c = line[0];
                if (strlen(line) > 1) {
                    printf("Error: wrong format with student status in the input file.");
                    return -1;
                } else if (c == 'D') {
                    count = 1;
                    new->toefl = -1;
                    if (head == NULL) {
                        head = new;
                        curr = new;
                    } else {
                        curr->next = new;
                        curr = new;
                    }
                    new = malloc(sizeof(Student));
                } else if (c != 'I'){
                    printf("Error: wrong format with student status in the input file.");
                    return -1;
                }
                break;
            case 5:
                new->toefl = atoi(line);
                if (new->toefl < 0 || new->toefl > 120){
                    printf("Error: wrong range of toefl score in the input file.");
                    return -1;
                }
                count = 1;
                if (head == NULL) {
                    head = new;
                    curr = new;
                } else {
                    curr->next = new;
                    curr = new;
                }
                new = malloc(sizeof(Student));
                break;
        }
    }
    switch (o) {
        case 1 :
        case 2:
        case 3 :
            printStudents(head, o, fw);
            break;
        case 4 :
        case 5:
        case 6 :
            head = mergeSortList(&head);
            printStudents(head, o, fw);
            break;
    }

    return 0;
}