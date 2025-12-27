#include <iostream>
#include <string>
using namespace std;

class Teacher {
    private:
    double salary;
    
    public:
    string name;
    string dept;
    string subject;
    //Creating non-parameterized Constructor
   // Teacher() {
    //    dept = "computer Science";
  //  }
    
    //Creating parameterized Constructor using this pointer
    Teacher(string name, string dept, string subject, double salary) {
        this->name = name;
        this->dept = dept;
        this->subject = subject;
        this->salary = salary;
    }
    
    void changeDept(string newDept){
        dept = newDept;
    }
    
    void setSalary(double s)
    {
        salary = s;
    }
    
    double getSalary(){
        return salary;
    }
    
    void getInfo()
    {
       cout<<"name :" <<name <<endl;
       cout<<"subject :" <<subject <<endl;
    }
};
int main(){
   // Teacher t1;
   Teacher t1("Ali", "CS", "OOP", 25000);
   //t1.getInfo();
   Teacher t2(t1); //default copy constructor -invoke
   t2.getInfo();
    return 0;
}