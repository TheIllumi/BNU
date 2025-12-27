#include <iostream>
using namespace std;

class Student
{
public:
    string name;  
    
    // Constructor to initialize the student's name
    Student(string name) 
    {
        this->name = name;
    }

    void display() 
    {
        cout << "Student: " << name << endl;
    }
};

class Teacher {
public:
    string name;  

    // Constructor to initialize the teacher's name
    Teacher(string name) {
        this->name = name;
    }

    // A teacher can "have" a student (aggregation)
    void teachStudent(Student &student) {
        cout << name << " is teaching " << student.name << endl;
    }
};

int main() {
    Student s1("Alice");
    Student s2("Bob");
    
    Teacher t1("Mr. Smith");

    t1.teachStudent(s1); 
    t1.teachStudent(s2); 

    return 0;
}


