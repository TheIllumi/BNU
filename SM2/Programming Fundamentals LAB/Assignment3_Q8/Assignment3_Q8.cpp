#include <iostream>
using namespace std;

int main()
{
    int TotalSeats = 10;
    int BusinessSeats = 5;
    int EconomySeats = 5;
    char Seats[] = {'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S'};
    int Choice;
    int unallocatedCount = 0;

    cout << "Enter \n Business Class: 1 \n Economy Class: 2" << endl;
    for (int i = 0; i < TotalSeats; i++)
    {
        cin >> Choice;
        bool allocated = false;

        if (Choice == 1)
        {
            for (int j = 0; j < BusinessSeats; j++)
            {
                if (Seats[j] == 'S')
                {
                    Seats[j] = 'B';
                    allocated = true;
                    break;
                }
            }
            if (!allocated)
            {
                cout << "Business class seats are full. Unable to allocate seat.\n";
                unallocatedCount++;
            }
        }
        else if (Choice == 2)
        {
            for (int j = EconomySeats; j < TotalSeats; j++)
            {
                if (Seats[j] == 'S')
                {
                    Seats[j] = 'E';
                    allocated = true;
                    break;
                }
            }
            if (!allocated)
            {
                cout << "Economy class seats are full. Unable to allocate seat.\n";
                unallocatedCount++;
            }
        }
        else
        {
            cout << "Invalid choice. Unable to allocate seat.\n";
            unallocatedCount++;
        }
    }

    cout << "Current seat assignments:" << endl;
    for (int i = 0; i < TotalSeats; i++)
    {
        cout << Seats[i] << " ";
    }
    cout << endl;

    cout << "S indicates unallocated seats." << endl;
    cout << "Number of seats not allocated: " << unallocatedCount << endl;

    return 0;
}
