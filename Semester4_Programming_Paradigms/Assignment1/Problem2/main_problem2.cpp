#include "recursion_module.h"
#include <iostream>
using namespace std;

int main() {
    // variable declaration zone
    int target = 0;
    char s1[512], s2[512];
    char c1, c2;
    int *a;
    int n;

    cout << "Enter two strings: ";
    cin >> s1 >> s2;
    cout << "Result : " << compareStrings(s1, s2, 0) << "\n";

    cout << "Enter value of n: ";
    cin >> n;

    a = new int[n];

    cout << "Enter " << n << " values: \n";

    for (int i = 0; i < n; i++)
        cin >> a[i];
    cout << "Inputted numbers : ";
    for (int i = 0; i < n; i++)
        cout << a[i] << " ";
    cout << endl;
    cout << "Largest among n numbers inputted is : "
         << largestAmongNIntegers(a, n, 0, a[0]) << "\n";

    cout << "Enter value of n : ";
    cin >> n;

    cout << "Enter " << n << " values: ";
    for (int i = 0; i < n; i++)
        cin >> a[i];

    cout << "Enter target value to search for : ";
    cin >> target;
    cout << "Search result: ";
    if (searchList(a, n, 0, target) == 1)
        cout << "True";
    else
        cout << "False";
    cout << endl;

    cout << "Printing inputted list in reverse order : ";
    printReverse(a, n);
    cout << endl;

    cout << "Enter a string : ";
    cin >> s1;
    cout << "Palindrome result: ";
    if (checkPalindrome(s1, length(s1), 0) == 1)
        cout << "True";
    else
        cout << "False";
    cout << endl;

    cout << "Enter two characters, c1 and c2 to replace all occurrences of c1 "
            "by c2 in the string: ";
    cin >> c1 >> c2;
    if (replaceCharacter(c1, c2, s1, 0) == 0)
        cout << "Couldn't replace/find c1 in string";
    else
        cout << "Successfully replaced c1 by c2\nNew string : " << s1;
    cout << endl;

    cout << "Sum of array elements: " << sumArray(a, n, 0) << endl;

    cout << "Lexicographically smallest element in string : "
         << lexicographicallySmallest(s1, length(s1) - 1, s1[length(s1) - 1])
         << endl;

    return 0;
}
