#include <iostream>
using namespace std;

/*
1. Write a C++ program that takes a 10-digit integer as input and
sorts the digits in descending order.
For Example:
Input:
User Enter: 12936497857
Output
Number: 9877654321
*/

int main()
{
    int num0;
    int num1, num2, num3, num4;
    // int num10;

    cout << "Enter a 9 digit number = ";
    cin >> num0;

    if (num0 >= 1000 && num0 <= 9999)
    {

        num1 = num0 % 10;
        num2 = num0 % 100 / 10;
        num3 = num0 % 1000 / 100;
        num4 = num0 % 10000 / 1000;

        if (num1 > num2 && num1 > num3 && num1 > num4)
        {
            cout << num1;
        }
        else if (num2 > num1 && num2 > num3 && num2 > num4)
        {
            cout << num2;
        }
        else if (num3 > num1 && num3 > num4 && num3 > num4)
        {
            cout << num3;
        }
        else
        {
            cout << num4;
        }

        if (num1 > num3 && num1 > num4)
        {
            cout << num1;
        }
        else if (num2 > num3 && num2 > num4)
        {
            cout << num2;
        }
        else if (num3 > num2 && num3 > num4)
        {
            cout << num3;
        }
        else
        {
            cout << num4;
        }

        if (num1 > num4)
        {
            cout << num1;
        }
        else if (num2 > num4)
        {
            cout << num2;
        }
        else if (num3 > num4)
        {
            cout << num3;
        }
        else
        {
            cout << num4;
        }

        cout << "Number Entered = " << num0 << endl;
        cout << "Digit 1 = " << num4 << endl;
        cout << "Digit 2 = " << num3 << endl;
        cout << "Digit 3 = " << num2 << endl;
        cout << "Digit 4 = " << num1 << endl;

        cout << "Number: " << num4 << num3 << num2 << num1 << endl;
    }
    else
    {
        cout << "Number entered should be a 4 digit number" << endl;
    }
    return 0;
}
