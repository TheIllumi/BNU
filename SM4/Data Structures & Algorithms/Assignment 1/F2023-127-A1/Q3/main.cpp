#include<iostream>
using namespace std;
class sortedcatalog {
private:
    int* skus;
    int sz, cap;
    void resize(int newcap) {
        int* tmp = new int[newcap];
        for (int i = 0;i < sz;i++) tmp[i] = skus[i];
        delete[] skus;
        skus = tmp;
        cap = newcap;
    }
    int binarysearch(int sku) {
        int left = 0, right = sz - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (skus[mid] == sku) return mid;
            else if (skus[mid] < sku) left = mid + 1;
            else right = mid - 1;
        }
        return -1;
    }

public:
    sortedcatalog() :sz(0), cap(1) { skus = new int[cap]; }
    ~sortedcatalog() { delete[] skus; }

    void addproduct(int sku) {
        if (sz == cap) resize(cap * 2);
        int i = sz - 1;
        while (i >= 0 && skus[i] > sku) {
            skus[i + 1] = skus[i];
            i--;
        }
        skus[i + 1] = sku;
        sz++;
    }
    int findproduct(int sku) {
        return binarysearch(sku);
    }
    void printcatalog() {
        for (int i = 0;i < sz;i++) cout << skus[i] << " ";
        cout << endl;
    }
};

int main() {
    sortedcatalog catalog;
    catalog.addproduct(300);
    catalog.addproduct(100);
    catalog.addproduct(200);

    cout << "catalog: "; catalog.printcatalog();

    int sku = 200;
    cout << "find sku " << sku << ": " << catalog.findproduct(sku) << endl;
    return 0;
}