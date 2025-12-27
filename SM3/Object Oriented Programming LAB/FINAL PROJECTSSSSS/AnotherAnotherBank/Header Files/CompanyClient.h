#ifndef COMPANYCLIENT_H
#define COMPANYCLIENT_H

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

class CompanyClient
{
private:
    string companyName;
    string companyAddress;
    string taxNumber;
    int companyAccID;
    string password;
    double balance;
    double dailyWithdrawalLimit;
    AccountType accountType; // Add AccountType here
    vector<Card> cards;

public:
    // Constructor
    CompanyClient(string name, string address, string tax, int accID, string pass, double limit, AccountType type);

    // Add a new card to the company
    void addCard(const string &cardNumber, const string &pin);

    // Deposit money to the company's balance
    void deposit(double amount);

    // Withdraw money from the company's balance
    void withdraw(double amount);

    // Transfer funds to another company or individual
    void transferFunds(string targetUserID, double amount);

    // View the current balance
    void viewBalance() const;

    // Save the company data to a file
    void saveToFile();
};

#endif // COMPANYCLIENT_H