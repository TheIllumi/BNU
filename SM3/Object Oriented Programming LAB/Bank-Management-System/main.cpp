//main.cpp
#include <iostream>
#include "bank.h"
#include "database.h"
#include "User.h"
#include "UserClient.h"

using namespace std;

int main() {
    int choice;
    User user;
    UserClient client;

    // Initialize database connection
    initializeDatabase();

    while (true) {
        cout << "Welcome to the Bank Management System!" << endl;
        cout << "1. Sign Up" << endl;
        cout << "2. Login" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            user.signUp();
        }
        else if (choice == 2) {
            if (user.login()) {
                client.setUserID(user.getUserID());  // Set the userID in UserClient

                int userChoice;
                while (true) {
                    cout << "\nBanking Menu:" << endl;
                    cout << "1. Deposit Money" << endl;
                    cout << "2. Withdraw Money" << endl;
                    cout << "3. Transfer Funds" << endl;
                    cout << "4. View Balance" << endl;
                    cout << "5. View Transaction History" << endl;
                    cout << "6. Logout" << endl;
                    cout << "Enter your choice: ";
                    cin >> userChoice;

                    if (userChoice == 1) {
                        double amount;
                        cout << "Enter amount to deposit: ";
                        cin >> amount;
                        client.deposit(amount);
                    }
                    else if (userChoice == 2) {
                        double amount;
                        cout << "Enter amount to withdraw: ";
                        cin >> amount;
                        client.withdraw(amount);
                    }
                    else if (userChoice == 3) {
                        int targetUserID;
                        double amount;
                        cout << "Enter target user ID: ";
                        cin >> targetUserID;
                        cout << "Enter amount to transfer: ";
                        cin >> amount;
                        client.transferFunds(targetUserID, amount);
                    }
                    else if (userChoice == 4) {
                        client.viewBalance();
                    }
                    else if (userChoice == 5) {
                        client.viewTransactionHistory();
                    }
                    else if (userChoice == 6) {
                        cout << "Logging out..." << endl;
                        break;
                    }
                    else {
                        cout << "Invalid choice. Please try again." << endl;
                    }
                }
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
