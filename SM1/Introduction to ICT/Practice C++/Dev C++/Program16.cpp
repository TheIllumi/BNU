/*
Program 16:
• Ask the user to enter total seconds. Convert seconds into 
  minutes and seconds. Display the entered seconds. 
  Display the calculated minutes and seconds.
• If you have 100seconds
• Convert into minutes and seconds?
*/

#include <iostream>
using namespace std;

int main()
{
	int sec,min,sec1;
	sec = 100; 
	min = sec/60;
	sec1 = sec-60;
	cout<<"Minutes + Seconds = "<< min <<" min "<< sec1 <<" sec "<<endl;
	return 0;
}