#include <iostream>
#include <string>
using namespace std;

class Teacher {
    //we will tell all the proporties/ attributes of the class first
    private:
    double salary;
    
    public:
    //CREATING CONSTRUCTOR
   // Teacher() {
    //    dept = "computer Science";
  //  }
    
    Teacher(string n, string d, string s, double sal) {
        name = n;
        dept = d;
        subject = s;
        salary = sal;
    }
    
    string name;
    string dept;
    string subject;
    
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
   t1.getInfo();
   // t1.name ="Ali";
    //t1.dept ="Computer Science";
   // t1.subject="C++";
   // t1.setSalary(25000);
    //Teacher t2;
    //Teacher t3;
    //Teacher t4;
   // cout<<t1.name<<endl;
   // cout<<t1.dept<<endl;
    return 0;
}