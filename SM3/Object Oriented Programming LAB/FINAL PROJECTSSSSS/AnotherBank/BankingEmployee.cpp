#include "BankingEmployee.h"
#include <iostream>
#include <fstream>

using namespace std;

// Constructor
BankingEmployee::BankingEmployee(string id, string pass)
    : employeeID(id), password(pass) {}

// Login method
bool BankingEmployee::login(const string &id, const string &pass)
{
    if (id == employeeID && pass == password)
    {
        cout << "Login successful!" << endl;
        return true;
    }
    else
    {
        cout << "Invalid credentials!" << endl;
        return false;
    }
}

// View all client accounts
void BankingEmployee::viewClientAccounts()
{
    ifstream inFile("Companies.txt");
    if (inFile.is_open())
    {
        string line;
        cout << "Client Accounts:\n";
        while (getline(inFile, line))
        {
            cout << line << endl;
        }
        inFile.close();
    }
    else
    {
        cerr << "Error: Unable to read client accounts!" << endl;
    }
}

// Approve a client account
void BankingEmployee::approveAccount(const string &accountID)
{
    cout << "Account " << accountID << " has been approved." << endl;
}

// Reject a client account
void BankingEmployee::rejectAccount(const string &accountID)
{
    cout << "Account " << accountID << " has been rejected." << endl;
}

// Approve a loan request
void BankingEmployee::approveLoanRequest(const string &loanID)
{
    cout << "Loan request " << loanID << " has been approved." << endl;
}

// View transaction history of a client account
void BankingEmployee::viewTransactionHistory(const string &accountID)
{
    ifstream inFile("transactions.txt");
    if (inFile.is_open())
    {
        string line;
        cout << "Transaction history for account " << accountID << ":\n";
        while (getline(inFile, line))
        {
            if (line.find(accountID) != string::npos)
            {
                cout << line << endl;
            }
        }
        inFile.close();
    }
    else
    {
        cerr << "Error: Unable to read transaction history!" << endl;
    }
}

// Freeze a client account
void BankingEmployee::freezeAccount(const string &accountID)
{
    cout << "Account " << accountID << " has been frozen." << endl;
}

// Close a client account
void BankingEmployee::closeAccount(const string &accountID)
{
    cout << "Account " << accountID << " has been closed." << endl;
}