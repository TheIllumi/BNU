/*
Q5:
Ask the user to enter a number as dividend. User also
enters another integer value as the divisor. Calculate the
quotient and the remainder after dividing the two
numbers values. Display dividend, divisor, quotient, and
the remainder.
*/

#include <iostream>
using namespace std;

int main()
{
    int dividend, divisor, quo, remain;
    cout << "Enter dividend = ";
    cin >> dividend;
    cout << "Enter divisor = ";
    cin >> divisor;
    quo = dividend / divisor;
    remain = dividend % divisor;
    cout << "Dividend = " << dividend << endl;
    cout << "Divisor = " << divisor << endl;
    cout << "Quotient = " << quo << endl;
    cout << "Remainder = " << remain << endl;
    return 0;
}