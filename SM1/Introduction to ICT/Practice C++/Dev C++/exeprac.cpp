#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
using namespace std;

int main()
{
srand(time(0));
int i;
int r_num, myguess;

r_num = rand() % 10 + 1;
cout<<" Add 2 to your number"<<endl;

myguess = r_num + 2;
cout<<" Multiply your current value by 2"<<endl;

system("PAUSE");
myguess = myguess * 2;
cout<<" Subtract 2 from your current value"<<endl;

system("PAUSE");
myguess = myguess - 2;
cout<<" Divide your current value by 2"<<endl;

system("PAUSE");
myguess = myguess / 2;
cout<<" Subtract your original number from your current value"<<endl;

system("PAUSE");
myguess = myguess - r_num;
cout<<"Number in your mind = "<< myguess;

return 0;
}