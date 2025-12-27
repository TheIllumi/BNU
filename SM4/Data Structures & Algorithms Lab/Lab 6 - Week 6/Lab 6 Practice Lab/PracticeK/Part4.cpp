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
        if (!head) {
            head = newNode;
            return;
        }
        Node* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newNode;
    }

    // Delete the last element
    void deleteLast() {
        if (!head) return;
        if (!head->next) {
            delete head;
            head = nullptr;
            return;
        }
        Node* temp = head;
        while (temp->next->next) {
            temp = temp->next;
        }
        delete temp->next;
        temp->next = nullptr;
    }

    // Double the list
    void doubleList() {
        if (!head) return;

        Node* temp = head;
        Node* tail = nullptr;

        // Find the last node
        while (temp->next) {
            temp = temp->next;
        }
        tail = temp; // Tail points to the last node

        // Copy original list and append to the end
        Node* curr = head;
        while (curr) {
            insertEnd(curr->data);
            curr = curr->next;
        }
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

    // Insert at the end
    list.insertEnd("TUV");
    list.insertEnd("QRS");

    cout << "Initial List: ";
    list.display();

    // Double the list
    list.doubleList();
    cout << "After doubling the list: ";
    list.display();

    return 0;
}
