/*
Question 8:

A used bicycle shop lends bicycles with the following rules: A deposit of $150 must be made before taking any bicycle 
from the shop. The charges for hiring depend on the month in which it is hired. If the number of days of hire exceeds 15, 
a discount of 11% is offered. The hire-rate is determined as per the following rules: 

Month name Rate/day (in $) 
Jan. to Mar. 1.75 
April to June 1.65 
July to Sept. 1.50 
Oct. to Dec. 1.15 

In case of multiple day hiring, the rate is same for all days as on the first day of hiring. Develop a flowchart showing the 
logic to calculate the amount to be paid before taking any bicycle from the shop.

Task Analysis. 

For the first three months of the year, that is, for the month numbers less than or equal to three, the rate of charge is 
the same. For the next three, but less than or equal to six, the rate of charge is the same. The next three months and the 
last three months are at a similar rate. To determine the charge for taking a bicycle from the shop, we require two 

inputs: 

the number of months in which a request is made for hire and the number of days for which the hire is effective. 
However, the month number given as input should be validated first and then the number of days for hire should be 
accepted as input. As the rates for the month numbers are given, the calculation of the charge of hiring after discount.
*/

#include <iostream>
using namespace std;

int main()
{
	int month;
	int days;
	int deposit;
	float discount;
	
	deposit = 150;
	discount = 0.89;
	
	float total;
	float HireRate;
	
	cout<<"Input today's month by entering a value from 1-12 = ";
	cin>>month;
	
	while (month<1 || month>12)
	{
		cout<<"Enter value from 1-12 = ";
		cin>>month;
	}
	
	if (month <= 3)
	{
		HireRate = 1.75;
	}
	else if (month > 3 && month <=6 )
	{
		HireRate = 1.65;
	}
	else if (month > 6 && month <= 9)
	{
		HireRate = 1.50;
	}
	else if (month > 9 && month <=12)
	{
		HireRate = 1.15;
	}
	
	cout<<"Enter the number of days for hire = ";
	cin>>days;
	if (days < 15)
	{
		total = deposit * HireRate;
		cout<<"Total Amount = "<<total<<endl;
	}
	else
	{
		total = deposit * HireRate * discount;
		cout<<"Total Amount After 11% discount = "<<total<<endl;
	} 
	
	
	return 0;
}