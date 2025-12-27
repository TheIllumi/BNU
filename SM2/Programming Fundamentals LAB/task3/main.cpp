#include <iostream>
using namespace std;

float func_avg(int t[5]);

int main() {
    int marks[5];
    for (int i = 0; i < 5; i++)
    {
        cin>>marks[i];
    }
    cout<<"avg scroe"<<func_avg(marks)<<endl;
    if (func_avg(marks) > 8)
    {
        cout<<"Well done"<<endl;
    }
    else
    {
        cout<<"Work hard"<<endl;
    }
    return 0;
}

float func_avg(int t[5])
{
    int sum = 0;
    for (int i = 0; i < 5; i++)
    {

        sum = sum + t[i];
    }
    float avg;
    avg = sum / 5.0;
    return avg;
}
