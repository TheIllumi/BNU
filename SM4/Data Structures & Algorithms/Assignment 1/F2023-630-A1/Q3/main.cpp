#include <iostream>
using namespace std;

class SortedCatalog
{
private:
    int* list{ nullptr };
    int size{ 0 };
    int capacity{ 1 };

public:
    SortedCatalog()
    {
        list = new int[capacity];
    }
    SortedCatalog(int c)
    {
        capacity = c;
        list = new int[capacity];
    }

    void AddProduct(int sku)
    {
        if (size == capacity)
        {

            capacity++;
            int* TempArr = new int[capacity];
            for (int i = 0; i < size; ++i)
            {
                TempArr[i] = list[i];
            }
            delete[] list;
            list = TempArr;
        }
        list[size++] = sku;
        BubbleSort();
    }

    void BubbleSort()
    {
        int temp = 0;
        for (int i = 0; i < size - 1; i++)
        {
            for (int j = 0; j < size - 1; j++)
            {
                if (list[j] > list[j + 1])
                {
                    temp = list[j];
                    list[j] = list[j + 1];
                    list[j + 1] = temp;
                }
            }
        }
    }

    void PrintCatalog()
    {
        for (int i = 0; i < size; i++)
        {
            cout << list[i] << " ";
        }
        cout << endl;
    }

    int FindCatalog(int value)
    {
        int first = 0, last = size - 1, middle, position = -1;
        bool found = false;
        while (!found && first <= last)
        {
            middle = (first + last) / 2;
            if (list[middle] == value)
            {
                found = true;
                position = middle;
            }
            else if (list[middle] > value)
                last = middle - 1;
            else
                first = middle + 1;
        }
        return position;
    }
    ~SortedCatalog()
    {
        delete[] list;
    }
};

int main()
{
    SortedCatalog catalog(10);

    catalog.AddProduct(5);
    catalog.AddProduct(2);
    catalog.AddProduct(8);
    catalog.AddProduct(1);
    catalog.AddProduct(9);
    catalog.AddProduct(3);

    catalog.PrintCatalog();

    cout << "Finding 8: Index = " << catalog.FindCatalog(8) << endl;
    cout << "Finding 4: Index = " << catalog.FindCatalog(4) << endl;


    SortedCatalog catalog2(3);
    catalog2.AddProduct(10);
    catalog2.AddProduct(15);
    catalog2.AddProduct(5);
    catalog2.AddProduct(12);

    catalog2.PrintCatalog();
    cout << "Finding 12: Index = " << catalog2.FindCatalog(12) << endl;
    return 0;
}