#include <iostream>
#include "Book.h"
using namespace std;

int main() {
    // Create books
    Book book1("C++ Primer", "Lippman", 45.99);
    Book book2("Effective C++", "Scott Meyers", 39.99);
    Book book3("Design Patterns", "Gamma et al.", 50.00);

    // Display books
    cout << "Book Collection:\n";
    cout << book1 << "\n" << book2 << "\n" << book3 << "\n";

    // Book duplication
    Book book4 = book1; // Copy Constructor
    cout << "\nDuplicated Book:\n" << book4;

    // Book Comparison
    if (book1 == book4) {
        cout << "\nBooks are identical!\n";
    }
    else {
        cout << "\nBooks are different!\n";
    }

    // Create a book bundle
    Book bundle = book1 + book2;
    cout << "\nBook Bundle:\n" << bundle;

    return 0;
}
