#include <iostream>
#include <string>
using namespace std;

int main()
{
    int size;

    // Get the size and elements for the character array
    cout << "Enter the number of elements for the character array: ";
    cin >> size;

    char *characterArray = new char[size];

    // Enter characters in the array
    cout << "Enter " << size << " characters for the array:" << endl;
    for (int i = 0; i < size; i++)
    {
        cin >> characterArray[i];
    }

    // Display the array
    cout << "\nYour array is:" << endl;
    for (int i = 0; i < size; i++)
    {
        cout << characterArray[i] << " ";
    }
    cout << endl;

    // Allocate memory for the merged array
    int copiedSize = size;
    char *copiedArray = new char[copiedSize];

    // Make a copy of the array
    for (int i = 0; i < size; i++)
    {
        copiedArray[i] = characterArray[i];
    }

    // Display the copied array
    cout << "\nThe copied array is:" << endl;
    for (int i = 0; i < copiedSize; i++)
    {
        cout << copiedArray[i] << " ";
    }
    cout << endl;

    cout << "\nEnter a letter to replace the last entry of your array: ";
    char letter;
    cin >> letter;
    for (int i = size - 1; i > size - 2; i--)
    {
        characterArray[i] = letter;
    }

    cout << "\nEnter a letter to replace the last entry of your copied array: ";
    char newletter;
    cin >> newletter;
    for (int i = size - 1; i > size - 2; i--)
    {
        copiedArray[i] = newletter;
    }

    // Display the altered array
    cout << "\nPrinting your array: ";
    for (int i = 0; i < size; i++)
    {
        cout << characterArray[i] << " ";
    }
    cout << endl;

    // Display the altered copied array
    cout << "\nPrinting the copy: ";
    for (int i = 0; i < size; i++)
    {
        cout << copiedArray[i] << " ";
    }
    cout << endl;

    // Free the memory for the original arrays
    delete[] characterArray;

    // Release the memory for the merged array
    delete[] copiedArray;

    return 0;
}