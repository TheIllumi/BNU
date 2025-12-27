#include <iostream>
#include <string>
using namespace std;

class Person {
    protected: 
         string name;
         int age;

    public:
        Person(string name, int age) {
            this->name = name;
            this->age = age;
        }
};

class Student : private Person { 
    public:
        int rollno;

        Student(string name, int age, int rollno) : Person(name, age) {
            this->rollno = rollno;
        }

        void getInfo() {
            cout << "Name: " << name << endl;
            cout << "Age: " << age << endl;
            cout << "Roll No: " << rollno << endl;
        }
};

int main() {
    Student s1("Ali", 21, 1234);
    s1.getInfo();
    return 0;
}
