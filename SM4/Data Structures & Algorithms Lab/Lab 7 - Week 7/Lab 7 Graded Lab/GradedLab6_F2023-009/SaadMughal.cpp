#include <iostream>
#include <string>

using namespace std;

class Node {
public:
    int id;
    double gpa;
    string name;
    Node* next;
    Node* prev;

    Node(int id, double gpa, string name) {
        this->id = id;
        this->gpa = gpa;
        this->name = name;
        next = prev = nullptr;
    }
};

class DoublyLinkedList {
private:
    Node* head;
    Node* tail;

public:
    DoublyLinkedList() {
        head = tail = nullptr;
    }

    void insertStudent(int id, double gpa, string name) {
        Node* newNode = new Node(id, gpa, name);
        if (!head) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }


    // Function to find students with GPA above a threshold
    void findStudentsAboveGPA(double threshold) {
        Node* temp = head;
        int i = 0;
        while (temp)
        {
            if (temp->gpa >= threshold)
            {
                i++;
                cout << "ID: " << temp->id << ", Name: " << temp->name << ", GPA: " << temp->gpa << endl;
            }
            else
            {
                i = 0;
            }
            temp = temp->next;
        }
    }

    // Function to merge two doubly linked lists
    void mergeLists(DoublyLinkedList& otherList) {
        Node* list1 = head;
        Node* list2 = otherList.head;

        while (list1 && list2) {
            if (list1->id < list2->id) {
                Node* temp = list2->next;
                if (list1->prev) {
                    list1->prev->next = list2;
                }
                else {
                    head = list2;
                }
                list2->prev = list1->prev;
                list2->next = list1;
                list1->prev = list2;
                list2 = temp;
            }
            else {
                list1 = list1->next;
            }
        }
    }
    void display() 
    {
        Node* temp = head;
        while (temp) {
            cout << "ID: " << temp->id << ", Name: " << temp->name << ", GPA: " << temp->gpa << endl;
            temp = temp->next;
        }
    }
};

int main() {
    DoublyLinkedList list1, list2;

    // Adding students to first list
    list1.insertStudent(101, 3.8, "Alice");
    list1.insertStudent(102, 3.5, "Bob");
    list1.insertStudent(103, 3.3, "Johnny");
    list1.insertStudent(104, 2.5, "Courage");
    list1.insertStudent(105, 3.7, "Doug");

    // Adding students to second list
    list2.insertStudent(106, 3.9, "Charlie");
    list2.insertStudent(107, 3.6, "Dan");
    list2.insertStudent(108, 3.8, "Xander");
    list2.insertStudent(109, 3.9, "Ezikial");
    list2.insertStudent(110, 3.1, "Yorick");

    cout << "List 1 before merging:\n";
    list1.display();

    cout << "\nList 2 before merging:\n";
    list2.display();

    // Merging list2 into list1
    list1.mergeLists(list2);

    cout << "\nMerged List:\n";
    list1.display();

    // Test the function to find students above a given GPA threshold
    cout << "\nStudents with GPA >= 3.7:\n";
    list2.findStudentsAboveGPA(3.7);

    return 0;
}