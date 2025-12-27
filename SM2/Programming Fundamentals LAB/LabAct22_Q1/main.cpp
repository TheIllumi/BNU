#include <iostream>
#include <fstream>
using namespace std;

int main() {
    ifstream inputFile("C:\\Users\\saadm\\Downloads\\BNU\\SM2\\Programming Fundamentals\\File.txt");
    if (!inputFile) {
        cout << "Error opening file." << endl;
        return 1;
    }

    int number;
    int sum = 0;
    int productOfEvens = 1;
    bool hasEven = false;

    for (int i = 0; i < 10; ++i) {
        if (inputFile >> number) {
            sum += number;
            if (number % 2 == 0) {
                productOfEvens *= number;
                hasEven = true;
            }
        } else {
            cout << "Error reading number from file." << endl;
            return 1;
        }
    }

    inputFile.close();

    cout << "Sum of all integers: " << sum << endl;
    if (hasEven) {
        cout << "Product of even numbers: " << productOfEvens << endl;
    } else {
        cout << "No even numbers found in the file." << endl;
    }

    return 0;
}
