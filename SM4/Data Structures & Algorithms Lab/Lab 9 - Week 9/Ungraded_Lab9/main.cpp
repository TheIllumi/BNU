#include <iostream>
using namespace std;

// Define a custom Stack class for integers
class Stack {
private:
    int arr[100];   // Array to store stack elements (fixed size: 100)
    int top;        // Index of the top element in the stack

public:
    // Constructor to initialize the stack
    Stack() {
        top = -1; // When stack is empty, top is -1
    }

    // Push a new element onto the stack
    void push(int x) {
        if (top >= 99) { // Stack overflow check (max index is 99)
            cout << "Stack Overflow! Cannot push " << x << endl;
            return;
        }
        top++;           // Move top to the next index
        arr[top] = x;    // Insert the value at the top
    }

    // Pop (remove and return) the top element from the stack
    int pop() {
        if (top == -1) { // Stack underflow check (nothing to pop)
            cout << "Stack Underflow! Returning 0 by default." << endl;
            return 0;
        }
        int value = arr[top]; // Get the top element
        top--;                // Decrease the top index
        return value;         // Return the removed element
    }

    // Check if the stack is empty
    bool isEmpty() {
        return top == -1; // If top is -1, stack has no elements
    }

    // Optional: Peek at the top element without removing it
    int peek() {
        if (top == -1) {
            cout << "Stack is empty!" << endl;
            return 0;
        }
        return arr[top];
    }
};

int power(int base, int exp) {
    int res = 1;
    for (int i = 0; i < exp; i++) res *= base;
    return res;
}

int main() {
    Stack s;
    int n;
    cout << "Enter number of tokens in expression: ";
    cin >> n;

    cout << "Now enter tokens one by one (integers or operators like + - * / $):\n";

    for (int i = 0; i < n; i++) {
        string token;
        cin >> token;

        if (isdigit(token[0])) {
            // Convert to int and push
            int num = 0;
            for (char c : token) {
                num = num * 10 + (c - '0');
            }
            s.push(num);
        }
        else {
            // It's an operator
            int op2 = s.pop();
            int op1 = s.pop();
            int res = 0;
            char op = token[0];

            if (op == '+') res = op1 + op2;
            else if (op == '-') res = op1 - op2;
            else if (op == '*') res = op1 * op2;
            else if (op == '/') res = op1 / op2;
            else if (op == '$') res = power(op1, op2);

            s.push(res);
        }
    }

    cout << "Result: " << s.pop() << endl;
    return 0;
}
