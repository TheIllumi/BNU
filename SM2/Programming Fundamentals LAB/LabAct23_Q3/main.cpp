#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

void OutFunc();
void InFunc();

int main() {
    srand(time(0));
    OutFunc();
    InFunc();
    return 0;
}

void OutFunc() {
    ofstream outputFile("C:\\Users\\saadm\\Downloads\\BNU\\SM2\\Programming Fundamentals\\Random.txt");
    if (!outputFile) {
        cout << "Error opening file for writing!" << endl;
        return;
    }

    for (int i = 0; i < 10; ++i) {
        int num = rand() % 11;
        outputFile << num << " ";
    }

    outputFile.close();
}

void InFunc() {
    ifstream inputFile("C:\\Users\\saadm\\Downloads\\BNU\\SM2\\Programming Fundamentals\\Random.txt");
    if (!inputFile) {
        cout << "Error opening file for reading!" << endl;
        return;
    }

    ofstream outputFile("C:\\Users\\saadm\\Downloads\\BNU\\SM2\\Programming Fundamentals\\Factorials.txt");
    if (!outputFile) {
        cout << "Error opening file for writing factorials!" << endl;
        return;
    }

    int numbers[10];
    for (int i = 0; i < 10; ++i) {
        inputFile >> numbers[i];
    }
    inputFile.close();

    for (int i = 0; i < 10; ++i) {
        int num = numbers[i];
        unsigned long long factorial = 1;

        for (int j = 1; j <= num; ++j) {
            factorial *= j;
        }

        cout << "Factorial of " << num << " is " << factorial << endl;
        outputFile << "Factorial of " << num << " is " << factorial << endl;
    }

    outputFile.close();
    cout << "Factorials calculated and saved to Factorials.txt" << endl;
}
