#include <iostream>
#define max(a, b) {(a) >= (b) ? a : b}
using namespace std;

int length(char s[]) {
    int l = 0;
    while (s[l] != '\0')
        l++;
    return l;
}

int compareStrings(char s1[], char s2[], int index) {
    int l1 = length(s1);
    int l2 = length(s2);

    if (l1 < l2)
        return -1;
    else if (l1 > l2)
        return 1;
    else {
        if (s1[index] == '\0')
            return 0;
        else if (s1[index] == s2[index])
            return compareStrings(s1, s2, ++index);
        else if (s1[index] < s2[index])
            return -1;
        else if (s1[index] > s2[index])
            return 1;
    }
    return 0;
}

int largestAmongNIntegers(int *a, int n, int index, int max) {
    if (index == n)
        return max;
    else if (a[index] >= max)
        return largestAmongNIntegers(a, n, index + 1, a[index]);
    else
        return largestAmongNIntegers(a, n, index + 1, max);
}

int searchList(int *a, int n, int index, int target) {
    if (index == n)
        return 0;
    if (a[index] == target)
        return 1;
    return searchList(a, n, index + 1, target);
}

void printReverse(int *a, int n) {
    if (n == 0)
        return;
    cout << a[n - 1] << " ";
    printReverse(a, n - 1);
}

int checkPalindrome(char s[], int n, int i) {
    if (i == n / 2 + 1)
        return 1;
    if (s[i] == s[n - i - 1])
        return checkPalindrome(s, n, i + 1);
    else
        return false;
}

int replaceCharacter(char c1, char c2, char s[], int index) {
    int n = length(s);
    if (index == n)
        return 1;
    if (s[index] == c1) {
        s[index] = c2;
        return replaceCharacter(c1, c2, s, index + 1);
    } else
        return replaceCharacter(c1, c2, s, index + 1);
    return 0;
}

int sumArray(int *a, int n, int sum) {
    if (n == 0)
        return sum;
    return sumArray(a, n - 1, sum + a[n - 1]);
}

char lexicographicallySmallest(char s[], int n, char least) {
    if (n < 0)
        return least;
    if (least > s[n])
        return lexicographicallySmallest(s, n - 1, s[n]);
    else
        return lexicographicallySmallest(s, n - 1, least);
}

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
