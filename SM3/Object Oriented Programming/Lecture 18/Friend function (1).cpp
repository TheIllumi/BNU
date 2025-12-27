#include <iostream>
using namespace std;

class Box {
private:
    double length; 

public:
    Box(double l) : length(l) {}

    friend void showLength(Box b); 
};

// Define the friend function
void showLength(Box b) {
    cout << "The length of the box is: " << b.length << endl; 
}

int main() {
    Box myBox(10.5); 
    showLength(myBox); 
    return 0;
}
