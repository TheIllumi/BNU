#include <iostream>
using namespace std;

int main()
{
    int value;
    cout << "Enter a value < 100: ";
    cin >> value;

    if(value < 100) {
        while (value >= 100) {
            cout << "Enter a value < 100: ";
            cin >> value;
        }
    }

    return 0;

    int value;
    do {
        cout << "Enter a value < 100: ";
        cin >> value;
    } while (value >= 100)
}