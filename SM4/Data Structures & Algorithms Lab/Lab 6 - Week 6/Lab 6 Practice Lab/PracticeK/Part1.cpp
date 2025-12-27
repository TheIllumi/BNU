#include <iostream>
using namespace std;

// Node structure
struct Node {
    string data;
    Node* next;
    Node(string val) : data(val), next(nullptr) {}
};

// Linked List class
class LinkedList {
private:
    Node* head;
public:
    LinkedList() : head(nullptr) {}

    // Insert at the front
    void insertFront(string value) {
        Node* newNode = new Node(value);
        newNode->next = head;
        head = newNode;
    }

    // Display the list
    void display() {
        Node* temp = head;
        while (temp) {
            cout << temp->data;
            if (temp->next) cout << " -> ";
            temp = temp->next;
        }
        cout << endl;
    }
};

// Main function to test the linked list
int main() {
    LinkedList list;

    // Insert elements at the front
    list.insertFront("ABC");
    list.insertFront("XYZ");
    list.insertFront("LMN");

    // Display the list
    cout << "Current Linked List: ";
    list.display();

    return 0;
}

