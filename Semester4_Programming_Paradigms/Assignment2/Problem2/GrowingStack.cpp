#include <iostream>
#define Upper_Bound (int)1e5
using std::cin, std::cout, std::endl;

namespace StackSystem {
struct Stack {
    int *array;
    int top;
    int size;
    int currentMaxSize;
    int upperBound;
};

bool initializeStack(Stack &s, const int n) {
    s.array = NULL;
    s.array = new int[n];
    if (s.array == NULL) {
        return false;
    }
    s.top = -1;
    s.size = 0;
    s.currentMaxSize = n;
    s.upperBound = Upper_Bound;
    return true;
}

bool isEmpty(const Stack &s) { return s.top == -1; }

bool isFull(const Stack &s, const int n) { return s.currentMaxSize == n; }

} // namespace StackSystem

int main() {
    cout << "Hello world" << endl;
    return 0;
}
