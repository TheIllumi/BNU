#include <iostream>
#include <string>
using namespace std;

class Student {
public:
    string name;       
    double* grade;     

    // Constructor to initialize Student with a name and initial grade
    Student(string name, double initialGrade) 
    {
        this->name = name;
        grade = new double;      
        *grade = initialGrade;   
    }

    // Copy Constructor for Shallow Copy
    Student(Student& obj, bool deepCopyFlag) 
    {
        this->name = obj.name;  
        if (deepCopyFlag == true) 
        {  // If true, perform a deep copy
            grade = new double;  
            *grade = *(obj.grade); 
        } 
        else 
        {  // If false, perform a shallow copy
            grade = obj.grade;  
        }
    }

    void display() {
        cout << "Student Name: " << name << endl;
        cout << "Grade: " << *grade << endl;
    }
    
    ~Student() {
        delete grade;  // Deallocate memory
    }
};

int main() 
{
    Student s1("Ali", 92.5);
    cout << "Original Student (s1):" << endl;
    s1.display();
    

    // Use shallow copy constructor to create s2
    Student s2(s1, false); // Shallow copy
    *(s2.grade) = 85.0;
    cout << "\nShallow Copy of Student (s2):" << endl;
    s2.display();
    s1.display();
    
    Student s3(s2, true); // Deep copy
    *(s3.grade) = 79.0;
    s3.display();
    s2.display();
}
