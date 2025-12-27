#include <iostream>
using namespace std;

class ResizableArray
{
private:
    int size;
    int maxSize;
    int *array;

    void resize(int newSize)
    {
        int *newArray = new int[newSize];
        for (int i = 0; i < size; i++)
        {
            newArray[i] = array[i];
        }
        delete[] array;
        array = newArray;
        maxSize = newSize;
    }

public:
    ResizableArray()
    {
        size = 0;
        maxSize = 2;
        array = new int[maxSize];
    }

    ResizableArray(int size, int maxSize)
    {
        this->size = size;
        this->maxSize = maxSize;
        array = new int[maxSize];
    }

    void add(int value)
    {
        if (size >= maxSize)
        {
            resize(maxSize * 2);
        }
        array[size++] = value;
    }

    bool insert(int index, int value)
    {
        if (index < 0 || index > size)
        {
            cout << "Index out of bounds." << endl;
            return false;
        }

        if (size >= maxSize)
        {
            resize(maxSize * 2);
        }

        for (int i = size; i > index; i--)
        {
            array[i] = array[i - 1];
        }
        array[index] = value;
        size++;

        return true;
    }

    bool remove(int index)
    {
        if (index < 0 || index >= size)
        {
            cout << "Index out of bounds." << endl;
            return false;
        }

        for (int i = index; i < size - 1; i++)
        {
            array[i] = array[i + 1];
        }

        size--;

        if (size > 0 && size <= maxSize / 4)
        {
            resize(maxSize / 2);
        }

        return true;
    }

    bool update(int index, int value)
    {
        if (index < 0 || index >= size)
        {
            return false;
        }
        array[index] = value;
        return true;
    }

    int get(int index) const
    {
        if (index < 0 || index >= size)
        {
            cout << "Index out of bounds." << endl;
            return -1;
        }
        return array[index];
    }

    int getSize() const
    {
        return size;
    }

    int capacity() const
    {
        return maxSize;
    }

    void reverse()
    {
        for (int i = 0; i < size / 2; i++)
        {
            int temp = array[i];
            array[i] = array[size - i - 1];
            array[size - i - 1] = temp;
        }
    }

    int find(int value) const
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

    void print() const
    {
        for (int i = 0; i < size; i++)
        {
            cout << array[i] << " ";
        }
        cout << endl;
    }

    ~ResizableArray()
    {
        delete[] array;
    }
};

int main()
{
    ResizableArray arr;

    arr.add(1);
    arr.add(2);
    arr.add(3);
    arr.add(4);
    arr.add(5);
    arr.add(6);
    arr.add(7);
    arr.add(8);
    arr.add(9);

    cout << "--------------------------------------------------------------|" << endl;
    cout << "Array after adding elements: ";
    arr.print();
    cout << "--------------------------------------------------------------|" << endl;

    arr.insert(3, 50);
    cout << "After inserting 50 at index 3: ";
    arr.print();
    cout << "--------------------------------------------------------------|" << endl;

    arr.remove(4);
    cout << "After removing element at index 4: ";
    arr.print();
    cout << "--------------------------------------------------------------|" << endl;

    arr.insert(1, 15);
    cout << "After inserting 15 at index 1: ";
    arr.print();
    cout << "--------------------------------------------------------------|" << endl;

    return 0;
}