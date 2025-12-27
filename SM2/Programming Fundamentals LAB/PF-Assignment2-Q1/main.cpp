// Q1:
#include <iostream>
#include <cmath>
using namespace std;

int main() {
    int Number, CountNumber, DigitCount = 0, Sum = 0, Product = 1, LastDigit, Temp, Factorial;
    cout<<"Enter a number to find factorial of every single digit: ";
    cin>>Number;
    cout<<endl;
    if (Number>=0)
    {
        CountNumber = Number;
        while (CountNumber != 0)
        {
            CountNumber = CountNumber/10;
            DigitCount++;
        }

        cout<<"Number Entered = "<<Number<<endl;
        cout<<endl;

        LastDigit = Number;
        int Input = Number;
        for (int i = 1; i <= DigitCount; i++)
        {
            Factorial = 1;
            LastDigit = Input%10;
            Temp = Input/10;
            for (int j = 1; j <= LastDigit; j++)
            {
                Factorial = Factorial * j;
            }
            Input = Temp;
            Sum = Sum + Factorial;
            Product = Product * Factorial;
        }

        cout<<"Sum of factorials = "<<Sum<<endl;

        if (Sum == Number)
        {
            cout<<"Expression is equal"<<endl;
            cout<<endl;
        }
        else
        {
            cout<<"Expression is not equal"<<endl;
            cout<<endl;
        }

        int Digit1, Digit2;
        if (Product <= 1000)
        {
            cout<<"Product of factorials: "<<Product<<endl;

            Digit1 = Product%10;
            Digit2 = Product%100/10;
            cout<<"Last two digits of product:"<<endl;
            cout<<"Second last digit = "<<Digit2<<"\t"<<"Last digit = "<<Digit1<<endl;
        }
        else if (Product > 1000 && Product < 5000)
        {
            cout<<"Product of factorials: "<<Product<<endl;
            Digit1 = Product%10;
            cout<<"Last digit of the product: "<<Digit1<<endl;
        }
        else
        {
            cout<<"Product of factorials: "<<Product<<endl;
        }
    }
    else
    {
        cout<<"Invalid Value entered"<<endl;
    }
    return 0;
}
