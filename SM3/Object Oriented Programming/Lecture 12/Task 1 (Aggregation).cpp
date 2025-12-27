#include <iostream>
#include <string>
using namespace std;

// Address Class
class Address {
private:
    string street;
    string city;
    string state;
    string country;

public:
    // Constructor
    Address(string street, string city, string state, string country) {
        this->street = street;
        this->city = city;
        this->state = state;
        this->country = country;
    }

    // Method to display address
    string displayAddress() {
        return street + ", " + city + ", " + state + ", " + country;
    }
};

// Employee Class
class Employee {
private:
    int empId;
    string empFName;
    string empLName;
    double basicPay;
    Address *address; // Aggregation: Employee has an Address

public:
   
    Employee(int empId, string empFName, string empLName, double basicPay, Address *address) {
        this->empId = empId;
        this->empFName = empFName;
        this->empLName = empLName;
        this->basicPay = basicPay;
        this->address = address;
    }
    
    void dispatchSalarySlip() {
        cout << "Salary slip for " << empFName << " " << empLName << endl;
        cout << "Basic Pay: $" << basicPay << endl;
        cout << "Address: " << address->displayAddress() << endl;
    }
};

int main() {
    Address addr("123 Main St", "Springfield", "Illinois", "USA");
    
    Employee emp(101, "John", "Doe", 5000.0, &addr);
    
    emp.dispatchSalarySlip();

    return 0;
}
