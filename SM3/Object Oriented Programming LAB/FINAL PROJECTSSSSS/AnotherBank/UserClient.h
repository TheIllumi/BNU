#ifndef USERCLIENT_H
#define USERCLIENT_H

#include <string>
#include <vector>
#include "Card.h"
#include "Transaction.h"

using namespace std;

// Enum to represent the account type
enum class AccountType
{
    PERSONAL,
    BUSINESS
};

class UserClient
{
private:
    string userName;
    string userAddress;
    string userID;
    string password;
    double balance;
    double dailyWithdrawalLimit;
    AccountType accountType;
    bool hasCompanyAccount; // Add flag to check if the user has a company account
    vector<Card> cards;

public:
    // Constructor
    UserClient(string name, string address, string id, string pass, AccountType type, double limit, bool companyAccount = false);

    // Add a new card to the user account
    void addCard(const string &cardNumber, const string &pin);

    // Deposit money to the user's balance
    void deposit(double amount);

    // Withdraw money from the user's balance
    void withdraw(double amount);

    // Transfer funds to another user or company
    void transferFunds(string targetUserID, double amount);

    // View the current balance
    void viewBalance() const;

    // Save the user data to a file
    void saveToFile();

    // Set the flag for company account availability
    void setCompanyAccount(bool hasAccount);

    // Check if the user has a company account
    bool hasCompany() const;
};

#endif // USERCLIENT_H