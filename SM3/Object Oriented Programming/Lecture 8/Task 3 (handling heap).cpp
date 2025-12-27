#include <iostream>
#include <string>
using namespace std;

class Student {
    public:
    string name;
    double* cgpaPtr;
    
    Student(string name,double cgpa) //default
    {
    this->name = name;
    cgpaPtr = new double; //new memory allocation to cgpa ptr
    *cgpaPtr = cgpa; //dereferencing
    }
    
    //we can also create our own copy constructor
    Student(Student &obj) //default
    {
    this->name = obj.name;
    this->cgpaPtr = obj.cgpaPtr;
    }
    
    void getInfo(){
        cout<<"name :" <<name<<endl;
        cout<<"cgpa :" <<*cgpaPtr<<endl;
    }
};
int main(){
   Student s1("Ali", 3.9);
   Student s2(s1); 
  
   s1.getInfo();
   *(s2.cgpaPtr) = 3.7;
   s1.getInfo();
    return 0;
}