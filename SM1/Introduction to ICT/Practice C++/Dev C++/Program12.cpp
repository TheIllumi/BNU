/* 
Program 12:
• K&N sales division of Lahore generates 58 percent of 
  total sales
• Based on that percentage, design a flowchart that will 
  predict how much K&N sales division of Lahore will 
  generate if the company has total of Rs. 8500,000 in 
  sales this year. 
• Display the Sales of Lahore division along with total sales 
  of K&N.
*/

#include <iostream>
#include <cmath>
using namespace std;

int main()
{
	int sales;
	float TotalSales;
	sales = 8500000;
	TotalSales = sales * 58/100;
	cout<<"Sales = "<<sales<<endl;
	cout<<"Total Sales = "<<TotalSales<<endl; 
	return 0;
}