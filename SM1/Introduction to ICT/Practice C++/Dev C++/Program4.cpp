/* 
Program 4:
• Write program logic for the following:
• Ask the user to enter three integer values
• Store them in x, y, and z
• Calculate the product of three values and store in PROD
• Calculate the square of each value and store in Sq_x, 
  Sq_y, Sq_z
• Also calculate the sum of three entered values and store 
  in SUM
• Display PROD, Sq_x, Sq_y, Sq_z, SUM
• Display a message at the end “ That’s all for now..”
*/

#include <iostream>
#include <cmath>
using namespace std;

int main()
{
	int x,y,z;
	int PROD;
	int Sq_x,Sq_y,Sq_z;
	int SUM;
	cout<<"Enter integer values of x, y and z respectively: "<<endl;
	cin>>x;
	cin>>y;
	cin>>z;
	PROD = x*y*z;
	SUM = x+y+z;
	Sq_x = pow(x,2);
	Sq_y = pow(y,2);
	Sq_z = pow(z,2);
	cout<<"x = "<<x<<endl;
	cout<<"y = "<<y<<endl;
	cout<<"z = "<<z<<endl;
	cout<<"Product = "<<PROD<<endl;
	cout<<"Sum = "<<SUM<<endl;
	cout<<"Squrare of x = "<<Sq_x<<endl;
	cout<<"Square of y = "<<Sq_y<<endl;
	cout<<"Square of z = "<<Sq_z<<endl;
	return 0;
}