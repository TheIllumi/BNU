// Lab4Practice_SecB.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib> // Needed for rand() and srand()
#include <ctime>   // Needed for time()
#include <vector>
#include <cstring>
using namespace std;

void TraverseString(string &str, int N);

int main()
{

    // OPENING ACCOUNTS FILE FOR SIZE
    ifstream inputFile("engmix.txt");
    if (!inputFile)
    {
        cout << "Error opening file!" << endl;
        return 1;
    }

    string line;
    int size1 = 0, size2 = 0;
    while (getline(inputFile, line))
    {
        size1++;
        if (line.length() >= 7)
        {
            size2++;
        }
    }
    inputFile.close(); // Close the file

    string *allwords = new string[size1];
    string *selectedwords = new string[size2];

    ifstream inFile("engmix.txt");
    if (!inFile)
    {
        cout << "Error opening file!" << endl;
        return 1;
    }

    int i = 0, j = 0;
    while (getline(inFile, line) && i < size1 && j < size2)
    {
        allwords[i] = line;
        i++;
        if (line.length() >= 7)
        {
            selectedwords[j] = line;
            j++;
        }
    }
    inputFile.close(); // Close the file

    /*for (int i = 0; i < size2; i++)
    {
        cout << selectedwords[i] << endl;
    }*/

    srand(time(0));

    int randomNum = rand() % size2;
    string randomstring = selectedwords[randomNum];
    cout << "The baseword: " << randomstring << endl;

    // ------------------------------------------------------------------------- //

    // Part 4
    string name;
    bool flag = false;
    bool flag2 = false;
    do
    {
        cout << "Enter your name using baseword: ";
        cin >> name;
        for (int k = 0; k < size2; ++k)
        {
            if (selectedwords[k] == name)
            {
                flag = true;
            }
        }
        for (int j = 0; j < name.length(); ++j)
        {
            for (int k = 0; k < randomstring.length(); ++k)
            {
                if (name[j] == randomstring[k])
                {
                    cout << "TRUE" << endl;
                    flag2 = true;
                }
            }
        }
        cout << "FOUND IT YO" << endl;
    } while (flag == true && flag2 == true);

    return 0;
}

void TraverseString(string &str, int N)
{
    // Traverse the string
    for (int i = 0; i < N; i++)
    {

        // Print current character
        cout << str[i] << " ";
    }
}