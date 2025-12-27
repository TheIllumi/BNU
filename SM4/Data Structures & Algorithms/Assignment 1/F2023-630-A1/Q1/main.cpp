#include <iostream>
using namespace std;

class ResizeableArray
{
private:
    int size{ 0 };
    int index{ -1 };
    int capacity;
    int* array = nullptr;

public:
    ResizeableArray()
    {
        size = 0;
        capacity = 1;
        array = new int[capacity];
    }
    ResizeableArray(int c)
    {
        capacity = c;
        array = new int[capacity];
    }

    void Add(int value)
    {
        Constraints();
        array[size++] = value;
    }

    void Constraints()
    {
        if (size == capacity)
        {

            int* TempArr = new int[capacity * 2];
            for (int i = 0; i < size; ++i)
            {
                TempArr[i] = array[i];
            }
            delete[] array;
            array = TempArr;
            capacity = (capacity * 2);
        }
        else if (size < (capacity / 4) && capacity > 1)
        {
            int* TempArr = new int[capacity / 2];
            for (int i = 0; i < size; ++i)
            {
                TempArr[i] = array[i];
            }
            delete[] array;
            array = TempArr;
            capacity = (capacity / 2);
        }
    }

    int Get(int index)
    {
        if (index >= 0 && index < size)
        {
            return array[index];
        }
        else
        {
            cout << "Index out of bounds." << endl;
            return -1;
        }
    }

    void Remove(int i)
    {
        if (i >= 0 && i < size)
        {
            for (int j = i; j < size - 1; j++)
            {
                array[j] = array[j + 1];
            }
            size--;
        }
        else
        {
            cout << "Index out of bounds." << endl;
        }
        Constraints();
    }

    void clear()
    {
        delete[] array;
        array = new int[capacity];
        size = 0;
        capacity = 1;
        index = -1;
    }

    void reverse()
    {
        int* TempArr = new int[size];
        for (int i = 0; i < size; i++)
        {
            TempArr[i] = array[size - 1 - i];
        }
        delete[] array;
        array = TempArr;
    }

    int find(int value)
    {
        for (int i = 0; i < size; i++)
        {
            if (array[i] == value)
            {
                return i;
            }
        }
        return -1;
    }

    int GetSize() { return size; }
    int GetCapacity() { return capacity; }

    void DisplayArr()
    {
        cout << "---------------------------" << endl;
        for (int i = 0; i < size; i++)
        {
            cout << array[i] << " ";
        }
        cout << endl;
    }
    ~ResizeableArray()
    {
        delete[] array;
    }
};
int main()
{
    ResizeableArray Arr;
    Arr.Add(1);
    Arr.Add(2);
    Arr.Add(3);
    Arr.Add(4);
    Arr.Add(5);
    Arr.Add(6);

    cout << Arr.find(5) << endl;

    Arr.DisplayArr();

    Arr.reverse();

    Arr.DisplayArr();

    Arr.Remove(3);

    Arr.DisplayArr();

    return 0;
}