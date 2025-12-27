#include <iostream>
#include "book.h"
using namespace std;

int main() {
    // Creating book objects
    Book book1("C++ Primer", "Lippman", 45.99);
    Book book2("Effective C++", "Scott Meyers", 39.99);

    cout << "Book 1:\n" << book1;
    cout << "\nBook 2:\n" << book2;

    // Copy Constructor Test
    Book book3 = book1;
    cout << "\nCopied Book:\n" << book3;

    // Assignment Operator Test
    book2 = book1;
    cout << "\nAfter Assignment (book2 = book1):\n" << book2;

    // Comparison Operator Test
    if (book1 == book3) {
        cout << "\nBook 1 and Book 3 are identical!\n";
    }
    else {
        cout << "\nBook 1 and Book 3 are different!\n";
    }

    // Book Bundle (Overloaded + Operator)
    Book bundle = book1 + book2;
    cout << "\nBook Bundle:\n" << bundle;

    return 0;
}