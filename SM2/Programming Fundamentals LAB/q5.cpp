#include <iostream>
using namespace std;

int main()
{
    int Value;
    cout << "Enter a value < 100: ";
    cin >> Value;
    for (int i = Value; i >= 100; i++)
    {
        cout << "Enter a value < 100: ";
        cin >> Value;
    }

    return 0;
}