#include <iomanip>
#include <iostream>
#include <string>
using std::cout, std::cin, std::endl;

namespace Academic {
struct Student {
    std::string name;
    int age;
    std::string department;
    int year;
};

void readStudentData(Student &s) {
    cout << "Enter name: ";
    cin.ignore();
    std::getline(cin, s.name);
    cout << "Enter age: ";
    cin >> s.age;
    cout << "Enter department: ";
    cin.ignore();
    std::getline(cin, s.department);
    cout << "Enter year: ";
    cin >> s.year;
}

void displayStudentData(const Student &s) {
    cout << std::string(80, '-') << endl;
    cout << std::left << std::setw(20) << s.name << " | " << std::setw(10)
         << s.age << " | " << std::setw(20) << s.department << " | "
         << std::setw(10) << s.year << " | " << endl;
}
} // namespace Academic

int main() {
    using namespace Academic;
    int n = 0;
    cout << "Enter number of students : ";
    cin >> n;
    Student students[n];

    for (int i = 0; i < n; i++) {
        cout << "\n" << std::string(80, '-') << endl;
        cout << "Enter data for student " << i + 1 << endl;
        readStudentData(students[i]);
        cout << "\n";
    }

    cout << std::left << std::setw(20) << "NAME" << " | " << std::setw(10)
         << "AGE" << " | " << std::setw(20) << "DEPARTMENT" << " | "
         << std::setw(10) << "YEAR" << " | " << endl;
    for (int i = 0; i < n; i++)
        displayStudentData(students[i]);
    cout << std::string(80, '-') << endl;
    return 0;
}
