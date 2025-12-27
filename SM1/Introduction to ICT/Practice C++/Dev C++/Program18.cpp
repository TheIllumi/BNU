/*
Program 18:
• Design flow chart which asks user to enter a four digit 
  number (integer)
• Your logic should print each digit separately
• Hint: use floor and Mod functions
*/

#include <iostream>
using namespace std;

int main()
{
	int num,d4,d3,d2,d1;
	cout<<"Enter 4 digit number = ";
	cin>>num;
	
	while (num <1000 || num >9999)
	{
		cout<<"Number entered is not a 4 digit number, therefore enter again = ";
		cin>>num;	
	}
	
	d4 = num%10;
	d3 = (num%100 - d4)/10;
	d2 = (num%1000 - d3)/100;
	d1 = (num%10000 - d2)/1000;
	
	cout<<"\n"<<d4<<"\n"<<d3<<"\n"<<d2<<"\n"<<d1<<endl; 
	return 0;
}