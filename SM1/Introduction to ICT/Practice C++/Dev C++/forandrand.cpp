#include <iostream>
#include <iomanip>
#include <cstdlib>
using namespace std;

int main()
{
	int i;
	int r_num;
	
	for(i=1; i<=10; i++)
	{
		r_num = rand();
		cout<<r_num<<endl;
	}
	return 0;
}