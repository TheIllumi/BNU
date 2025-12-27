#include "StringLinkedList.h"

// Constructor
StringLinkedList::StringLinkedList()
    : head(NULL) {
}

// Destructor
StringLinkedList::~StringLinkedList() {
    while (!empty()) removeFront();
}

// Check if the list is empty
bool StringLinkedList::empty() const {
    return head == NULL;
}

// Get front element
const string& StringLinkedList::front() const {
    return head->elem;
}

// Add an element to the front
void StringLinkedList::addFront(const string& e) {
    StringNode* v = new StringNode;
    v->elem = e;
    v->next = head;
    head = v;
}

// Remove front item
void StringLinkedList::removeFront() {
    StringNode* old = head;
    head = old->next;
    delete old;
}

// Display all elements
void StringLinkedList::display() const {
    StringNode* current = head;
    while (current != NULL) {
        cout << current->elem << " ";
        current = current->next;
    }
    cout << endl;
}

// Delete the last element
void StringLinkedList::removeLast() {
    if (empty()) return;

    if (head->next == NULL) { 
        delete head;
        head = NULL;
        return;
    }

    StringNode* current = head;
    while (current->next && current->next->next != NULL) {
        current = current->next;
    }

    delete current->next;
    current->next = NULL;
}

// Add an element at the end
void StringLinkedList::addBack(const string& e) {
    StringNode* newNode = new StringNode;
    newNode->elem = e;
    newNode->next = NULL;

    if (empty()) {
        head = newNode;
    }
    else {
        StringNode* current = head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

// Double the list
void StringLinkedList::doubleList() {
    if (empty()) return;

    StringNode* current = head;
    StringLinkedList tempList;

    while (current != NULL) {
        tempList.addBack(current->elem);
        current = current->next;
    }

    current = tempList.head;
    while (current != NULL) {
        addBack(current->elem);
        current = current->next;
    }
}

// Search the node
int StringLinkedList::search(const string& e) {
    StringNode* current = head;
    int count = 1;

    while (current != NULL) {
        if (current->elem == e) {
            cout << "Value Found at Index: " << count << endl;
            return count;
        }
        current = current->next;
        count++;
    }
    cout << "Value NOT Found: " << -1 << endl;
    return -1;
}

// Insert in the middle
void StringLinkedList::insertToClass(int index, const string& e) {
    StringNode* current = head;
    int count = 1;

    while (current != NULL) {
        if (count == index) {
            current = current->next;

            StringNode* newNode = new StringNode;
            newNode->elem = e;
            newNode->next = current;

            StringNode* temp = head;
            while (temp->next != current) {
                temp = temp->next;
            }
            temp->next = newNode;

            cout << "List after insertion: ";
            display();
        }
        current = current->next;
        count++;
    }
}

// Are two lists equal?
bool StringLinkedList::isEqual(StringLinkedList& other) {
    StringNode* current = head;
    StringNode* otherCurrent = other.head;

    while (current != NULL && otherCurrent != NULL) {
        if (current->elem != otherCurrent->elem) {
            cout << "Lists are NOT equal!" << endl;
            return false;
        }
        current = current->next;
        otherCurrent = otherCurrent->next;
    }

    cout << "Lists are equal!" << endl;
    return current == NULL && otherCurrent == NULL;
}