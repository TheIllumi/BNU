#include <iostream>
using namespace std;

int main() {
    int Array[10];
    int target;

    for (int i = 0; i < 10; i++)
    {
        cout<<"Enter values in the array: ";
        cin>>Array[i];
    }
    cin.clear();

    cout<<"Enter target: ";
    cin>>target;

    int Index1st, Index2nd;
    for (int j = 0; j < 10; j++)
    {
        Index1st = Array[j];
        for (int k = j; k < 10; k++)
        {
            Index2nd = Array[k];
            if ((Index1st+Index2nd)==target)
            {
                cout<<"["<<j<<","<<k<<"]"<<endl;
            }
        }
    }
    return 0;
}
