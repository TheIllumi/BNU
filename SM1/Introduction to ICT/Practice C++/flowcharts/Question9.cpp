/*
~Question 9:

Draw a flowchart to show how to obtain the HCF and LCM of two numbers.

!Task Analysis.
We know that HCF (Highest Common Factor) of two numbers is the largest number that can divide the two numbers
without leaving any remainder and the LCM (Least Common Multiple) of two numbers is the smaller number that is
divisible by both the numbers. The best way to obtain the HCF is the method of division in which one number is divided by
another 70
Flowchart and Algorithm Basics number to see if the remainder is zero. The divisor number is the HCF. If it
is other than zero, then the divisor is made the dividend, the remainder is made the divisor, and the division is repeated
to obtain the remainder again. This change of dividend and divisor is done repeatedly until we get the divisor that leaves
zero as the remainder and the divisor in the last case is the HCF of the given numbers. The easiest way to find the LCM
is to use the relationship between the HCF and LCM. We know that the product of two numbers equals the product of their
HCF and LCM. The LCM can be obtained by dividing the product of the given numbers by that HCF.

!This is shown below:
LCM x HCF of two numbers = product of the two numbers
LCM of two numbers = (Product of the two numbers) / (HCF of the two numbers)
We require two inputs only: the two numbers we use to determine the HCF and LCM.
*/

/*16, 20*/

#include <iostream>
using namespace std;

int main()
{
    int num1, num2, x, y;
    int HCF, LCM, rem;
    cout << "Enter first number = ";
    cin >> num1;
    cout << "Enter second number = ";
    cin >> num2;
    cout << "First number = " << num1 << "\n Second number = " << num2 << endl;
    x = num1;
    y = num2;
    while (y != 0)
    {
        rem = y;
        y = x % y;
        x = rem;
    }

    HCF = x;
    LCM = (num1 * num2) / HCF;
    cout << "HCF = " << HCF << endl;
    cout << "LCM = " << LCM << endl;
    return 0;
}