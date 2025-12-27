#include <iostream>
using namespace std;

int sqr (int num);
int main() {
    int num;
    cout<<"Enter number: ";
    cin>>num;
    cout<<"Square: "<<sqr(num)<<endl;
    return 0;
}

int sqr (int num)
{
    int sqr = num*num;
    return sqr;
}
