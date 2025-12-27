#include <iostream>
#include <string>
using namespace std;

class Teacher {
    //we will tell all the proporties/ attributes of the class first
    private:
    double salary;
    public:
    string name;
    string dept;
    string subject;
    
    void changeDept(string newDept){
        dept = newDept;
    }
     //setter
    void setSalary(double s)
    {
        salary=s;
    }
     //getter
     double getSalary()
    {
        return salary;
    }
};
int main(){
    Teacher t1;
    t1.name ="Ali";
    t1.dept ="Computer Science";
    t1.subject="C++";
    t1.setSalary(25000);
    //Teacher t2;
    //Teacher t3;
    //Teacher t4;
    cout<<t1.name<<endl;
    cout<<t1.getSalary()<<endl;
    return 0;
}
