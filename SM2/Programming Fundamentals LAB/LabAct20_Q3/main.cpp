#include <iostream>
#include <cmath>
using namespace std;

const double PI = 3.14;
const double RATE = 0.25;

void findArea(float);
void findCircumference(float);

int main() {
    float radius;
    cout<<"Enter Radius: "<<endl;
    cin>>radius;
    float area;
    float circumference;
    cout<<"The radius = "<<radius <<endl;
    findArea(radius);
    findCircumference(radius);

    return 0;
}

void findArea( float x)
{
    int a = PI * pow(x,2);
    cout<<"The area = "<<a<<endl;
}

void findCircumference( float y)
{
    int c = 2 * PI * y;
    cout<<"The circumference = "<<c<<endl;
}