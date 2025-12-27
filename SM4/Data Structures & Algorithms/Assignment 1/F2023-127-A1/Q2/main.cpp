#include<iostream>
using namespace std;

class custlist {
    int* custs;
    int sz, cap;
    void resize(int newcap) {
        int* tmp = new int[newcap];
        for (int i = 0;i < sz;i++) tmp[i] = custs[i];
        delete[] custs;
        custs = tmp;
        cap = newcap;


    }

public:
    custlist() :sz(0), cap(1) { custs = new int[cap]; }
    ~custlist() { delete[] custs; }

    void add(int id) {
        if (sz == cap) resize(cap * 2);
        custs[sz++] = id;
    }

    int find(int id) {
        for (int i = 0;i < sz;i++) if (custs[i] == id) return i;
        return -1;
    }

    bool rem(int id) {
        int idx = find(id);
        if (idx != -1) {
            for (int i = idx;i < sz - 1;i++) custs[i] = custs[i + 1];
            sz--;
            return true;
        }
        return false;
    }

    void print() {
        for (int i = 0;i < sz;i++) cout << custs[i] << " ";
        cout << endl;
    }
};

int main() {
    custlist lst;
    lst.add(101);
    lst.add(202);
    lst.add(303);

    cout << "list: ";lst.print();
    int sid = 202;
    cout << "find id " << sid << ": " << lst.find(sid) << endl;

    int rid = 101;
    if (lst.rem(rid)) cout << "id " << rid << " gone." << endl;
    else cout << "id " << rid << " not found." << endl;
    cout << "new list: ";lst.print();
    return 0;
}