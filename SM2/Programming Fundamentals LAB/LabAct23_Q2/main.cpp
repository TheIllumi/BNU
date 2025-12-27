#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
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
    for (int i = 0; i < 50; ++i) {
        int num = rand() % 11;
        outputFile << num << " ";
    }
    outputFile.close();
}
void InFunc()
{
    ifstream inputFile("Random.txt");
    if (!inputFile) {
        cout << "Error opening file for reading!" << endl;
        return;
    }
    int numbers[50];
    int count[11] = {0};
    for (int i = 0; i < 50; ++i) {
        inputFile >> numbers[i];
        count[numbers[i]]++;
    }
    inputFile.close();
    cout << "Count of duplicate numbers:" << endl;
    for (int i = 0; i <= 10; ++i) {
        if (count[i] > 1) {
            cout << "DupliKate Number " << i << ": " << count[i] << endl;
        }
    }
}
