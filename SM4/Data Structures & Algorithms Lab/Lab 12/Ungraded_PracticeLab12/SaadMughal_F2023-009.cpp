#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    int data;
    Node* next;

    Node(int value) {
        data = value;
        next = nullptr;
    }
};

class LinkedList {
public:
    Node* head;

    LinkedList() {
        head = nullptr;
    }

    void insert(int value) {
        Node* newNode = new Node(value);
        if (head == nullptr)
            head = newNode;
        else {
            Node* temp = head;
            while (temp->next != nullptr)
                temp = temp->next;
            temp->next = newNode;
        }
    }

    // Q6: Count nodes
    int countNode(Node* current) {
		if (current == nullptr)
			return 0;
		else
			return 1 + countNode(current->next);
    }

    // Q7: Print list in reverse
    void printReverse(Node* current) {
		if (current == nullptr)
			return;
		printReverse(current->next);
		cout << current->data << " ";
    }

    // Q8: Find max value
    int maxNode(Node* current) {
        if (current == nullptr)
            return 0;
		int maxValue = current->data;
		int maxInRest = maxNode(current->next);
		if (maxInRest > maxValue)
			maxValue = maxInRest;
		return maxValue;
	}
    // Print the list normally
    void print() {
        cout << "Original List: ";
        Node* temp = head;
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};

// Q1: Ackermann’s Function
int ackermann(int m, int n) {
    if (m == 0)
        return n + 1;
    else if (n == 0)
        return ackermann(m - 1, 1);
    else
        return ackermann(m - 1, ackermann(m, n - 1));
    return 0;
}

// Q2: Count Characters
int countcharacters(string str, char ch, int pos) {
	if (pos >= str.length())
		return 0;
	if (str[pos] == ch)
		return 1 + countcharacters(str, ch, pos + 1);
	else
		return countcharacters(str, ch, pos + 1);
    return 0;
}

// Q3: Palindrome Detector
bool palindromedetector(string input, int len, int i) {
   /*if (i >= len / 2)
       return true;
   else if (input[i] != input[len - 1 - i])
       return false;*/
    if (input[i] != input[len -1 - i] && i < len / 2)
		return false;
	else if (i >= len / 2)
		return true;
	else
		return palindromedetector(input, len, i + 1);
	return false;
}

int main() {
    // Q1: Ackermann’s Function
    cout << "Ackermann: " << ackermann(3, 2) << endl;

    // Q2: Count Characters
    string str = "abcdddeffd";
    cout << "Count Characters: " << countcharacters(str, 'd', 0) << endl;

    // Q3: Palindrome Detector
    string input = "desserts I stressed";
    //string input = "able was I, ere I saw Elba";
    //string input = "a man, a plan, a canal, Panama";
    //string input = "kayak";
    int len = input.length();
    cout << "Palindrome Detector: " << (palindromedetector(input, len, 0) ? "Found" : "Not Found") << endl;

    LinkedList list;
    list.insert(10);
    list.insert(25);
    list.insert(7);
    list.insert(32);
    list.insert(18);

    list.print();

    // Q6: Count nodes
    cout << "Total nodes: " << list.countNode(list.head) << endl;

    // Q7: Print in reverse
    cout << "Reversed List: ";
    list.printReverse(list.head);
    cout << endl;

    // Q8: Find max value
    cout << "Maximum value: " << list.maxNode(list.head) << endl;

    return 0;
}