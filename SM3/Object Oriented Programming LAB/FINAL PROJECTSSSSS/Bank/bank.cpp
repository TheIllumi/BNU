#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

// Function to check if a user exists during login
bool login(const string& username, const string& password) {
    ifstream file("users.txt");
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string storedUsername, storedPassword;
        ss >> storedUsername >> storedPassword;

        // Check if entered username and password match the stored ones
        if (storedUsername == username && storedPassword == password) {
            return true;
        }
    }
    return false;
}

// Function to create a new user (sign-up)
void signUp(const string& username, const string& password) {
    // Check if the user already exists (simple check, we can extend it)
    ifstream file("users.txt");
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string storedUsername, storedPassword;
        ss >> storedUsername >> storedPassword;

        if (storedUsername == username) {
            cout << "Username already taken. Try another one!" << endl;
            return;
        }
    }

    // Append the new user to the file
    ofstream outFile("users.txt", ios::app);
    outFile << username << " " << password << endl;
    cout << "Account successfully created!" << endl;
}

int main() {
    int choice;
    string username, password;

    while (true) {
        cout << "Welcome to the Bank Management System!" << endl;
        cout << "1. Sign Up" << endl;
        cout << "2. Login" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;
            signUp(username, password);
        }
        else if (choice == 2) {
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;

            if (login(username, password)) {
                cout << "Login successful! Welcome, " << username << "!" << endl;
            }
            else {
                cout << "Invalid username or password!" << endl;
            }
        }
        else if (choice == 3) {
            break;
        }
        else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
