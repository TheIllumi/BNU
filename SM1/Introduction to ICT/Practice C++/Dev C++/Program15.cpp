/*
Program 15:
• Write the program logic to print the right most digit of a
  number
*/

#include <iostream>
#include <cmath>
using namespace std;

int main()
{
	int x, y;
	cout << "Enter an integer = ";
	cin >> x;
	y = x % 10;
	cout << "Integer = " << x << endl;
	cout << "Right most digit of the integer = " << y << endl;
	return 0;
}