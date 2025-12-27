#include <iostream>
#include <string>
using namespace std;

class Teacher {
    //we will tell all the proporties/ attributes of the class first
    private:
    double salary;
    
    public:
    //CREATING CONSTRUCTOR
    Teacher() {
        cout<<"Hi, I am a constructor"<<endl;
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
};
int main(){
    Teacher t1;
    t1.name ="Ali";
    //t1.changeDept("Computer Science");
    t1.dept ="Computer Science";
    t1.subject="C++";
    t1.setSalary(25000);

    //Teacher t2;
    //Teacher t3;
    //Teacher t4;
    cout<<t1.name<<endl;
    cout<<t1.dept<<endl;
    cout<<t1.getSalary()<<endl;
    return 0;
}