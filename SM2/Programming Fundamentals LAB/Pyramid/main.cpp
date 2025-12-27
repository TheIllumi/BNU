#include <iostream>
using namespace std;

int main() {
    for (int i = 1; i <= 5; i++)
    {
        cout<<"*";

        for (int j = 5; j > i; j--) {
            cout<<"-";

        }
        cout<<endl;
    }

    return 0;
}
