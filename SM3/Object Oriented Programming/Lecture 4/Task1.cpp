#include <iostream>
#include <string>
using namespace std;

class Teacher {
    //we will tell all the proporties/ attributes of the class first
    string name;
    string dept;
    string subject;
    double salary;
    
    //we will tell all the methods(functions/member functions) which belong to that class, we writing the methods inside the class
    void changeDept(string newDept){
        dept = newDept;
    }
};
int main(){
    Teacher t1;
    t1.name ="Ali";
    t1.dept ="Computer Science";
    t1.subject="C++"";
    t1.salary="25000";
    //Teacher t2;
    //Teacher t3;
    //Teacher t4;
    cout<<t1.name<<endl;
    return 0;
}