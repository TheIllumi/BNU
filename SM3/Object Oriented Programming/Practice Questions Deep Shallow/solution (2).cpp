#include <iostream>
#include <string>

using namespace std;

class Course {
private:
    string courseName;   
    double* grades;      
    int numStudents;    

public:
    Course(const string& name, int students) {
        courseName = name;
        numStudents = students;
        grades = new double[numStudents];  
        for (int i = 0; i < numStudents; ++i) {
            grades[i] = 0.0;  // Initialize grades to 0
        }
        cout << "Constructor called for course: " << courseName << endl;
    }

    Course(const Course& other) {
        courseName = other.courseName;
        numStudents = other.numStudents;
        grades = new double[numStudents];  
        
        for (int i = 0; i < numStudents; ++i) {
            grades[i] = other.grades[i];  
        }
        cout << "Deep Copy Constructor called for course: " << courseName << endl;
    }

    ~Course() {
        delete[] grades;  
        cout << "Destructor called for course: " << courseName << endl;
    }

    void setGrade(int studentIndex, double grade) {
        if (studentIndex >= 0 && studentIndex < numStudents) {
            grades[studentIndex] = grade;
        }
    }

    void display() const {
        cout << "Course Name: " << courseName << endl;
        cout << "Grades:" << endl;
        for (int i = 0; i < numStudents; ++i) {
            cout << "Student " << (i + 1) << ": " << grades[i] << endl;
        }
    }
};

int main() {
    Course course1("Mathematics", 3);
    course1.setGrade(0, 85.5);
    course1.setGrade(1, 90.0);
    course1.setGrade(2, 78.0);
    course1.display();

    Course course2 = course1; 
    course2.display();

    return 0;
}
