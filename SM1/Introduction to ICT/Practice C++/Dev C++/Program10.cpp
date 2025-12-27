/* 
Program 10:
• Design a flowchart to input temperature in degree 
  Fahrenheit and to display after converting it to degree 
  Centigrade.
  
  C = (F - 32) * 5/9
*/

#include <iostream>
#include <cmath>
using namespace std;

int main()
{
	float F,C;
	cout<<"Enter temperature in degree Fahrenheit = ";
	cin>>F;
	C = (F - 32) * 5/9;
	cout<<"Fahrenheit = "<<F<<endl;
	cout<<"Centigrade = "<<C<<endl;
	return 0;
}