#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
using namespace std;

int main()
{
	srand(time(0));
	int i;
	int r_num;
	
	for(i=1; i<=10; i++)
	{
		// to generate numbers from 1 to 6
		r_num = rand() % 6 + 1;
		cout<<r_num<<endl;
	}
	return 0;
}