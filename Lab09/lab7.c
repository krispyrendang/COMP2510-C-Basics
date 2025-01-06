/**
 * File:    lab7.c
 *
 * Author:  Taswinder Singh Dhaliwal
 * Date:    Nov 2022
 * Partner: I worked alone
 * Course:  Comp 2510 - Procedural Programming
 *
 * Summary of file:
 *
 *      This file contains code which the user sends a text file through the command line
 *      to print students scores to a file that match one of 6 options.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sort.h"

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
 *  The function then calls the fileParser function in the file-handler.c file.
 *
 * */

int main(int argc, char **argv){
    FILE *fr;
    FILE *fw;
    int result;
    if(argc != 4){
        printf("Error: wrong number of input parameters.");
        return -1;
    }else {
        fr = fopen(argv[1], "r");
        fw = fopen(argv[2], "w");
        int opt = atoi(argv[3]);
        if (fr == NULL || fw == NULL) {
            printf("Error: file does not exist.");
        } else {
            switch (opt) {
                case 1:
                    result = fileParser(fr, fw, 1);
                    break;
                case 2:
                    result = fileParser(fr, fw, 2);
                    break;
                case 3:
                    result = fileParser(fr, fw, 3);
                    break;
                case 4:
                    result = fileParser(fr, fw, 4);
                    break;
                case 5:
                    result = fileParser(fr, fw, 5);
                    break;
                case 6:
                    result = fileParser(fr, fw, 6);
                    break;
                default:
                    printf("Error: invalid option selected.");
                    return -1;
            }
        }

        fclose(fr);
        fclose(fw);

    }

    return 0;
}
