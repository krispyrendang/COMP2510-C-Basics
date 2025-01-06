/**
 * File:    lab8.c
 *
 * Author:  Taswinder Singh Dhaliwal
 * Date:    Nov 2022
 * Partner: I worked alone
 * Course:  Comp 2510 - Procedural Programming
 *
 * Summary of file:
 *
 *      This file contains code which the user selects and inputs
 *      data to be sorted and printed, or print a single input from
 *      a list of user inputs. There are 4 types of data the user
 *      may select from.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct Node {
    void *data;
    struct Node *next;
} Node;

/**
 *
 * void addNode(struct Node **head, struct Node **curr, void *input, size_t inputSize)
 *
 * Summary of the addNode function:
 *
 *      The function creates a node and stores the input data and the new node
 *      in a linked list.
 *
 *  Parameters  :
 *      struct double pointer: points to the address of the pointer passed into the function.
 *      struct double pointer: points to the address of the pointer passed into the function.
 *      void pointer: points to the address of the input.
 *      size_t: a non-negative integer value denoting the size of the input parameter.
 *
 *  Return Value: Nothing -- adds a node to a linked list.
 *
 * */
void addNode(struct Node **head, struct Node **curr, void *input, size_t inputSize) {
    struct Node *newNode = (struct Node *) malloc(sizeof(struct Node));
    newNode->data = malloc(inputSize);
    memcpy(newNode->data, input, inputSize);
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
        *curr = newNode;
    } else {
        (*curr)->next = newNode;
        *curr = (*curr)->next;
    }
}

/**
 *
 * void printIndex(struct Node *head, int option, int index)
 *
 * Summary of the printIndex function:
 *
 *      The function reads the contents stored in the linked list and
 *      prints according to the selected index as denoted by the
 *      integer value passed into the function.
 *
 *  Parameters  :
 *      struct pointer: points to the head node of the linked list.
 *      integer option: the indicated data type
 *      integer index: the indicated index for printing
 *
 *  Return Value: Nothing -- prints the requested index
 *                           from the linked list.
 *
 * */
void printIndex(struct Node *head, int option, int index) {
    struct Node *start = head;
    int dataInt;
    float dataFloat;
    char dataC;
    for (int i = 0; i <= index; ++i) {
        if (i == index) {
            switch (option) {
                case 1:
                    printf("%d\n", *(int *) start->data);
                    break;
                case 2:
                    printf("%.1f\n", *(float *) start->data);
                    break;
                case 3:
                    printf("%.2e\n", *(float *) start->data);
                    break;
                case 4:
                    printf("%c\n", *(char *) start->data);
                    break;
            }
        } else {
            start = start->next;
        }
    }
}

/**
 *
 * void printList(struct Node *head, int option)
 *
 * Summary of the printList function:
 *
 *      The function reads the contents stored in the linked list and
 *      prints according to the selected data type as denoted by the
 *      integer value passed into the function.
 *
 *  Parameters  :
 *      struct pointer: points to the head node of the linked list.
 *      integer option: the indicated data type
 *
 *  Return Value: Nothing -- prints the data from all the nodes of the
 *                           linked list.
 *
 * */
void printList(struct Node *head, int option) {
    struct Node *start = head;
    int dataInt;
    float dataFloat;
    char dataC;
    while (start != NULL) {
        switch (option) {
            case 1:
                printf("%d\n", *(int *) start->data);
                break;
            case 2:
                printf("%.1f\n", *(float *) start->data);
                break;
            case 3:
                printf("%.2e\n", *(float *) start->data);
                break;
            case 4:
                printf("%c\n", *(char *) start->data);
                break;
        }
        start = start->next;
    }
}

/**
 *
 * midPoint(struct Node* source, struct Node** first, struct Node** second)
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

void midPoint(struct Node *source, struct Node **first, struct Node **second) {
    struct Node *fast;
    struct Node *slow;
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
 * struct Node* sortedMerge(struct Node* a, struct Node* b)
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

struct Node *sortedMerge(struct Node *a, struct Node *b) {
    struct Node *result = NULL;

    /* Base cases */
    if (a == NULL)
        return (b);
    else if (b == NULL)
        return (a);

    //Compare value of data in lists a and b
    if (a->data > b->data) {
        result = a;
        result->next = sortedMerge(a->next, b);
    } else {
        //if b->data is equal/smaller than a->data
        result = b;
        result->next = sortedMerge(a, b->next);
    }
    return (result);
}

/**
 *
 * struct Node* mergeSortList(struct Node** headRef)
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
struct Node *mergeSortList(struct Node **headRef) {
    struct Node *head = *headRef;
    struct Node *a;
    struct Node *b;

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
 * int main(int argc, char **argv)
 *
 * Summary of the main function:
 *
 *  The main function runs the program and the functions in the file.
 *
 *Parameters  : char pointer to pointer: points to the data in the file.
 *              input text file containing the student data.
 *              output text file containing the student data.
 *              integer value denoting the way to filter the students data.
 *
 *Return Value: Integer number 1 or 0 that denotes if the program runs without errors.
 *
 *Description:
 *  The main function opens a file in read mode and assigns a pointer to read from it.
 *  The function then calls other functions based on user input from lab8.c.
 *
 * */

int main(int argc, char **argv) {
    int menu1, menu2;
    struct Node *head = NULL;
    struct Node *curr = NULL;

    do {
        printf("What data type do you want?\n\t"
               "1) Int\n\t"
               "2) Float\n\t"
               "3) Scientific\n\t"
               "4) Character\n");
        scanf("%d", &menu1);
    } while (menu1 > 4 || menu1 < 1);

    do {
        printf("Select an option:\n\t"
               "1) Input the data\n\t"
               "2) Sort the array\n\t"
               "3) Index the array\n\t"
               "4) Exit the program\n");
        scanf("%d", &menu2);

        switch (menu2) {
            //input data
            case 1:
                printf("Input the data:\n");
                switch (menu1) {
                    case 1:
                        int inputInt;
                        scanf("%d", &inputInt);
                        addNode(&head, &curr, &inputInt, sizeof(inputInt));
                        break;
                    case 2:
                        float inputFloat;
                        scanf("%f", &inputFloat);
                        addNode(&head, &curr, &inputFloat, sizeof(inputFloat));
                        break;
                    case 3:
                        float inputSci;
                        scanf("%e", &inputSci);
                        addNode(&head, &curr, &inputSci, sizeof(inputSci));
                        break;
                    case 4:
                        char inputChar;
                        scanf(" %c", &inputChar);
                        addNode(&head, &curr, &inputChar, sizeof(inputChar));
                        break;
                }
                break;
                //carry out a merge sort (descending order) and print the list
            case 2:
                head = mergeSortList(&head);
                printList(head, menu1);
                break;
                //Input index to be printed.
            case 3:
                printf("Please input the index:\n");
                int index;
                scanf("%d", &index);
                printIndex(head, menu1, index);
                break;
            case 4:
                //avoids default output in case of exiting program.
                break;
            default:
                printf("invalid entry. please try again.\n");
                break;
        }

    } while (menu2 != 4);


    printf("good bye.\n");
    return 0;
}
