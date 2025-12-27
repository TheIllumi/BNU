#include <iostream>
using namespace std;

class SortedCatalogue
{
private:
    int *sku;
    int count;
    int maxSize;

public:
    SortedCatalogue()
    {
        maxSize = 10000;
        sku = new int[maxSize];
        count = 0;
    }

    void addProduct(int newSku)
    {
        if (count >= maxSize)
        {
            cout << "Catalogue is full" << endl;
            return;
        }

        int i;
        for (i = count - 1; i >= 0 && sku[i] > newSku; i--)
        {
            sku[i + 1] = sku[i];
        }

        sku[i + 1] = newSku;
        count++;
    }

    int findProduct(int sku) const
    {
        int first, last, mid;

        first = 0;
        last = count - 1;

        while (first <= last)
        {
            mid = (first + last) / 2;

            if (this->sku[mid] == sku)
            {
                return mid;
            }
            else if (this->sku[mid] < sku)
            {
                first = mid + 1;
            }
            else
            {
                last = mid - 1;
            }
        }

        return -1;
    }

    void printCatalog() const
    {
        if (count == 0)
        {
            cout << "Catalogue is empty" << endl;
            return;
        }

        for (int i = 0; i < count; i++)
        {
            cout << sku[i] << " ";
        }
        cout << endl;
    }

    ~SortedCatalogue()
    {
        delete[] sku;
    }
};

int main()
{
    cout << "-----------------------------------------|" << endl;

    SortedCatalogue catalogue;

    catalogue.addProduct(52);
    catalogue.addProduct(10);
    catalogue.addProduct(150);
    catalogue.addProduct(103);

    cout << "Sorted Catalogue: ";
    catalogue.printCatalog();

    cout << "-----------------------------------------|" << endl;

    cout << "Index of 150: " << catalogue.findProduct(150) << endl;
    cout << "Index of 10: " << catalogue.findProduct(10) << endl;

    cout << "-----------------------------------------|" << endl;

    cout << "Adding more products..." << endl;
    catalogue.addProduct(10);
    catalogue.addProduct(1);
    catalogue.addProduct(47);

    cout << "Updated Catalogue: ";
    catalogue.printCatalog();

    cout << "-----------------------------------------|" << endl;

    return 0;
}