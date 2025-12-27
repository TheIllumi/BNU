/* 
Program 9:
• Design a flowchart to swap the two values entered by 
  the user
  
  For example the values entered by the user:
  A = 10
  B = 50
  
  Values displayed by your code:
  A= 50
  B = 10
*/

#include <iostream>
#include <cmath>
using namespace std;

int main()
{
	int A;
	int B;
	int X;
	cin>>A;
	cin>>B;
	X = A;
	A = B;
	B = X;
	cout<<"A = "<<A<<endl;
	cout<<"B = "<<B<<endl;
	return 0;
}