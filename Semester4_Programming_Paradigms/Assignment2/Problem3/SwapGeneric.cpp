#include <iostream>
#include <string>
using std::cout, std::endl, std::string, std::boolalpha;

namespace SwapUtility {
template <typename T> void swap(T &a, T &b) {
    T temp = a;
    a = b;
    b = temp;
}
struct structure {
    int x;
    int y;
};
} // namespace SwapUtility

int main() {
    using namespace SwapUtility;

    int i1 = 10, i2 = 20;
    float f1 = 1.5f, f2 = 4.5f;
    double d1 = 99.99, d2 = 0.01;
    char c1 = 'A', c2 = 'Z';
    string s1 = "Hello", s2 = "World";
    bool b1 = true, b2 = false;
    structure A = {100, 200};
    structure B = {300, 400};

    cout << "BEFORE SWAP" << endl;
    cout << "Integer: " << i1 << ", " << i2 << endl;
    cout << "Float: " << f1 << ", " << f2 << endl;
    cout << "Double: " << d1 << ", " << d2 << endl;
    cout << "Char: " << c1 << ", " << c2 << endl;
    cout << "String: " << s1 << ", " << s2 << endl;
    cout << "Bool: " << boolalpha << b1 << ", " << b2 << endl;
    cout << "Struct: {" << A.x << "," << A.y << "} , {" << B.x << "," << B.y
         << "}" << endl;

    swap(i1, i2);
    swap(f1, f2);
    swap(d1, d2);
    swap(c1, c2);
    swap(s1, s2);
    swap(b1, b2);
    swap(A, B);

    cout << endl << "AFTER SWAP" << endl;
    cout << "Integer: " << i1 << ", " << i2 << endl;
    cout << "Float: " << f1 << ", " << f2 << endl;
    cout << "Double: " << d1 << ", " << d2 << endl;
    cout << "Char: " << c1 << ", " << c2 << endl;
    cout << "String: " << s1 << ", " << s2 << endl;
    cout << "Bool: " << b1 << ", " << b2 << endl;
    cout << "Struct: {" << A.x << "," << A.y << "} , {" << B.x << "," << B.y
         << "}" << endl;

    return 0;
}
