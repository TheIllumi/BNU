/* 
Program 2:
Write a program that allows the user to enter the last 
names of a candidate in a local elections of Punjab 
province. 
It also accepts the number of votes received by 
candidate. 
The program then outputs the names of candidate, 
number of votes received
*/

#include <iostream>
#include <string>
using namespace std;

int main()
{
	int Votes;
	string LastName;
	cout<<"Enter last name of a candidate = ";
	cin>>LastName;
	cout<<"Enter votes received by the candidate = ";
	cin>>Votes;
	cout<<"Last Name = "<<LastName<<endl;
	cout<<"Votes = "<<Votes<<endl;
	return 0;
}