#include <iostream>
#include <math.h>
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
    long long num, num2;
    int hit;
    do
    {
        cout << "Enter a 10-digit number: ";
        cin >> num;
    } while (num < 1000000000 || num > 9999999999);
    num2 = num;
    cin.clear();

    cout << "Enter hit number: ";
    cin >> hit;

    for (int i = 0; i < 10; i++)
    {
        int temp = num2 % 10;
        num2 /= 10;
        if (temp == hit)
        {
            num -= (temp * pow(10, i));
        }
    }

    cout << endl
         << "modified num = " << num;

    return 0;
}