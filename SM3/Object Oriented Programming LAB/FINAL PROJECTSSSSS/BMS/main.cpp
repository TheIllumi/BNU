#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <ctime>
#include <iomanip>
using namespace std;

class User {
private:
    static int userCount;
    int userID;
    string name;
    string CNIC;
    string address;
    int phone;
    int loginID;
    string password;
    double accountBalance;

    // Helper function to validate alphabetic input
    bool isValidName(const string &str) {
        for (char c : str) {
            if (!isalpha(c) && c != ' ') {
                return false;
            }
        }
        return true;
    }

    // Helper function to validate CNIC format
    bool isValidCNIC(const string &str) {
        if (str.length() > 15) return false;
        for (char c : str) {
            if (!isdigit(c) && c != '-') return false;
        }
        return true;
    }

    // Helper function to trim leading and trailing whitespaces
    string trim(const string &str) {
        size_t start = str.find_first_not_of(" \t");
        size_t end = str.find_last_not_of(" \t");
        return (start == string::npos || end == string::npos) ? "" : str.substr(start, end - start + 1);
    }

public:
    User() : userID(0), phone(0), loginID(0), accountBalance(0.0) {}

    void registerUser() {
        userID = ++userCount;

        cout << "\nEnter Name (alphabets only): ";
        cin.ignore();
        while (true) {
            getline(cin, name);
            if (isValidName(name)) break;
            cout << "Invalid name. Please enter alphabets only: ";
        }

        cout << "Enter CNIC (15 characters max, numbers and '-'): ";
        while (true) {
            cin >> CNIC;
            if (isValidCNIC(CNIC)) break;
            cout << "Invalid CNIC. Please use numbers and '-' only (max 15 characters): ";
        }

        cout << "Enter Address: ";
        cin.ignore();
        getline(cin, address);

        cout << "Enter Phone (numbers only): ";
        while (!(cin >> phone) || phone <= 0) {
            cout << "Invalid phone number. Please enter a valid number: ";
            cin.clear();
        }

        cout << "Enter Login ID (numbers only): ";
        while (!(cin >> loginID) || loginID <= 0) {
            cout << "Invalid Login ID. Please enter a valid number: ";
            cin.clear();
        }

        cout << "Enter Password: ";
        cin >> password;
        string confirmPassword;
        cout << "Confirm Password: ";
        cin >> confirmPassword;

        while (password != confirmPassword) {
            cout << "Passwords do not match. Enter Password again: ";
            cin >> password;
            cout << "Confirm Password: ";
            cin >> confirmPassword;
        }

        cout << "Enter Initial Account Balance: ";
        while (!(cin >> accountBalance) || accountBalance < 0) {
            cout << "Invalid balance. Please enter a valid balance: ";
            cin.clear();
        }

        ofstream outFile("users.txt", ios::app);
        if (outFile) {
            // Add column headers if file is empty
            if (isFileEmpty()) {
                outFile << "UserID|Name|Address|CNIC|Phone|LoginID|Password|AccountBalance\n";
            }

            // Write user details in a tabular format
            outFile << userID << "|"
                    << name << "|"
                    << address << "|"
                    << CNIC << "|"
                    << phone << "|"
                    << loginID << "|"
                    << password << "|"
                    << accountBalance << "\n";
            outFile.close();
            cout << "\nUser registered successfully! Your User ID is: " << userID << "\n";
        } else {
            cout << "\nError: Could not save user data.\n";
        }
    }

    bool isFileEmpty() {
        ifstream inFile("users.txt");
        return inFile.peek() == ifstream::traits_type::eof();
    }

    void loginUser() {
        int inputLoginID;
        string inputPassword;

        cout << "Enter Login ID: ";
        cin >> inputLoginID;

        cout << "Enter Password: ";
        cin >> inputPassword;

        ifstream inFile("users.txt");
        if (!inFile || isFileEmpty()) {
            cout << "No users registered yet.\n";
            return;
        }

        string line;
        bool found = false;

        // Read header line and find column indices
        getline(inFile, line);  // Skip the header row

        while (getline(inFile, line)) {
            stringstream ss(line);
            vector<string> columns;
            string value;

            while (getline(ss, value, '|')) {
                columns.push_back(trim(value));  // Split by delimiter and trim
            }

            if (columns.size() >= 7) {
                int storedLoginID = stoi(columns[5]);
                string storedPassword = columns[6];

                if (storedLoginID == inputLoginID && storedPassword == inputPassword) {
                    found = true;
                    break;
                }
            }
        }

        if (found) {
            cout << "Login successful!\n";
        } else {
            cout << "Invalid login ID or password. Please try again.\n";
        }
    }
};

int User::userCount = 0;

// AccountType Class
class AccountType {
protected:
    string typeName;
    double dailyWithdrawalLimit;

public:
    AccountType(string name, double limit) : typeName(name), dailyWithdrawalLimit(limit) {}

    virtual ~AccountType() {}
};

// Derived Account Types
class Bronze : public AccountType {
public:
    Bronze() : AccountType("Bronze", 100000) {}
};

class Gold : public AccountType {
public:
    Gold() : AccountType("Gold", 500000) {}
};

class Business : public AccountType {
public:
    Business() : AccountType("Business", 20000000) {}
};

int main() {
    User user;
    int choice;

    do {
        cout << "\n--- Banking Management System ---\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        while (!(cin >> choice)) {
            cout << "Invalid input. Please enter a valid choice: ";
            cin.clear();
        }

        switch (choice) {
            case 1:
                user.registerUser();
                break;
            case 2:
                user.loginUser();
                break;
            case 3:
                cout << "\nThank you for using the Banking Management System!\n";
                break;
            default:
                cout << "\nInvalid choice. Please try again.\n";
        }
    } while (choice != 3);

    return 0;
}