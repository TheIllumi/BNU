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

    // Insert at the end
    void insertEnd(string value) {
        Node* newNode = new Node(value);
        if (!head) { // If list is empty, new node becomes head
            head = newNode;
            return;
        }
        Node* temp = head;
        while (temp->next) { // Traverse to last node
            temp = temp->next;
        }
        temp->next = newNode;
    }

    // Delete the last element
    void deleteLast() {
        if (!head) return; // Empty list, nothing to delete
        if (!head->next) { // Only one node
            delete head;
            head = nullptr;
            return;
        }
        Node* temp = head;
        while (temp->next->next) { // Traverse to second last node
            temp = temp->next;
        }
        delete temp->next;
        temp->next = nullptr;
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

    cout << "Initial List: ";
    list.display();

    // Insert at the end
    list.insertEnd("TUV");
    list.insertEnd("QRS");

    cout << "After inserting at the end: ";
    list.display();

    return 0;
}
