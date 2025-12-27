#include <iostream>
#include <sstream>
using namespace std;

class Customer
{
private:
    int id{0};
    string name{""};
    int discount{0};

public:
    Customer() = default;

    Customer(int i, string n, int d) : id{i}, name{n}, discount{d} {}

    int getID()
    {
        return id;
    }

    string getName()
    {
        return name;
    }

    int getDiscount()
    {
        return discount;
    }

    void setDiscount(int dis)
    {
        discount = dis;
    }

    string toString()
    {
        stringstream ss;
        ss << name << "(" << id << ")" << "(" << discount << "%)";
        return ss.str();
    }
};

class Invoice
{
private:
    int id{0};
    Customer customer;
    double amount{0.0};

public:
    Invoice(int i, Customer c, double a) : id{i}, customer{c}, amount{a} {}

    int getID()
    {
        return id;
    }

    Customer getCustomer()
    {
        return customer;
    }

    void setCustomer(Customer c)
    {
        customer = c;
    }

    double getAmount()
    {
        return amount;
    }

    void setAmount(double a)
    {
        amount = a;
    }

    int getCustomerID()
    {
        return customer.getID();
    }

    string getCustomerName()
    {
        return customer.getName();
    }

    int getCustomerDiscount()
    {
        return customer.getDiscount();
    }

    double getAmountAfterDiscount()
    {
        return amount * (1 - customer.getDiscount() / 100.0);
    }

    string toString()
    {
        stringstream ss;
        ss << "Invoice[ID=" << id << ", Customer=" << customer.toString()
           << ", Amount=" << amount << "]";
        return ss.str();
    }
};

int main()
{
    Customer customer1(9, "Saad Mughal", 23);
    Invoice invoice1(88, customer1, 450.0);

    cout << "Invoice ID: " << invoice1.getID() << endl;
    cout << "Customer Name: " << invoice1.getCustomerName() << endl;
    cout << "Amount: " << invoice1.getAmount() << endl;
    cout << "Amount After Discount: " << invoice1.getAmountAfterDiscount() << endl;
    cout << "Invoice Details: " << invoice1.toString() << endl;

    return 0;
}