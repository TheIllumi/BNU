#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

typedef char Elem; // list element type
class DNode
{ // doubly linked list node
private:
    Elem elem;                // node element value
    DNode *prev;              // previous node in list
    DNode *next;              // next node in list
    friend class DLinkedList; // allow DLinkedList access
};

class DLinkedList
{ // doubly linked list
public:
    DLinkedList();                                      // constructor
    ~DLinkedList();                                     // destructor
    bool empty() const;                                 // is list empty?
    const Elem &front() const;                          // get front element
    const Elem &back() const;                           // get back element
    void addFront(const Elem &e);                       // add to front of list
    void addBack(const Elem &e);                        // add to back of list
    void removeFront();                                 // remove from front
    void removeBack();                                  // remove from back
    void display();                                     // display the list
    bool findSequence(const char *seq);                 // find a sequence in the list
    void DLinkedList::insertAt(int pos, const Elem &e); // insert at a position
private:                                                // local type definitions
    DNode *header;                                      // list sentinels
    DNode *trailer;

protected:                             // local utilities
    void add(DNode *v, const Elem &e); // insert new node before v
    void remove(DNode *v);             // remove node v
};

DLinkedList::DLinkedList()
{                       // constructor
    header = new DNode; // create sentinels
    trailer = new DNode;
    header->next = trailer; // have them point to each other
    trailer->prev = header;
}

bool DLinkedList::empty() const // is list empty?
{
    return (header->next == trailer);
}

const Elem &DLinkedList::front() const // get front element
{
    return header->next->elem;
}

const Elem &DLinkedList::back() const // get back element
{
    return trailer->prev->elem;
}
void DLinkedList::remove(DNode *v)
{                       // remove node v
    DNode *u = v->prev; // predecessor
    DNode *w = v->next; // successor
    u->next = w;        // unlink v from list
    w->prev = u;
    delete v;
}

void DLinkedList::removeFront() // remove from font
{
    remove(header->next);
}

void DLinkedList::removeBack() // remove from back
{
    remove(trailer->prev);
}

// insert new node before v
void DLinkedList::add(DNode *v, const Elem &e)
{
    DNode *u = new DNode;
    u->elem = e;       // create a new node for e
    u->next = v;       // link u in between v
    u->prev = v->prev; // ...and v->prev
    v->prev->next = u;
    v->prev = u;
}

void DLinkedList::addFront(const Elem &e) // add to front of list
{
    add(header->next, e);
}

DLinkedList::~DLinkedList()
{ // destructor
    while (!empty())
        removeFront(); // remove all but sentinels
    delete header;     // remove the sentinels
    delete trailer;
}

void DLinkedList::addBack(const Elem &e) // add to back of list
{
    add(trailer, e);
}

void DLinkedList::display()
{
    DNode *temp = header->next;
    while (temp != trailer)
    {
        cout << temp->elem << " ";
        temp = temp->next;
    }
    cout << endl;
}

/*bool DLinkedList::findSequence(const char *seq)
{
    DNode *temp = header->next;
    int i = 0;
    while (temp != trailer)
    {
        if (temp->elem == seq[i])
        {
            i++;
            if (seq[i] == '\0')
            {
                return true;
            }
        }
        else
        {
            i = 0;
        }
        temp = temp->next;
    }

    DNode *temp1 = trailer->prev;
    i = 0;
    while (temp1 != header)
    {
        if (temp1->elem == seq[i])
        {
            i++;
            if (seq[i] == '\0')
            {
                return true;
            }
        }
        else
        {
            i = 0;
        }
        temp1 = temp1->prev;
    }

    return false;
}*/

bool DLinkedList::findSequence(const char *seq)
{
    string listContent = "";

    // Traverse the list and build a string
    for (DNode *temp = header->next; temp != trailer; temp = temp->next)
    {
        listContent += temp->elem;
    }

    // Check if sequence exists in the string
    if (listContent.find(seq) != string::npos)
    {
        return true;
    }

    // Reverse the string to check in backward direction
    reverse(listContent.begin(), listContent.end());

    if (listContent.find(seq) != string::npos)
    {
        return true;
    }

    return false;
}

void DLinkedList::insertAt(int pos, const Elem &e)
{
    DNode *temp = header->next; // Start from first element
    int count = 0;

    // Traverse to the position (but not beyond the last element)
    while (temp != trailer && count < pos)
    {
        temp = temp->next;
        count++;
    }

    // If position is valid, insert before `temp`
    if (temp != trailer)
    {
        add(temp, e); // Uses `add()` to insert before `temp`
    }
    else
    {
        cout << "Invalid position!" << endl;
    }
}

int main()
{
    DLinkedList L1;
    L1.addBack('L');
    L1.addBack('A');
    L1.addBack('S');
    L1.addBack('T');
    L1.addBack('M');
    L1.addBack('A');
    L1.addBack('X');
    L1.addBack('E');

    L1.display();

    if (L1.findSequence("LAST"))
    {
        cout << "LAST found" << endl;
    }
    else
    {
        cout << "LAST not found" << endl;
    }

    if (L1.findSequence("EXAM"))
    {
        cout << "EXAM found" << endl;
    }
    else
    {
        cout << "EXAM not found" << endl;
    }

    if (L1.findSequence("MAX"))
    {
        cout << "MAX found" << endl;
    }
    else
    {
        cout << "MAX not found" << endl;
    }

    if (L1.findSequence("MAZE"))
    {
        cout << "MAZE found" << endl;
    }
    else
    {
        cout << "MAZE not found" << endl;
    }

    return 0;
}