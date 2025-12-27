#pragma once
#include <iostream>
#include <string>
using namespace std;

class Book
{
private:
	string title;
	string author;
	double price;
	const int bookID;
	static int bookcount;

public:
	// Constructor with default values
	Book(const string& t = "Untitled", const string& a = "Unknown", double p = 0.0);

	// Copy Constructor
	Book(const Book& other); 

	// Overloaded Assignment Operator
	Book& operator=(const Book& other);			

	// Overloaded + Operator (Create a Book Bundle)
	Book operator+(const Book& other) const;		

	// Overloaded == Operator (Compare Books)
	bool operator==(const Book& other) const;		

	// Getter Functions
	string getTitle() const;				
	string getAuthor() const;				
	int getbookID() const;

	// Overloaded << Operator (Friend Function)
	friend ostream& operator<<(ostream& out, const Book& b);
};
