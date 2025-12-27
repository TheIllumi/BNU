/* 
Program 14:
• Design a flowchart that computes the tax and tip on a 
  restaurant bill for a client
• Ask the user to enter meal cost.
• The tax should be 16.5 percent of the meal cost. 
• The tip should be 15 percent of the total after adding 
  the tax. 
• Display the meal cost, tax amount, tip amount, and total 
  bill on the screen.
*/

#include <iostream>
#include <cmath>
using namespace std;

int main()
{
	int MealCost;
	float Tax,Tip,TotalBill;
	cout<<"Enter the cost of meal = ";
	cin>>MealCost;
	Tax = MealCost * (16.5/100);
	TotalBill = MealCost + Tax;
	Tip = TotalBill * (15.0/100);
	cout<<"Meal Cost = "<<MealCost<<endl;
	cout<<"Tax = "<<Tax<<endl;
	cout<<"Total Bill = "<<TotalBill<<endl;
	cout<<"Tip = "<<Tip<<endl;
	return 0;	
}