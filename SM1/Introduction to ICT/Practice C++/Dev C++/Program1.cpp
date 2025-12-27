/* 
Program 1:
Problem: User enters two integers. Your program should 
give you two answers: Sum & Product 
*/

#include <iostream>
using namespace std;

int main()
{
	int x;
	int y;
	int Sum;
	int Product;
	cout<<"Enter the value of first integer = ";
	cin>>x;
	cout<<"Enter the value of second integer = ";
	cin>>y;
	Sum = x + y;
	Product = x * y;
	cout<<"x = "<<x<<endl;
	cout<<"y = "<<y<<endl;
	cout<<"Sum = "<<Sum<<endl;
	cout<<"Product = "<<Product<<endl;
	return 0;
}