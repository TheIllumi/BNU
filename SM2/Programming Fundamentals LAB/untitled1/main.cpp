#include <iostream>
using namespace std;

int main() {
    int SIZE = 20;

    // Array with employee IDs sorted in ascending order.
    int idNums[] = {101,142,147,189,199,207,222,
                    234,289,296,310,319,388,394,417,429,
                    447,521,536,600};

    int empID; //To hold an employee ID
    // Get an employee ID to search for
    cout<<"Enter the employee ID you wish to search for: ";
    cin>>empID;

    int first = 0;         // first array element
    int last = SIZE - 1;  //Last array element
    int middle;          // Midpoint of search
    bool found = false; // Flag
    int position;

    while(!found && first <= last)
    {
        middle = (first+last)/2;  // Calculate midpoint

        if (idNums[middle]==empID)  // If value is found at mid
        {
            found = true;
            position = middle;
        }
        else if (idNums[middle] > empID)
        {
            last = middle - 1;      // if value is in LOWER half
        }
        else
        {
            first = middle + 1;    // if value is in UPPER half
        }

        if (position == -1)  // If position contains -1 the empID was not found
        {
            cout<<"That empID does not exist in the array. \n";
        }
        else // Otherwise position contains the subscript of the specified employee ID in the array.
        {
            cout<<"That ID is the element number "<< position+1;
            cout<<" in the array.\n";
        }
    }
    return 0;
}
