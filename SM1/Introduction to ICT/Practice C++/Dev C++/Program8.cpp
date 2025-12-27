/* 
Program 8:
• Design a flowchart to print the sum, product, difference, 
  and remainder after dividing the two numbers entered 
  by the user.
*/

#include <iostream>
#include <cmath>
using namespace std;

int main()
{
	int x,y,sum,product,difference;
	float quotient;
	float remainder;
	cout<<"Enter values of x and y"<<endl;
	cin>>x;
	cin>>y;
	sum = x + y;
	product = x * y;
	difference = x - y;
	quotient = x / y;
	remainder = x % y;
	cout<<"x = "<<x<<endl;
	cout<<"y = "<<y<<endl;
	cout<<"Sum = "<<sum<<endl;
	cout<<"Product = "<<product<<endl;
	cout<<"Difference = "<<difference<<endl;
	cout<<"Quotient = "<<quotient<<endl;
	cout<<"Remainder = "<<remainder<<endl;
	return 0;
}