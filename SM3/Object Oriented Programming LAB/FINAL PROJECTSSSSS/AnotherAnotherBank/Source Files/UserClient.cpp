#include "UserClient.h"
#include <iostream>
#include <fstream>

using namespace std;

// Constructor
UserClient::UserClient(string name, string address, string id, string pass, AccountType type, double limit, bool companyAccount)
    : userName(name), userAddress(address), userID(id), password(pass), accountType(type),
      balance(0), dailyWithdrawalLimit(limit), hasCompanyAccount(companyAccount) {}

// Set the flag for company account availability
void UserClient::setCompanyAccount(bool hasAccount)
{
    hasCompanyAccount = hasAccount;
}

// Check if the user has a company account
bool UserClient::hasCompany() const
{
    return hasCompanyAccount;
}

// Add a new card to the user account
void UserClient::addCard(const string &cardNumber, const string &pin)
{
    cards.emplace_back(cardNumber, pin);
    ofstream outFile("cards.txt", ios::app);
    if (outFile.is_open())
    {
        outFile << userID << ", " << cardNumber << ", " << pin << endl;
        outFile.close();
    }
    else
    {
        cerr << "Error: Unable to save card information!" << endl;
    }
}

// Deposit money to the user's balance
void UserClient::deposit(double amount)
{
    Transaction transaction("TXN001", "Deposit", amount, Transaction::getCurrentDate());
    transaction.deposit(balance);
}

// Withdraw money from the user's balance
void UserClient::withdraw(double amount)
{
    Transaction transaction("TXN002", "Withdraw", amount, Transaction::getCurrentDate());
    transaction.withdraw(balance, dailyWithdrawalLimit);
}

// Transfer funds to another user or company
void UserClient::transferFunds(string targetUserID, double amount)
{
    double dummyReceiverBalance = 0; // Simulate the receiver's balance
    Transaction transaction("TXN003", "Transfer", amount, Transaction::getCurrentDate(), nullptr, targetUserID);
    transaction.transfer(balance, dailyWithdrawalLimit, dummyReceiverBalance);
}

// View the current balance
void UserClient::viewBalance() const
{
    cout << "Current balance: " << balance << " PKR" << endl;
}

// Save the user data to a file
void UserClient::saveToFile()
{
    ofstream outFile("Users.txt", ios::app);
    if (outFile.is_open())
    {
        outFile << userName << ", " << userAddress << ", " << userID << ", " << password << ", "
                << static_cast<int>(accountType) << ", " << balance << endl;
        outFile.close();
    }
    else
    {
        cerr << "Error: Unable to save user information!" << endl;
    }
}