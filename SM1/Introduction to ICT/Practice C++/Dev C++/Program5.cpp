/* 
Program 5:
• Draw a flowchart that reads in a number that represents 
  the number of kilometers traveled
• The flowchart will convert this number to miles
  1 kilometer = 0.621 miles
• Display the kilometers travelled as well as miles 
  travelled
*/

#include <iostream>
#include <cmath>
using namespace std;

int main()
{
	float Km;
	float Miles;
	cout<<"Enter kilometer travelled = ";
	cin>>Km;
	Miles = Km * 0.621;
	cout<<"Kilometers travelled = "<<Km<<endl;
	cout<<"Miles travelled = "<<Miles<<endl;
	return 0;
}