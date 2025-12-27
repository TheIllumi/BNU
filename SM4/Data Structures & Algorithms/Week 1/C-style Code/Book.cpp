#include "Book.h"
#include <cstring> 
#include <iostream>

int Book::bookcount = 1;  // Initialize static variable

// Constructor
Book::Book(const char* t, const char* a, double p) : bookID(bookcount++)    
{
    title = new char[strlen(t) + 1];                                        
    strcpy_s(title, strlen(t) + 1, t);                                      

    author = new char[strlen(a) + 1];
    strcpy_s(author, strlen(a) + 1, a);

    price = p;
}

// Copy Constructor (Deep Copy)
Book::Book(const Book& other) : bookID(bookcount++) 
{
    title = new char[strlen(other.title) + 1];
    strcpy_s(title, strlen(other.title) + 1, other.title);                  

    author = new char[strlen(other.author) + 1];
    strcpy_s(author, strlen(other.author) + 1, other.author);

    price = other.price;
}

// Assignment Operator (Deep Copy)
Book& Book::operator=(const Book& other) 
{
    if (this != &other)                                                 
    {
        delete[] title;                                                  
        delete[] author;                                                

        title = new char[strlen(other.title) + 1];
        strcpy_s(title, strlen(other.title) + 1, other.title);

        author = new char[strlen(other.author) + 1];
        strcpy_s(author, strlen(other.author) + 1, other.author);

        price = other.price;
    }
    return *this;                                         
}

// Overloaded + Operator: Create a Book Bundle
Book Book::operator+(const Book& other) const                               
{                                                                           
    char* bundleTitle = new char[strlen(title) + strlen(other.title) + 4];
    strcpy_s(bundleTitle, strlen(title) + strlen(other.title) + 4, title);                             
    strcat_s(bundleTitle, strlen(title) + strlen(other.title) + 4, " & ");
    strcat_s(bundleTitle, strlen(title) + strlen(other.title) + 4, other.title);
     
    char* bundleAuthor = new char[strlen(author) + strlen(other.author) + 4];
    strcpy_s(bundleAuthor, strlen(author) + strlen(other.author) + 4, author);                             
    strcat_s(bundleAuthor, strlen(author) + strlen(other.author) + 4, " & ");
    strcat_s(bundleAuthor, strlen(author) + strlen(other.author) + 4, other.author);

    Book newBook(bundleTitle, bundleAuthor, price + other.price);

    delete[] bundleTitle;
    delete[] bundleAuthor;

    return newBook;                 
}

// Overloaded == Operator (Compare Books)
bool Book::operator==(const Book& other) const 
{
    return (strcmp(title, other.title) == 0) && (strcmp(author, other.author) == 0) && (price == other.price);
}

// Overloaded << Operator (Formatted Output) by making a friend function
ostream& operator<<(ostream& out, const Book& b)        
{                                                          
    out << "Book ID: " << b.bookID << "\nTitle: " << b.title << "\nAuthor: " << b.author << "\nPrice: $" << b.price << "\n";
    return out;
}

// Getters
const char* Book::getTitle() const { return title; }
const char* Book::getAuthor() const { return author; }
int Book::getID() const { return bookID; }

// Destructor
Book::~Book() 
{
    delete[] title; delete[] author;
}