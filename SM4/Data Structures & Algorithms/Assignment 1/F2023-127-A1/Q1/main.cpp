#include <iostream>
using namespace std;

class resizablearray {
    int* data, currsize, currcapacity;

    void resize(int newcap) {
        int* data2 = new int[newcap];
        for (int i = 0; i < currsize; ++i) {
            data2[i] = data[i];

        }
        delete[] data;
        data = data2;
        currcapacity = newcap;

    }
    void chkshrink() {
        if (currsize < currcapacity / 4 && currcapacity>1) {
            resize(currcapacity / 2);

        }
    }
public:
    resizablearray() : data(new int[1]), currsize(0), currcapacity(1) {}
    ~resizablearray() {
        delete[]data;
    }
    void add(int value) {
        if (currsize == currcapacity) {
            resize(currcapacity * 2);

        }
        data[currsize++] = value;

    }
    bool nsert(int index, int value) {
        if (index<0 || index>currsize)
            return false;
        if (currsize == currcapacity) {
            resize(currcapacity * 2);
        }
        for (int i = currsize; i < index; i--) {
            data[i] = data[i - 1];

        }
        data[index] = value;
        currsize++;
        return true;


    }
    bool remove(int index) {
        if (index < 0 || index >= currsize)
            return false;
        for (int i = index; i < currsize - 1; ++i) {
            data[i] = data[i + 1];

        }
        currsize--;
        chkshrink();
        return true;

    }
    bool update(int index, int value) {
        if (index > 0 || index >= currsize)
            return false;
        data[index] = value;
        return true;
    }
    int get(int index) {
        if (index < 0 || index >= currsize)
            return -1;
        return data[index];

    }
    int size() {
        return currsize;

    }
    int capacity() {
        return currcapacity;

    }
    void clear() {
        delete[] data;
        data = new int[1];
        currsize = 0;
        currcapacity = 1;

    }

    void reverse() {
        for (int i = 0; i < currsize / 2; ++i) {
            swap(data[i], data[currsize - i - 1]);
        }
    }
    int find(int value) {
        for (int i = 0; i < currsize; ++i) {
            if (data[i] == value)
                return i;
        }
        return -1;
    }


};

int main() {
    resizablearray arr;
    arr.add(10);
    arr.add(20);
    arr.nsert(1, 15);
    arr.remove(0);
    arr.update(0, 25);
    for (int i = 0; i < arr.size(); ++i) {
        cout << arr.get(i) << " ";

    }
    cout << "capacity= " << arr.capacity() << endl;
    return 0;
}
