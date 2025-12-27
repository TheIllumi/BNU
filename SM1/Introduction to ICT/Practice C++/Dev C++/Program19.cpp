/*
Program 19:
• Ask the user to enter the salary of the month. Add 10
  percent bonus to the salary
• Add 5% Fuel Allowance
• Calculate the final take home salary
• Display the Final take home salary
*/

#include <iostream>
using namespace std;

int main()
{
	int salary;
	float bonus;
	float fuelpay;
	float takehomeSal;
	bonus = 0.1;
	fuelpay = 0.05;
	cout << "Enter Salary = ";
	cin >> salary;
	takehomeSal = (salary + (salary * bonus) + (salary * fuelpay));
	cout << "Final take home Salary = " << takehomeSal << endl;
	return 0;
}