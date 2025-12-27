#include <iostream>
#include <string>
using namespace std;
class Person {
    public:
         string name;
         int age;
         
   Person()
   {
        cout << "parent constructor"<<endl;
   }
   
   ~Person()
   {
        cout << "parent destructor"<<endl;
   }
};

class Student : public Person {
    //name, age, roll no
    public:
    int rollno;
    
    Student ()
    {
        cout << "child constructor"<<endl;
    }
    
    ~Student ()
    {
        cout << "child destructor"<<endl;
    }
    
    void getInfo(){
        cout << "name : " <<name <<endl;
        cout << "age : " <<age <<endl;
        cout << "rollno : " <<rollno <<endl;
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