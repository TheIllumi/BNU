#include <iostream>
using namespace std;

void maximum(int x, int y, int z);
int main() {
    int x, y, z;
    cout<<"Enter integer one: ";
    cin>>x;
    cout<<"Enter integer two: ";
    cin>>y;
    cout<<"Enter integer three: ";
    cin>>z;
    maximum(x,y,z);
    return 0;
}

void maximum(int x, int y, int z)
{
    if(x>y)
    {
        if (x>z)
        {
            cout<<"Max value is x: "<<x<<endl;
        }
        else
        {
            cout<<"Max value is z: "<<z<<endl;
        }
    }
    else
    {
        if(y>x)
        {
            if (y>z)
            {
                cout<<"Max value is y: "<<y<<endl;
            }
            else
            {
                cout<<"Max value is z: "<<z<<endl;
            }
        }
    }
}