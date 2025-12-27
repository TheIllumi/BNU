// prime or not
#include <iostream>
using namespace std;

int main() 
{
    int counter = 0, i = 2, number;

    cout << "enter number : " << endl;
    cin >> number;

    while (i <= number) {
        if (number % i == 0) {
            counter++;
        }
        i++;
    }

    if (counter == 1) {
        cout << "prime";
    }
    else {
        cout << "not prime";
    }
    return 0;
}