#include <iostream>
#include <vector>

#include "User.h"
#include "BankingEmployee.h"
#include "UserClient.h"
#include "CompanyClient.h"
#include "AccountType.h"
#include "Bronze.h"
#include "Gold.h"
#include "Business.h"
#include "Card.h"
#include "Transaction.h"

using namespace std;

int main()
{
    vector<User *> users;
    vector<BankingEmployee> employees;
    vector<Transaction> transactions;
    int choice;
    bool running = true;

    while (running)
    {
        cout << "\n--- Welcome to the Banking System ---\n";
        cout << "1. Create User Account\n";
        cout << "2. Create Company Account\n";
        cout << "3. Deposit Money\n";
        cout << "4. Withdraw Money\n";
        cout << "5. Transfer Money\n";
        cout << "6. View Account Balance\n";
        cout << "7. View Transaction History\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            string name;
            double initialDeposit;
            cout << "Enter your name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter initial deposit: ";
            cin >> initialDeposit;

            // Create a UserClient with a default account type (e.g., Bronze)
            UserClient *newUser = new UserClient(name, new Bronze(), initialDeposit);
            users.push_back(newUser);

            cout << "User account created successfully!\n";
            break;
        }
        case 2:
        {
            string companyName;
            double initialDeposit;
            cout << "Enter company name: ";
            cin.ignore();
            getline(cin, companyName);
            cout << "Enter initial deposit: ";
            cin >> initialDeposit;

            // Create a CompanyClient with a Business account type
            CompanyClient *newCompany = new CompanyClient(companyName, new Business(), initialDeposit);
            users.push_back(newCompany);

            cout << "Company account created successfully!\n";
            break;
        }
        case 3:
        {
            int userId;
            double amount;
            cout << "Enter user ID (0-based index): ";
            cin >> userId;
            cout << "Enter deposit amount: ";
            cin >> amount;

            if (userId >= 0 && userId < users.size())
            {
                users[userId]->deposit(amount);
                cout << "Deposit successful!\n";
            }
            else
            {
                cout << "Invalid user ID.\n";
            }
            break;
        }
        case 4:
        {
            int userId;
            double amount;
            cout << "Enter user ID (0-based index): ";
            cin >> userId;
            cout << "Enter withdrawal amount: ";
            cin >> amount;

            if (userId >= 0 && userId < users.size())
            {
                if (users[userId]->withdraw(amount))
                {
                    cout << "Withdrawal successful!\n";
                }
                else
                {
                    cout << "Insufficient funds.\n";
                }
            }
            else
            {
                cout << "Invalid user ID.\n";
            }
            break;
        }
        case 5:
        {
            int fromUserId, toUserId;
            double amount;
            cout << "Enter sender user ID: ";
            cin >> fromUserId;
            cout << "Enter receiver user ID: ";
            cin >> toUserId;
            cout << "Enter transfer amount: ";
            cin >> amount;

            if (fromUserId >= 0 && fromUserId < users.size() && toUserId >= 0 && toUserId < users.size())
            {
                if (users[fromUserId]->transfer(*users[toUserId], amount))
                {
                    cout << "Transfer successful!\n";
                }
                else
                {
                    cout << "Transfer failed.\n";
                }
            }
            else
            {
                cout << "Invalid user ID(s).\n";
            }
            break;
        }
        case 6:
        {
            int userId;
            cout << "Enter user ID: ";
            cin >> userId;

            if (userId >= 0 && userId < users.size())
            {
                cout << "Current balance: " << users[userId]->getBalance() << "\n";
            }
            else
            {
                cout << "Invalid user ID.\n";
            }
            break;
        }
        case 7:
        {
            int userId;
            cout << "Enter user ID: ";
            cin >> userId;

            if (userId >= 0 && userId < users.size())
            {
                users[userId]->viewTransactionHistory();
            }
            else
            {
                cout << "Invalid user ID.\n";
            }
            break;
        }
        case 8:
            cout << "Exiting the banking system. Goodbye!\n";
            running = false;
            break;
        default:
            cout << "Invalid option. Please try again.\n";
        }
    }

    // Clean up allocated memory for users
    for (auto user : users)
    {
        delete user;
    }

    return 0;
}