#include<iostream>
using namespace std;
int main()
{
    int num,digit1,digit2,digit3;
    int fact=1;
    cout<<"enter a 3 digit number: ";
    cin>>num;
    if(num<0)
    {
        cout<<"invalid value entered";
    }
    else {
        digit3=num%10;
        digit2=num%100/10;
        digit1=num%1000/100;
        cout << "the digits are= " << digit1 << ", " << digit2 << ", " << digit3 << endl;
        for (int i = 1; i <= digit1; i++) {
            fact = fact * i;
        }
        cout << "factorial of " << digit1 << "= " << fact << endl;
        int product=1;
        product= product*fact;
        int sum = 0;
        sum = sum + fact;
        fact = 1;
        for (int i = 1; i <= digit2; i++) {
            fact = fact * i;
        }
        cout << "factorial of " << digit2 << "= " << fact << endl;
        product= product*fact;
        sum = sum + fact;
        fact = 1;
        for (int i = 1; i <= digit3; i++) {
            fact = fact * i;
        }
        cout << "factorial of " << digit3 << "= " << fact << endl;
        product= product*fact;
        sum = sum + fact;
        cout << "the sum of factorials= " << sum << endl;
        if (num==sum) {
            cout << "expression is equal" << endl;
        } else {
            cout << "expression is not equal" << endl;
        }

        if(product<=1000)
        {
            cout<<"product= "<<product<<endl;
            int n1,n2;
            n1=product%10;
            product=product/10;
            n2=product%10;
            cout<<"the last two digits of the product are= "<<n2<<","<<n1<<endl;
        }
        else if(product>1000 && product<5000)
        {
            cout<<"product= "<<product<<endl;
            int n1;
            n1=product%10;
            cout<<"the last digit of product= "<<n1<<endl;
        }
        else
        {
            cout<<"product= "<<product<<endl;
        }

    }
    return 0;
}