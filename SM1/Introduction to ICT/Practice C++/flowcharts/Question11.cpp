/*
!Question 11:
Construct a flowchart for obtaining the sum of a given number of terms (N) for a given value of x in the following
mathematical series:
X + X2 /2 + X3 /3 + ...... up to N terms.

!Task Analysis.
We need to know the values of two unknown quantities as input: the value of X and that of N, the number of terms. We
must find a general expression from which we can identify different terms. The expression X/I yields different terms for
different values of I from 1 to N. We can evaluate the expression for some given value of X and the obtained value can be
stored in some location, say S, that initially contains 0. Successive addition of the evaluated values for all the terms to
the content of S will give us the desired sum.
*/

#include <iostream>
using namespace std;

int main()
{
    double integer, Nth, sum;
    cout << "Enter integer = ";
    cin >> integer;
    cout << "Enter sum of nth terms = ";
    cin >> Nth;
    int counter = 1;
    while (counter <= Nth)
    {
        sum = sum + counter * (integer / counter);
        counter++;
    }
    cout << "sum = " << sum << endl;
    return 0;
}