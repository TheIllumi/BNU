#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Course {
private:
    int courseId;
    string courseTitle;
    int teacherId;

public:
    Course(int courseId, string courseTitle, int teacherId) {
        this->courseId = courseId;
        this->courseTitle = courseTitle;
        this->teacherId = teacherId;
    }

    void displayCourse() const {
        cout << "Course ID: " << courseId << ", Title: " << courseTitle << ", Taught by Teacher ID: " << teacherId << endl;
    }

    int getTeacherId() const {
        return teacherId;
    }
};

class Teacher {
private:
    int teacherId;
    string teacherName;
    vector<Course> coursesTaught;

public:
    Teacher(int teacherId, string teacherName) {
        this->teacherId = teacherId;
        this->teacherName = teacherName;
    }

    void assignCourse(Course course) {
        coursesTaught.push_back(course);
    }

    void displayAssignedCourses() const {
        cout << "Teacher ID: " << teacherId << ", Name: " << teacherName << endl;
        cout << "Courses taught by " << teacherName << ":" << endl;
        for (const auto& course : coursesTaught) {
            course.displayCourse();
        }
    }
};

int main() {
    Teacher teacher1(1, "Sir Haider Ali");
    Teacher teacher2(2, "Ma'am Nimra");

    Course course1(101, "Multi-variable Calculus", 1);
    Course course2(102, "Calculus", 1);
    Course course3(103, "Artificial Intelligence", 2);
    Course course4(104, "Object-Oriented Programming", 2);

    teacher1.assignCourse(course1);
    teacher1.assignCourse(course2);
    teacher2.assignCourse(course3);
    teacher2.assignCourse(course4);

    teacher1.displayAssignedCourses();
    cout << endl;
    teacher2.displayAssignedCourses();

    return 0;
}