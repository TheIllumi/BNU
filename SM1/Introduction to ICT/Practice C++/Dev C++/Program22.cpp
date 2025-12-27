/*
Program 22:
• Let value of x equal to 100.
• Add 20 to x
• Ask user to enter value of y
• If y >=0 then add x to y to calculate answer.
• Otherwise add 100 to y to calculate answer
• Display x, y, and answer
*/

#include <iostream>
using namespace std;

int main()
{
	int x,y,ans;
	x = 20;
	cout<<"Enter value of y = ";
	cin>>y;
	if (y >= 0)
	{
		ans = x + y;
	/*	cout<<"Answer when y >= 0 = "<<ans<<endl;*/
	}
	else
	{
		ans = y + 100;
	/*	cout<<"y when y < 0 = "<<y<<endl;*/
	}
	cout<<"x = "<<x<<endl;
	cout<<"y = "<<y<<endl;
	cout<<"Answer = "<<ans<<endl;
	return 0;
}