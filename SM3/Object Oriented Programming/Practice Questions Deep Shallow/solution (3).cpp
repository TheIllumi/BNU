#include <iostream>
#include <cstring>
using namespace std;

class Product {
private:
    string productName;  
    double* productPrice;  

public:
    
    Product(string name, double price) {
        productName = name;
        productPrice = new double(price);  
    }

   
    Product(const Product& other) {
        productName = other.productName;
        productPrice = new double(*other.productPrice);  
    }

    
    void assign(const Product& other) {
        productName = other.productName;  
        delete productPrice;  
        productPrice = new double(*other.productPrice);  
    }

    
    void updatePrice(double newPrice) {
        *productPrice = newPrice;
    }

    
    void displayProductDetails() const {
        cout << "Product Name: " << productName << endl;
        cout << "Product Price: $" << *productPrice << endl;
    }

   
    ~Product() {
        delete productPrice;  
    }
};

int main() {
   
    Product prod1("Laptop", 999.99);
    prod1.displayProductDetails();

    Product prod2("Phone", 599.99);
    prod2.displayProductDetails();
    
    prod2.assign(prod1);
    cout << "\nAfter Assigning prod1 to prod2:\n";
    prod2.displayProductDetails();

    
    prod2.updatePrice(1099.99);
    cout << "\nAfter Updating prod2 Price:\n";
    prod2.displayProductDetails();

    return 0;
}
