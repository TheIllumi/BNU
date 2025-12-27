/* 
Program 11:
• Design a flowchart for a program that accepts number of 
  remaining weeks till Quaid’s Day.
• Your flowchart calculates the number of days left and 
  displays weeks and days.
*/

#include <iostream>
#include <cmath>
using namespace std;

int main()
{
	int R_Weeks,R_Days;
	cout<<"Enter remaining weeks till Quaid's Day = ";
	cin>>R_Weeks;
	R_Days = R_Weeks * 7;
	cout<<"Remaining Weeks = "<<R_Weeks<<endl;
	cout<<"Remaining Days = "<<R_Days<<endl;
	return 0;
}