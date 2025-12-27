#include <iostream>
#include <string>
using namespace std;

class Student {
    public:
    string name;
    double cgpa;
    
    Student(string name,double cgpa) //default
    {
    this->name = name;
    this->cgpa = cgpa;
    }
    
    Student(Student &obj) //custom copy constructor for t2
    { 
    this->name = obj.name;
    this->cgpa = obj.cgpa;
    }


    void getInfo(){
        cout<<"name :" <<name<<endl;
        cout<<"cgpa :" <<cgpa<<endl;
    }
};
int main(){
   Student s1("Ali", 3.9);
   s1.getInfo();
   Student s2(s1); 
   s2.getInfo();
    return 0;
}