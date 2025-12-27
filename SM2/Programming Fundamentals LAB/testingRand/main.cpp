#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

int main() {
    srand(time(0));
    int i;
    int r_num;

    for (int j = 1; j < 10; j++)
    {
        r_num = rand() % 9 + 1;
        cout<<r_num<<endl;
    }
    return 0;
}
