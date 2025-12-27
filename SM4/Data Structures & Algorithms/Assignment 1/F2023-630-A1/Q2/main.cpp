#include <iostream>
using namespace std;

class CustomerList
{
private:
    int* Customer_id;
    int size{ 0 };
    int capacity;

public:
    CustomerList()
    {
        capacity = 1;
        Customer_id = new int[capacity];
    }

    CustomerList(int c)
    {
        capacity = c;
        Customer_id = new int[capacity];
    }

    void AddCustomer(int customerid)
    {
        if (size == capacity)
        {

            capacity++;
            int* TempArr = new int[capacity];
            for (int i = 0; i < size; ++i)
            {
                TempArr[i] = Customer_id[i];
            }
            delete[] Customer_id;
            Customer_id = TempArr;
        }
        Customer_id[size++] = customerid;
    }

    int FindCustomer(int customerid)
    {
        for (int i = 0; i < size; i++)
        {
            if (Customer_id[i] == customerid)
            {
                return i;
            }
        }
        return -1;
    }

    bool RemoveCustomer(int customerid)
    {
        int i = FindCustomer(customerid);
        if (i >= 0 && i < size)
        {
            for (int j = i; j < size - 1; j++)
            {
                Customer_id[j] = Customer_id[j + 1];
            }
            size--;
            return true;
        }
        else
        {
            return false;
        }
    }

    void PrintList()
    {
        cout << "---------------------------" << endl;
        for (int i = 0; i < size; i++)
        {
            cout << Customer_id[i] << " ";
        }
        cout << endl;
    }
};

int main()
{

    CustomerList customerList;

    customerList.AddCustomer(1);
    customerList.AddCustomer(2);
    customerList.AddCustomer(3);
    customerList.AddCustomer(4);
    customerList.AddCustomer(5);
    customerList.AddCustomer(6);

    customerList.PrintList();

    cout << "Finding Customer 3: Index = " << customerList.FindCustomer(3) << endl;
    cout << "Finding Customer 7: Index = " << customerList.FindCustomer(7) << endl;

    if (customerList.RemoveCustomer(3))
    {
        cout << "Customer 3 removed successfully." << endl;
    }
    else
    {
        cout << "Customer 3 not found." << endl;
    }

    customerList.PrintList();

    if (customerList.RemoveCustomer(7))
    {
        cout << "Customer 7 removed successfully." << endl;
    }
    else
    {
        cout << "Customer 7 not found." << endl;
    }
    customerList.PrintList();

    return 0;
}