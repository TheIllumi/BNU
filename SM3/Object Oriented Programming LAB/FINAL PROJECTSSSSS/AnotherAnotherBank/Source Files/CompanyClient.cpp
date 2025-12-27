#include "CompanyClient.h"
#include <iostream>
#include <fstream>

using namespace std;

// Constructor
CompanyClient::CompanyClient(string name, string address, string tax, int accID, string pass, double limit, AccountType type)
    : companyName(name), companyAddress(address), taxNumber(tax), companyAccID(accID), password(pass), accountType(type), balance(0), dailyWithdrawalLimit(limit) {}

// Add a new card to the company
void CompanyClient::addCard(const string &cardNumber, const string &pin)
{
    cards.emplace_back(cardNumber, pin);
    ofstream outFile("cards.txt", ios::app);
    if (outFile.is_open())
    {
        outFile << companyAccID << ", " << cardNumber << ", " << pin << endl;
        outFile.close();
    }
    else
    {
        cerr << "Error: Unable to save card information!" << endl;
    }
}

// Deposit money to the company's balance
void CompanyClient::deposit(double amount)
{
    Transaction transaction("TXN001", "Deposit", amount, Transaction::getCurrentDate());
    transaction.deposit(balance);
}

// Withdraw money from the company's balance
void CompanyClient::withdraw(double amount)
{
    Transaction transaction("TXN002", "Withdraw", amount, Transaction::getCurrentDate());
    transaction.withdraw(balance, dailyWithdrawalLimit);
}

// Transfer funds to another company or individual
void CompanyClient::transferFunds(string targetUserID, double amount)
{
    double dummyReceiverBalance = 0; // Simulate the receiver's balance
    Transaction transaction("TXN003", "Transfer", amount, Transaction::getCurrentDate(), nullptr, targetUserID);
    transaction.transfer(balance, dailyWithdrawalLimit, dummyReceiverBalance);
}

// View the current balance
void CompanyClient::viewBalance() const
{
    cout << "Current balance: " << balance << " PKR" << endl;
}

// Save the company data to a file
void CompanyClient::saveToFile()
{
    ofstream outFile("Companies.txt", ios::app);
    if (outFile.is_open())
    {
        outFile << companyName << ", " << companyAddress << ", " << taxNumber << ", " << companyAccID << ", "
                << static_cast<int>(accountType) << ", " << balance << endl;
        outFile.close();
    }
    else
    {
        cerr << "Error: Unable to save company information!" << endl;
    }
}