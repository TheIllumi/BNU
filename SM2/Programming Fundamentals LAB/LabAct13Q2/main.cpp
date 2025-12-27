#include <iostream>
#include <math.h>

using namespace std;

int RoundingFunction(float x)
{
    int y = float(x + 0.5);
    return y;
}

int main() {
    float num;
    cout<<"Enter number to be rounded: ";
    cin>>num;
    cout<<"Number entered: "<<num<<endl;
    cout<<"Number rounded: "<<RoundingFunction(num)<<endl;
    return 0;
}
