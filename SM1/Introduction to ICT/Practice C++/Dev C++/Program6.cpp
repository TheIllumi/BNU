/* 
Program 6:
• Design a flowchart that will determine the area and 
  perimeter of a rectangle
• Accept the length and width from the user
• Calculate and display the area and perimeter using the 
  following formulae:
  
  Area = Length * Width
  
  Perimeter = 2(Length + Width)
*/

#include <iostream>
#include <cmath>
using namespace std;

int main()
{
	int L;
	int W;
	int Area;
	int Perimeter;
	cout<<"Enter Length of a rectangle = ";
	cin>>L;
	cout<<"Enter Width of a rectangle = ";
	cin>>W;
	Area = L*W;
	Perimeter = 2*(L+W);
	cout<<"Length = "<<L<<endl;
	cout<<"Width = "<<W<<endl;
	cout<<"Area = "<<Area<<endl;
	cout<<"Perimeter = "<<Perimeter<<endl;
	return 0;
}