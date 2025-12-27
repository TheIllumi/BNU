#include <iostream>
#include <string>
using namespace std;

class Book {
    public:
    string Btitle;
    double* Bookrating;
    
    Book(string Btitle,double rating) //constructor
    {
    this->Btitle = Btitle;
    Bookrating = new double; //new memory allocation to cgpa ptr
    *Bookrating = rating; //dereferencing
    }
    
    //shallow copy
    Book(Book &obj) 
    {
    this->Btitle = obj.Btitle;
    this->Bookrating = obj.Bookrating;
    }
    
     //we can also create our own copy constructor
    Book(Book &obj, bool isDeepCopy) //default
    {
    this->Btitle  = obj.Btitle ;
    Bookrating = new double; 
    *Bookrating = *obj.Bookrating;
    }
    
    void getInfo(){
        cout<<"Title :" <<Btitle<<endl;
        cout<<"Rating :" <<*Bookrating<<endl;
    }
    ~Book() {
        delete Bookrating;
    }
};
int main(){
    Book b1("Harry Potter", 4.5);
    cout << "Original Book (b1):" << endl;
    b1.getInfo();
    
    Book b2(b1); //shallow copy
    cout << "\nShallow Copy (b2) created from b1:" << endl;
    b2.getInfo();
    
    // Modify rating in shallow copy (b2)
    *(b2.Bookrating) = 3.7;
    cout << "\nAfter modifying rating in shallow copy (b2):" << endl;
    cout << "Original Book (b1):" << endl;
    b1.getInfo();
    cout << "Shallow Copy (b2):" << endl;
    b2.getInfo();
    
    // Deep copy
    Book b3(b1, false);
    cout << "\nDeep Copy (b3) created from b1:" << endl;
    b3.getInfo();

    // Modify rating in deep copy (b3)
    *(b3.Bookrating) = 5.0;
    cout << "\nAfter modifying rating in deep copy (b3):" << endl;
    cout << "Original Book (b1):" << endl;
    b1.getInfo();
    cout << "Deep Copy (b3):" << endl;
    b3.getInfo();

    return 0;
}