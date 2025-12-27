#include <iostream>
#include <vector>
using namespace std;

class Shape {
public:
    vector<double> dimensions;

    explicit Shape(const vector<double>& dims) : dimensions(dims) {}

    void displayDimensions() const {
        for (double dim : dimensions) {
            cout << dim << " ";
        }
        cout << endl;
    }
};

class Rectangle : public Shape {
public:
    explicit Rectangle(const vector<double>& dims) : Shape(dims) {}

    [[nodiscard]] double area() const {
        if (dimensions.size() >= 2) {
            return dimensions[0] * dimensions[1];
        } else {
            return 0.0;
        }
    }
};

int main() {
    vector<double> dims = {5.0, 10.0};
    Rectangle rect(dims);
    rect.displayDimensions();
    cout << rect.area() << endl;
    return 0;
}