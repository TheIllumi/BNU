#include <iostream>
using namespace std;

// Forward declaration of Teacher class
class Teacher;

class Student {
private:
    double grade;  

public:
    // Constructor to initialize grade
    Student(double g) : grade(g) {}

    friend class Teacher; 
};

class Teacher {
public:
    void checkGrade(Student s) {
        cout << "The student's grade is: " << s.grade << endl;  
    }
};

int main() {
    Student student1(95.5);  
    Teacher teacher1;         
    teacher1.checkGrade(student1);  
    return 0;
}
