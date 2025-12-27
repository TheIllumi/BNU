#include<iostream>
using namespace std;
int main()
{
    int num,digit1,digit2,digit3;
    int fact=1;
    cout<<"enter a 3 digit number: ";

    cin>>num;

    digit3=num%10;
    digit2=num%100/10;
    digit1=num%1000/100;

    cout<<"the digits are= "<<digit1<<", "<<digit2<<", "<<digit3<<endl;

    fact = 1;
    for(int i=1; i<=digit1; i++)
    {
        fact=fact*i;
    }
    cout<<"factorial of "<<digit1<<"= "<<fact<<endl;

    fact = 1;
    for(int j=1; j<=digit2; j++)
    {
        fact=fact*j;
    }

    cout<<"factorial of "<<digit2<<"= "<<fact<<endl;

    fact = 1;
    for(int k=1; k<=digit3; k++)
    {
        fact=fact*k;
    }

    cout<<"factorial of "<<digit3<<"= "<<fact<<endl;

    return 0;
}