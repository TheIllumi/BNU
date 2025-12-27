#include <iostream>
using namespace std;

class Course {
public:
    string courseName;

    Course(string name) {
        courseName = name;
    }

    void displayCourse() {
        cout << "Course: " << courseName << endl;
    }
};

class Student {
public:
    string studentName;

    Student(string name) {
        studentName = name;
    }

    // Method to enroll the student in a course (association)
    void enrollInCourse(Course& course) {
        cout << studentName << " is enrolled in " << course.courseName << endl;
    }
};

int main() {
    // Create course objects
    Course course1("Mathematics");
    Course course2("Computer Science");

    // Create student objects
    Student student1("Alice");
    Student student2("Bob");

    // Enroll students in courses
    student1.enrollInCourse(course1);
    student1.enrollInCourse(course2);

    student2.enrollInCourse(course1);

    return 0;
}
