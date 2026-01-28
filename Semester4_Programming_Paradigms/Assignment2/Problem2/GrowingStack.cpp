#include <iostream>
#define sizeExtend 16
#define Upper_Bound (int)1e5
using std::cin, std::cout, std::endl;

namespace StackSystem {
struct GrowingStack {
    int *array;
    int top;
    int currentSize;
    int currentMaxSize;
    int upperBound;
};

bool initializeStack(GrowingStack &s, const int n) {
    s.array = NULL;
    s.array = new int[n];
    if (s.array == NULL) {
        return false;
    }
    s.top = -1;
    s.currentSize = 0;
    s.currentMaxSize = n;
    s.upperBound = Upper_Bound;
    return true;
}

// default parameters to allow default and custom inflation to the stack
bool inflate(GrowingStack &s, int = sizeExtend);

inline bool isEmpty(const GrowingStack &s) { return s.top == -1; }

inline bool isFull(const GrowingStack &s) {
    return s.currentSize == s.currentMaxSize;
}

inline bool isMaxCapacity(const GrowingStack &s) {
    return s.currentSize == s.upperBound;
}

bool inflate(GrowingStack &s, int amount) {
    // default : Inflates by 64 bytes (16 integers)
    if (s.currentMaxSize >= s.upperBound)
        return false;
    int newCapacity = s.currentSize + amount;

    int *newStackArray = new int[newCapacity];
    if (!newStackArray)
        return false;

    // this is O(n). There is overhead as there is new allocation -> copy
    for (int i = 0; i < s.currentSize; i++)
        newStackArray[i] = s.array[i];
    for (int i = s.currentSize; i < newCapacity; i++)
        newStackArray[i] = 0;

    delete[] s.array;
    s.array = newStackArray;
    s.currentSize = s.currentMaxSize;
    s.currentMaxSize = newCapacity;

    return true;
}

bool push(GrowingStack &s, const int value) {
    if (isMaxCapacity(s))
        return false;
    if (isFull(s)) {
        if (!inflate(s))
            return false;
    }
    s.array[++s.top] = value;
    s.currentSize++;
    return true;
}

bool pop(GrowingStack &s, int &poppedValue) {
    if (isEmpty(s))
        return false;

    poppedValue = s.array[s.top];
    s.array[s.top--] = 0;
    s.currentSize--;

    return true;
}

} // namespace StackSystem

int main() {
    using namespace StackSystem;

    int n = 20;
    int counter = 1, poppedValue = -1;
    GrowingStack stack1, stack2, stack3;

    initializeStack(stack1, n);
    initializeStack(stack2, n);
    initializeStack(stack3, n);

    for (int i = 0; i < n; i++)
        push(stack1, i + 1);
    for (int i = 0; i < n; i++)
        push(stack2, i + n + 1);

    cout << "Stack 1 elements : " << endl;

    for (int i = 0; i < n; i++)
        cout << stack1.array[i] << " ";
    cout << endl;

    cout << "Stack 2 elements : " << endl;

    for (int i = 0; i < n; i++)
        cout << stack2.array[i] << " ";
    cout << endl;

    while (!isEmpty(stack1) && !isEmpty(stack2)) {
        if (counter % 2 != 0) {
            pop(stack1, poppedValue);
            push(stack3, poppedValue);
        } else {
            pop(stack2, poppedValue);
            push(stack3, poppedValue);
        }
        counter++;
    }
    while (!isEmpty(stack1)) {
        pop(stack1, poppedValue);
        push(stack3, poppedValue);
    }
    while (!isEmpty(stack2)) {
        pop(stack2, poppedValue);
        push(stack3, poppedValue);
    }

    cout << "Stack 3 elements : " << endl;

    for (int i = 0; i < stack3.currentSize; i++)
        cout << stack3.array[i] << " ";
    cout << endl;

    return 0;
}
