#include <iostream>
using namespace std;

/*
Lab: Dynamic Array Merging
Objective:
    - To practice dynamic memory allocation in C++.
    - To merge two arrays into a third dynamically allocated array.
    - To properly manage memory by releasing the original arrays after merging.
*/

int main()
{
    int size1, size2;

    // Get the size and elements for the first array
    cout << "Enter the number of elements for the first array: ";
    cin >> size1;

    int *array1 = new int[size1];
    cout << "Enter " << size1 << " integers for the first array:" << endl;

    for (int i = 0; i < size1; i++)
    {
        cin >> array1[i];
    }

    // Get the size and elements for the second array
    cout << "\nEnter the number of elements for the second array: ";
    cin >> size2;

    int *array2 = new int[size2];
    cout << "Enter " << size2 << " integers for the second array:" << endl;

    for (int i = 0; i < size2; i++)
    {
        cin >> array2[i];
    }

    // Allocate memory for the merged array
    int mergedSize = size1 + size2;
    int *mergedArray = new int[mergedSize];

    // Copy the first array into the merged array
    for (int i = 0; i < size1; i++)
    {
        mergedArray[i] = array1[i];
    }

    // Copy the second array into the merged array
    for (int i = 0; i < size2; i++)
    {
        mergedArray[size1 + i] = array2[i];
    }

    // Free the memory for the original two arrays
    delete[] array1;
    delete[] array2;

    // Display the merged array
    cout << "\nThe merged array is:" << endl;
    for (int i = 0; i < mergedSize; i++)
    {
        cout << mergedArray[i] << " ";
    }
    cout << endl;

    // Release the memory for the merged array
    delete[] mergedArray;

    return 0;
}