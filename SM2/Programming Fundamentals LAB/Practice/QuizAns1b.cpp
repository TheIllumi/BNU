#include <iostream>
using namespace std;
int main()
{

    int num1 = 0, num2 = 0, sub = 0, i = 1;
    cout << "Enter 1st number : " << endl;
    cin >> num1;
    cout << "Enter 2nd number : " << endl;
    cin >> num2;
    sub = num1 + (-num2);

    if (num1 < num2)
    {
        int temp = num2;
        while (i < num1)
        {
            num2 = temp + num2;
            i++;
        }
    }
    else
    {

        int temp = num2;
        while (i < num1)
        {
            num2 = temp + num2;
            i++;
        }
    }
    if (sub < 0)
    {
        sub = -sub;
    }
    cout << "Sub : " << sub << endl;
    cout << "Mul : " << num2 << endl;
    return 0;
}