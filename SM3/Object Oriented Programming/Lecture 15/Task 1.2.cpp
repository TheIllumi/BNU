#include <iostream>
#include <string>
using namespace std;

class Person {
    public:
        string name;
        int age;

        Person() {}

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

int main() 
{
    Person p1;

    p1.name = "Ali";
    p1.age = 30;
    
    p1.getInfo();

    // Uncommenting the following line will cause a compilation error:
    // p1.rollno = 1234; // ERROR: rollno is not a member of Person

    return 0;
}
