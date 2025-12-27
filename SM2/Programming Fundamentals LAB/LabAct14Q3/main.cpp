#include <iostream>
using namespace std;

int main() {
    int base, power, Answer = 1;
    cout<<"Enter base: ";
    cin>>base;
    cout<<"Enter power: ";
    cin>>power;
    for (int i = 0; i < power; i++)
    {
        Answer = Answer * base;
    }
    cout<<"Answer: "<<Answer<<endl;
    return 0;
}
