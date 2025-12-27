#include "book.h"
#include<iostream>
using namespace std;

int Book::bookcount = 1;  // Initialize static counter

// Constructor with default values
Book::Book(const string& t, const string& a, double p) : bookID(bookcount++), title(t), author(a), price(p) {}

// Copy Constructor
Book::Book(const Book& other) : bookID(bookcount++), title(other.title), author(other.author), price(other.price) {}

// Overloaded Assignment Operator
Book& Book::operator=(const Book& other) 
{
    if (this != &other) 
    {  // Self-assignment check
        title = other.title;
        author = other.author;
        price = other.price;
    }
    return *this;
}

// Overloaded + Operator (Create a Book Bundle)
Book Book::operator+(const Book& other) const 
{
    return Book(title + " & " + other.title, author + " & " + other.author, price + other.price);
}

// Overloaded == Operator (Compare Books)
bool Book::operator==(const Book& other) const 
{
    return (title == other.title) && (author == other.author) && (price == other.price);
}

// Getter Functions
string Book::getTitle() const { return title; }
string Book::getAuthor() const { return author; }
int Book::getbookID() const { return bookID; }

// Overloaded << Operator (Friend Function)
ostream& operator<<(ostream& out, const Book& b) 
{
    out << "Book ID: " << b.bookID << "\nTitle: " << b.title << "\nAuthor: " << b.author << "\nPrice: $" << b.price << "\n";
    return out;
}
