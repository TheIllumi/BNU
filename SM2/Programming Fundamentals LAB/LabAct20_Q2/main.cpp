#include <iostream>
using namespace std;

void calNetPay(int hours, float rate);

int main() {
    int hoursWorked = 20;
    float payRate = 5.00;
    calNetPay(hoursWorked, payRate);

    return 0;
}

void calNetPay(int hours, float rate)
{
    float net = hours * rate;
    cout<<"The net pay is $"<<net<<endl;
}
