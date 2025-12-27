/*
Program 21:
• Ask the user to enter an integer.
• If the integer is even, add 100 to the entered value and 
  display
• Else add 10 to the entered value and display
*/

#include <iostream>
using namespace std;

int main()
{
	int num;
	cout<<"Enter an Integer = ";
	cin>>num;
	if (num%2==0)
	{
		num = num + 100;
		cout<<"Integer is even = "<<num<<endl;
	}
	else
	{
		num = num + 10;
		cout<<"Integer is odd = "<<num<<endl;
	}
	return 0;
}