#include <iostream>
#include <cmath>
using namespace std;

int main()
{
	int i,sq,ans;
	i =1;
	sq = 1;
	ans = 0;
	while(i<=5)
	{
		ans = pow(sq,2);
		cout<<ans<<endl;
		sq = sq + 1;
		i++;
	}
	return 0;
}