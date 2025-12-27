#include <iostream>
using namespace std;

int main() {
    int Array[]={4,1,2,1,2};
    int size = sizeof (Array)/sizeof (Array[0]);
    int Answer = 0;
    for (int i = 0; i < size; i++)
    {
        Answer = Answer ^ Array[i];
    }
    cout << "Answer: " << Answer <<endl;
    return 0;
}
