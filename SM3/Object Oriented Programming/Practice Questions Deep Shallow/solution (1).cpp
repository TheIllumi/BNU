#include <iostream>
#include <string>

using namespace std;

class Employee {
private:
    string name;     
    double* salary;  

public:
    Employee(const string& empName, double empSalary) {
        name = empName;
        salary = new double(empSalary); 
        cout << "Constructor called for " << name << endl;
    }

    Employee(Employee& emp) {
        name = emp.name;
        salary = emp.salary; 
        cout << "Shallow Copy Constructor called for " << name << endl;
    }
    
    Employee(const Employee& emp, bool deepCopy) {
        if (deepCopy) {
            name = emp.name;
            salary = new double(*(emp.salary));  
            cout << "Deep Copy Constructor called for " << name << endl;
        }
    }
    ~Employee() {
        delete salary; 
        cout << "Destructor called for " << name << endl;
    }
    void display() {
        cout << "Employee Name: " << name << ", Salary: $" << *salary << endl;
    }
};

int main() {
    Employee emp1("Alice", 50000);
    emp1.display();

    Employee emp2(emp1);  
    emp2.display();

    Employee emp3(emp1, true);  
    emp3.display();

    return 0;
}
