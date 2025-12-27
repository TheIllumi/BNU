/* 
Program 13:
• Design a flowchart that computes the total bill at the 
  cash counter of a store. 
• Assume the sales tax is 16.5 percent. Ask the user to 
  enter the sales amount and your program logic should 
  display the sales amount, sales tax, and total bill on the 
  screen.
*/

#include <iostream>
#include <cmath>
using namespace std;

int main()
{
	float Tax,TotalBill;
	int SalesAmount;
	cout<<"Enter sale amount = ";
	cin>>SalesAmount;
	Tax = SalesAmount * (16.5/100);
	TotalBill = SalesAmount + Tax;
	cout<<"Sales Amount = "<<SalesAmount<<endl;
	cout<<"Tax = "<<Tax<<endl;
	cout<<"TotalBill = "<<TotalBill<<endl;
	return 0;
}