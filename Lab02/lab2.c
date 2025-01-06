#include <stdio.h>

//prints out a multiplication table for numbers up to 16.
void printMultiplicationTable() { // Do NOT touch this line at all

    //outer loop implements numbers up to 16 using its iterator.
    for(int i = 1; i < 17; i++){

        //inner loop prints a multiplication table of up to 16 using its iterator.
        for (int j = 1; j < 17; j++){
            printf("%d * %d = %d\n", i, j, i*j);
        }
        printf("\n");

    }
}

//takes an array of integers and the size of the array as the input and
//returns whether or not the array is a palindrome
int isPalindrome(int elements[], int size) { // Do NOT touch this line at all

    //outer loop checks the elements from left to right.
    for (int i = 0; i < (size/2); i++) {
        //inner loop checks the elements from right to left.
        for (int j = size-1; j > (size/2); j--) {
            //returns false if 2 elements do not match.
            if(elements[i] != elements[j]){
                return 0;
            } else {
                //increment outer loop to check the next number if the first pair is a match.
                i++;
            }
        }
    }
    //returns true if array is a palindrome.
    return 1;
}

int main(int argc, char **argv){ // Do NOT touch this line at all
    printMultiplicationTable();
    //array1 and array2
    int nums1[] = {1, 2, 3, 4, 5};
    int nums2[] = {9, 8, 7, 6, 7, 8, 9};

    //total size divided by the size of index 0 gives the number of elements in the array.
    int length1 = sizeof(nums1)/sizeof(nums1[0]);
    int length2 = sizeof(nums2)/sizeof(nums2[0]);

    //sends array1 and size to check if the array is a palindrome.
    if(isPalindrome(nums1, length1)){
        printf("Array 1 is palindrome\n");
    } else{
        printf("Array 1 is NOT palindrome\n");
    }

    //sends array2 and size to check if the array is a palindrome.
    if(isPalindrome(nums2, length2)){
        printf("Array 2 is pallindrome\n");
    } else{
        printf("Array 2 is NOT pallindrome\n");
    }
    return 0;
}
