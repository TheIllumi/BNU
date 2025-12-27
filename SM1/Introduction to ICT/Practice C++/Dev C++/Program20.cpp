/*
Program 20:
• Ask the user to enter Salary. If the salary is more than 
  50000, add 10% bonus
• Else add 15% bonus
• Calculate the take home salary and display
*/

#include <iostream>
using namespace std;

int main()
{
	int Salary;
	cout<<"Enter Salary = ";
	cin>>Salary;
	if (Salary > 50000)
	{
		Salary = Salary * 1.10;
	}
	else
	{
		Salary = Salary * 1.15;
	}
	
	cout<<"Take home Salary = "<<Salary<<endl;
	return 0;
}