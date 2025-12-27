#include <iostream>
using namespace std;

class CustomerList
{
private:
    int* customers;
    int count;
    int maxSize;

public:
    CustomerList()
    {
        customers = new int[maxSize];
        count = 0;
        maxSize = 10000;
    }

    void addCustomer(int customerId)
    {
        if (count < maxSize)
        {
            customers[count] = customerId;
            count++;
        }
        else
        {
            cout << "List is full!\n"
                << endl;
        }
    }

    int findCustomer(int customerId) const
    {
        for (int i = 0; i < count; i++)
        {
            if (customers[i] == customerId)
            {
                return i;
            }
        }
        return -1;
    }

    bool removeCustomer(int customerId)
    {
        int index = findCustomer(customerId);

        if (index == -1)
        {
            return false;
        }

        for (int i = index; i < count - 1; i++)
        {
            customers[i] = customers[i + 1];
        }

        count--;
        return true;
    }

    void printList() const
    {
        if (count == 0)
        {
            cout << "Customer list is empty.\n";
            return;
        }

        for (int i = 0; i < count; i++)
        {
            cout << customers[i] << " ";
        }
        cout << endl;
    }

    ~CustomerList()
    {
        delete[] customers;
    }
};

int main()
{
    cout << "-----------------------------------------|" << endl;

    CustomerList list;
    list.addCustomer(1);
    list.addCustomer(2);
    list.addCustomer(3);
    list.addCustomer(4);
    list.addCustomer(5);
    list.addCustomer(6);
    list.addCustomer(7);
    list.addCustomer(8);
    list.addCustomer(9);

    cout << "Initial list: ";
    list.printList();
    cout << "-----------------------------------------|" << endl;

    cout << "Customer 1 is at index: " << list.findCustomer(1) << endl;
    cout << "Customer 2 is at index: " << list.findCustomer(2) << endl;

    if (list.removeCustomer(8))
    {
        cout << "Customer 8 removed successfully." << endl;
    }
    else
    {
        cout << "Customer 8 not found." << endl;
    }

    cout << "-----------------------------------------|" << endl;

    cout << "Updated list: ";
    list.printList();
    cout << "-----------------------------------------|" << endl;

    bool removed = list.removeCustomer(5);
    cout << "Removing Customer 5: " << removed << endl;

    if (removed)
    {
        cout << "Customer 5 removed successfully." << endl;
    }
    else
    {
        cout << "Customer 5 not found." << endl;
    }

    cout << "-----------------------------------------|" << endl;

    cout << "Updated list: ";
    list.printList();

    cout << "-----------------------------------------|" << endl;
    return 0;
}