#ifndef RECURSION_MODULE_H
#define RECURSION_MODULE_H

// Declarations (Prototypes)
int length(char s[]);
int compareStrings(char s1[], char s2[], int index);
int largestAmongNIntegers(int *a, int n, int index, int max_val);
int searchList(int *a, int n, int index, int target);
void printReverse(int *a, int n);
int checkPalindrome(char s[], int n, int i);
int replaceCharacter(char c1, char c2, char s[], int index);
int sumArray(int *a, int n, int sum);
char lexicographicallySmallest(char s[], int n, char least);

#endif
