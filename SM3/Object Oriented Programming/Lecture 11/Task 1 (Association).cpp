#include <iostream>
#include <string>  
using namespace std;

class Teacher {
public:
    string name;  

    Teacher(string n) {
        name = n;  
    }

    void showTeacher() {
        cout << "Teacher: " << name << endl;
    }
};

class Course {
public:
    string courseName;  
    Teacher teacher;  

    // Constructor for Course which initializes courseName and teacher
    Course(string course) : teacher("Dr. John") 
    {  
        courseName = course;  
    }

    void showCourse() {
        cout << "Course: " << courseName << endl;
        teacher.showTeacher();  
    }
};

int main() {
    Course c("Math");
    c.showCourse();  

    return 0;
}
