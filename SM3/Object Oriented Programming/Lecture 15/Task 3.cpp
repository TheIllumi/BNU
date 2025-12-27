#include <iostream>
#include <string>
using namespace std;
class Person {
    public:
         string name;
         int age;
         
   Person(string name, int age)
   {
       this->name = name;
       this->age = age;
   }
};

class Student : public Person {
    public:
    int rollno;
    
    Student (string name, int age, int rollno) : Person(name, age )
    {
        this->rollno = rollno;
    }
    
    void getInfo(){
        cout << "name : " <<name <<endl;
        cout << "age : " <<age <<endl;
        cout << "rollno : " <<rollno <<endl;
    }
    
};
int main() {
    Student s1("Ali", 21, 1234);
    s1.getInfo();
    return 0;
}

