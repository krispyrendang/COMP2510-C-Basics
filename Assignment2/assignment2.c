/**
 * File:    assignment2.c
 *
 * Author:  Taswinder Singh Dhaliwal
 * Date:    Nov 2022
 * Partner: Usman Arshad
 * Course:  Comp 2510 - Procedural Programming
 *
 * Summary of file:
 *
 *      This file contains code that performs saturating addition operations.
 *      A saturating addition returns the type's maximum value when there
 *      would be positive overflow, and minimum when there would be negative overflow.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 *
 * long long signed_min(int bitwidth);
 *
 * Summary of the signed_min function:
 *
 *  This function calculates the min bound of the bitwidth
 *
 *Parameters  : take in the parameter of argv[1] to find the bottom
 *              bound of the bitwidth.
 *
 *Return Value: Lower bound number.
 *
 * */

long long signed_min(int bitwidth){
    if (bitwidth != 0){
        return (2 * signed_min(bitwidth - 1));
    }
    else{
        return 1;
    }
}

/**
 *
 * long long signed_max(int bitwidth);
 *
 * Summary of the signed_max function:
 *
 *  This function calculates the max bound of the bitwidth
 *
 *Parameters  : Takes in the parameter of argv[1] to find the max
 *              bound of the bitwidth.
 *
 *Return Value: Upper bound number.
 *
 * */

long long signed_max(int bitwidth){

    if (bitwidth != 0){

        return (2 * signed_max(bitwidth - 1));
    }
    else{
        return 1;
    }
}

/**
 *
 * long long sat_add(long long operand1, long long operand2, int bitwidth);
 *
 * Summary of the sat_add function:
 *
 *  This function calculates addition of the two opperands and checks to
 *  make sure that they are within the bitwidth. If the numbers added are
 *  larger than the max bitwidth it will overflow to the max. If the lower
 *
 *Parameters  : take in the parameter of argv[1], argv[2], and argv[3] to
 *              find the bitwidth of the first argument, and add the two
 *              next arguments together.
 *
 *Return Value: Sum of the two operand values within the bitwidth.
 *
 * */

long long sat_add(long long operand1, long long operand2, int bitwidth){

    long long sum;
    long long max = signed_max(bitwidth - 1) -1;
    long long min = signed_min(bitwidth - 1) * -1;
    sum = operand1 + operand2;

    long long minFlag = (sum - max) >> (bitwidth - 1);
    long long maxFlag = (min - sum) >> (bitwidth - 1);

    int msbA = operand1 >> (bitwidth - 1);
    int msbB = operand2 >> (bitwidth - 1);
    int msbSum = sum >> (bitwidth - 1);

    if (msbA == 0 && msbB == 0 && msbSum == -1){
        return max;
    } else if (msbA == -1 && msbB == -1 && msbSum == 0){
        return min;
    } else if (minFlag == -1 || sum == max){
        return sum;
    } else if (maxFlag == -1 || sum == min){
        return sum;
    }
    else if (minFlag == 0){
        return max;
    } else if (maxFlag == 0 || maxFlag == 1){
        return min;
    }
}

/**
 *
 * int main(int argc, char **argv)
 *
 * Summary of the main function:
 *
 *  The main function runs the program and the functions in the file.
 *
 *Parameters  : char pointer to pointer: points to the inputs in the command line
 *              when the program is executed.
 *              integer value denoting the number of arguments in the command line
 *              when the program is executed.
 *
 *Return Value: Integer number 1 or 0 that denotes if the program runs without errors.
 *
 *Description:
 *  The main function takes in 3 parameters. The bit width followed by 2 operands
 *  that would be added together.
 *
 * */

int main(int argc, char **argv) {

    int bitwidth = atoi(argv[1]);
    long long result;


    if (argc == 2){
        if ((atoi(argv[1]) - 65) && atoi(argv[1]) / 4){
          long long max = signed_max(bitwidth - 1) - 1;
          long long min = signed_min(bitwidth - 1) * -1;
          printf("%d-bit signed integer range\n"
                 "min: %lld   0x%llx\n"
                 "max:  %lld   0x%ll016x", bitwidth, min, min, max, max);
        } else {
          printf("Bitwidth not between 4 and 64.");
        }
    } else if(argc == 4){
        long long a = atoll(argv[2]);
        long long b = atoll(argv[3]);

        result = sat_add(a, b, bitwidth);
        printf("%lld + %lld = %lld", a, b, result);
    } else {
      printf("Error: wrong input format.");
      return -1;
    }

    return 0;
}