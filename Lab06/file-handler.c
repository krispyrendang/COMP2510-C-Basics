/**
 * File:    file-handler.c
 *
 * Author:  Taswinder Singh Dhaliwal
 * Date:    Nov 2022
 * Partner: I worked alone
 * Course:  Comp 2510 - Procedural Programming
 *
 * Summary of file:
 *
 *      This file contains code which is called from the main function
 *      in lab6.c and used to parse and filter contents of the input file.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "student.h"

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
 * printAllStudents(Student *list, int o, FILE* fw)
 *
 * Summary of the printAllStudents function:
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

void printAllStudents(Student *list, int o, FILE* fw) {

    float checkGPA = 3.9;
    int checkTOEFL = 70;

    switch (o){
        case 1:
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
 *  Return Value: Integer number 1 or 0 that denotes if the program runs without errors.
 *
 * */

int fileParser(FILE *fr, FILE *fw, int o) {

    int max = 200;
    char line[max];
    char *firstName;
    char *lastName;
    float gpa;
    char *status;
    char *token;
    char d = 'D';
    char i = 'I';
    char *na = "N/A";
    int toefl;
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

    printAllStudents(head, o, fw);
    return 0;
}