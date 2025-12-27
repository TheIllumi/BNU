#include <iostream>
using namespace std;

int main()
{
    int column = 0;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 1; j < i; j++)
        {
            cout << "*";
        }
    }

    return 0;
}