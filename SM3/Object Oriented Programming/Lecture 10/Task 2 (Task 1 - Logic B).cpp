#include <iostream>
#include <string>
using namespace std;

class Book {
public:
    string Btitle;
    double* Bookrating;

    // Constructor to initialize Book
    Book(string Btitle, double rating) {
        this->Btitle = Btitle;
        Bookrating = new double;    
        *Bookrating = rating;       
    }

    // Constructor to handle both shallow and deep copies using deepCopyFlag
    Book(Book &obj, bool deepCopyFlag) {
        this->Btitle = obj.Btitle; 

        if (deepCopyFlag == true) 
        {  
            Bookrating = new double;  
            *Bookrating = *(obj.Bookrating);  
        } 
        else 
        {  // If false, perform a shallow copy
            Bookrating = obj.Bookrating;  
        }
    }

    void getInfo() {
        cout << "Title: " << Btitle << endl;
        cout << "Rating: " << *Bookrating << endl;
    }

    ~Book() {
        delete Bookrating;
    }
};

int main() {
    Book b1("Harry Potter", 4.5);

    Book b2(b1, true); // Deep copy

    Book b3(b1, false); // Shallow copy

    // Modify the rating of b2 (deep copy)
    *(b2.Bookrating) = 3.7;
    cout << "Book 1 (Original):" << endl;
    b1.getInfo();
    cout << "Book 2 (Deep Copy):" << endl;
    b2.getInfo();
    
    // Modify the rating of b3 (shallow copy)
    *(b3.Bookrating) = 2.8;
    cout << "\nAfter modifying the shallow copy (b3):" << endl;
    cout << "Book 1 (Original):" << endl;
    b1.getInfo();
    cout << "Book 3 (Shallow Copy):" << endl;
    b3.getInfo();

    return 0;
}