#pragma once
#include <iostream>
using namespace std;
class Book
{
private:
    static int bookcount;  
    const int bookID;   
    char* title;
    char* author;
    double price;

public:
    // Constructor with default values
    Book(const char* t = "Untitled", const char* a = "Unknown", double p = 0.0);    

    // Copy Constructor (Deep Copy)
    Book(const Book& other);                

    // Assignment Operator (Deep Copy)
    Book& operator=(const Book& other); 
    
    // Overloaded + Operator (Creates Book Bundle)
    Book operator+(const Book& other) const;   

    // Overloaded == Operator (Comparison)
    bool operator==(const Book& other) const;   

    // Overloaded << Operator (Formatted Output)
    friend ostream& operator<<(ostream& out, const Book& b);     

    // Destructor
    ~Book();    

    //Getter functions
    const char* getTitle() const;       
    const char* getAuthor() const;      
    int getID() const;

};

