#include <iostream>
#include <string>
using namespace std;

class Person {
    public:
        string name; 
        int age;     

        Person() {
            
        } 

        void getInfo() {
            cout << "Name: " << name << endl;
            cout << "Age: " << age << endl;
        }
};

class Student : public Person {
    public:
        int rollno; 
        
        void getInfo() {
            Person::getInfo();
            cout << "Roll No: " << rollno << endl;
        }
};

int main() {
    Student s1;
    
    s1.name = "Ali"; 
    s1.age = 21;     
    s1.rollno = 1234; 

    s1.getInfo();

    return 0;
}
