#include <iostream>
using namespace std;

class Demos {
private:
    const int x; // Constant integer member variable

public:
    // Constructor to initialize the constant member x
    Demos(int value) : x(value) {
        // x is initialized using the initializer list because it is a constant.
    }

    // Const member function to display the value of x
    void display() const {
        cout << "Inside the display function." << endl;
        cout << "The value of x is: " << x << endl;
    }

    // Regular member function
    void showMessage() {
        cout << "Inside show message function." << endl;
    }
};

int main() {
    // Create an object of the class and initialize x with the value 42
    Demos d1(42);

    // Call the regular member function
    d1.showMessage();

    // Call the const member function
    d1.display();

    return 0;
}
