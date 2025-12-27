/* 
Program 3:
Ask the user to enter an integer value. The program 
displays “You have entered an even number” if it is 
even. Otherwise the program displays “You have entered 
odd number”
*/

#include <iostream>
using namespace std;

int main()
{
	int x;
	cout<<"Enter an integer value = ";
	cin>>x;
	if (x%2==0)
	{
		cout<<"You have entered an even number"<<endl;
	}
	else
	{
		cout<<"You have entered an odd number"<<endl;
	}
	return 0;
}