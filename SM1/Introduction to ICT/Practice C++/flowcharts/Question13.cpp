/*
!Question 13:
Develop a flowchart to show how to find out the sum of the following mathematical series:

!Task Analysis.
The inputs required here are X and N. The coefficients in this series bear a relationship with each other. The coefficient
of the 2nd term is 1/ 2, that of the 3rd term is 1/2 x 3/4, and that of the 4th term is 1/2 x ¾ x 5/6. We observe that
each coefficient is a result of evaluating an expression of the form 2 1 – I / 2 I for I = 1, 2 .........., an expression that
generates an odd number in the numerator and an even number in the denominator. For I = 1, the coefficient is 1/2 if it
is stored somewhere and it is multiplied by the value of the expression next time for I = 2, we get the 3rd coefficient;
that is, we evaluate an expression of the form C * (21 – 1)/2I for C = 1 initially. The successive values of I from 1 to n – 1
will give the coefficients from the 2nd to the nth term. Again, if we take C = – C * (2I – 1)/2I, we get the coefficients with
sign positive or negative. Now, multiplying the expression by X2I+1 for different values of I, we get the successive terms,
except for the 1st term. Now, if we initialize S with the value of X and add the terms evaluated successively to the current
value of S, we get the desired sum of the series
*/

#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    double x, sum = 0.0;
    int n;
    cout << "Enter the value of x: ";
    cin >> x;
    cout << "Enter the number of terms (N): ";
    cin >> n;

    double coefficient = 0.5; // Initialize coefficient
    double term = x;          // Initialize the first term with x

    for (int i = 2; i <= n; ++i)
    {
        coefficient *= (2.0 * (i - 1)) / (2.0 * i); // Update coefficient
        term *= x * x;                              // Calculate the next term
        sum += term * coefficient;                  // Add the term to the sum
    }

    cout << "Sum of the series is: " << sum << endl;

    return 0;
}