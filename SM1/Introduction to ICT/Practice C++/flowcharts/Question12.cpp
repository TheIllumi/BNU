/*
!Question 12:

*/

#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    int integer, nth;
    double sum;
    cout << "Enter integer = ";
    cin >> integer;
    cout << "Enter nth term = ";
    cin >> nth;
    sum = integer / (2 * nth - 1);
    cout << "sum = " << sum << endl;
    return 0;
}