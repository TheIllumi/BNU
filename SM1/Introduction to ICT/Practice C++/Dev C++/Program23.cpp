/*
Program 23:
• Ask the user to enter marks in the final exam (out of 100)
• If the marks are greater or equal to 50 then display a 
  message “ You have passed the course”
• Otherwise display “ You have failed the course : Good 
  Luck next Time”
• Display “ See you in the next course”
*/

#include <iostream>
using namespace std;

int main()
{
	int marks;
	cout<<"Enter final exam marks out of 100 = ";
	cin>>marks;
	
	while (marks > 100 || marks < 0)
	{
		cout<<"Marks ar eout of 100, please enter again = ";
		cin>>marks;
	}
	
	if (marks >= 50)
	{
		cout<<"You have passed the course"<<endl;
	}
	else
	{
		cout<<"You have failed the course, better luck next time loser :D "<<endl;
	}
	
	cout<<"See you in the next course!"<<endl;
	return 0;
}