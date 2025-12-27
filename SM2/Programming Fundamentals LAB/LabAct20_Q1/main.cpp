#include <iostream>
#include <cmath>
using namespace std;

int cubeIt(int x);
int squareIt(int x);

int main() {
    int x;
    cout << "Enter Number: ";
    cin >> x;

    int cube = cubeIt(x);
    int square = squareIt(x);

    cout << "The cube of " << x << " is " << cube << endl;
    cout << "The square of " << x << " is " << square << endl;

    return 0;
}

int cubeIt(int x) {
    return pow(x, 3);
}

int squareIt(int x) {
    return pow(x, 2);
}
