#include <iostream>
using namespace std;

/*
1. Write a C++ program that takes a 10-digit number and a single-digit (1-9)
 hit number from the user. If 10-digit numbers have that hit number, then it
 will be zero. Otherwise, display "no hit number in 10-digit." and display
 the same 10-digit number in the same order.
For Example:
Input:
User Enter: 9732665435
Hit number: 5
Output
Number: 9732660430
*/

int main()
{
    long long num0;
    long long num1, num2, num3, num4, num5, num6, num7, num8, num9, num10;

    int hit;

    // int num10;

    cout << "Enter a 10 digit number = ";
    cin >> num0;

    if (num0 >= 1000000000 && num0 <= 9999999999)
    {

        cout << "Enter hit number = ";
        cin >> hit;

        if (hit >= 0 && hit <= 10)
        {
            num1 = num0 % 10;
            num2 = num0 % 100 / 10;
            num3 = num0 % 1000 / 100;
            num4 = num0 % 10000 / 1000;
            num5 = num0 % 100000 / 10000;
            num6 = num0 % 1000000 / 100000;
            num7 = num0 % 10000000 / 1000000;
            num8 = num0 % 100000000 / 10000000;
            num9 = num0 % 1000000000 / 100000000;
            num10 = num0 % 10000000000 / 1000000000;

            int counter = 1;
            while (counter <= 9)
            {
                if (hit == num1)
                {
                    num1 = 0;
                }
                else if (hit == num2)
                {
                    num2 = 0;
                }
                else if (hit == num3)
                {
                    num3 = 0;
                }
                else if (hit == num4)
                {
                    num4 = 0;
                }
                else if (hit == num5)
                {
                    num5 = 0;
                }
                else if (hit == num6)
                {
                    num6 = 0;
                }
                else if (hit == num7)
                {
                    num7 = 0;
                }
                else if (hit == num8)
                {
                    num8 = 0;
                }
                else if (hit == num9)
                {
                    num9 = 0;
                }
                else if (hit == num10)
                {
                    num10 = 0;
                }
                else
                {
                    cout << counter << " = "
                         << "No hit number found" << endl;
                }
                counter++;
            }

            cout << "Number Entered = " << num0 << endl;
            cout << "Digit 1 = " << num9 << endl;
            cout << "Digit 2 = " << num8 << endl;
            cout << "Digit 3 = " << num7 << endl;
            cout << "Digit 4 = " << num6 << endl;
            cout << "Digit 5 = " << num5 << endl;
            cout << "Digit 6 = " << num4 << endl;
            cout << "Digit 7 = " << num3 << endl;
            cout << "Digit 8 = " << num2 << endl;
            cout << "Digit 9 = " << num1 << endl;
            cout << "Digit 10 = " << num10 << endl;
            
            cout << "Number: " << num10 << num9 << num8 << num7 << num6 << num5 << num4 << num3 << num2 << num1 << endl;
        }
        else
        {
            cout << "Hit number entered should be between 0 and 9" << endl;
        }
    }
    else
    {
        cout << "Number entered should be a 10 digit number" << endl;
    }
    return 0;
}
