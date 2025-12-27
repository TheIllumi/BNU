#include <iostream>
using namespace std;

int main()
{
    int Array[10], temp, swaps=0;

    for (int i = 0; i <= 9; i++)
    {
        cout<<"Enter values to fill the array: ";
        cin>>Array[i];
    }

    for (int i = 0; i < 10-1; i++)
    {
        for (int j = 0; j < 10-i-1; j++)
        {
            if (Array[j] > Array[j+1])
            {
                temp = Array[j];
                Array[j]= Array[j+1];
                Array[j+1] = temp;
                swaps++;
            }
        }
    }
    cout<<"Array sorted: ";
    for (int k = 0; k < 10; k++)
    {
        cout<<Array[k]<<" ";
    }
    cout<<endl;
    cout<<"Amount of swaps taken to sort the array: "<<swaps<<endl;
    return 0;
}