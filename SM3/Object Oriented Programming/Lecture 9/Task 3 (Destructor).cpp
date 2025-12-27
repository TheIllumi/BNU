#include <iostream>
#include <string>
using namespace std;

class Student {
    public:
    string name;
    double* cgpaPtr;
    
    Student(string name,double cgpa) //constructor for s1
    {
    this->name = name;
    cgpaPtr = new double; //new memory allocation to cgpa ptr
    *cgpaPtr = cgpa; //dereferencing
    }
    
    //destructor
    ~Student (){
        cout<<"Hi, Everthing is deleted"<<endl;
        delete cgpaPtr;
    }
    
    
    void getInfo(){
        cout<<"name :" <<name<<endl;
        cout<<"cgpa :" <<*cgpaPtr<<endl;
    }
};
int main(){
   Student s1("Ali", 3.9);
   s1.getInfo();
return 0;
}