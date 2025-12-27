#include "Transaction.h"
#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

// Constructor
Transaction::Transaction(string id, string type, double amt, string date, Card *card, string targetID)
    : transactionID(id), transactionType(type), amount(amt), transactionDate(date), cardUsed(card), targetUserID(targetID) {}

// Helper function to log transaction to a file
void Transaction::logTransaction()
{
    ofstream outFile("transactions.txt", ios::app);
    if (outFile.is_open())
    {
        outFile << transactionDate << ", " << transactionID << ", " << amount
                << ", " << transactionType;
        if (!targetUserID.empty())
        {
            outFile << ", " << targetUserID;
        }
        outFile << endl;
        outFile.close();
    }
    else
    {
        cerr << "Error: Unable to log transaction!" << endl;
    }
}

// Deposit method
bool Transaction::deposit(double &balance)
{
    balance += amount;
    logTransaction();
    cout << "Deposit successful! New balance: " << balance << " PKR" << endl;
    return true;
}

// Withdraw method
bool Transaction::withdraw(double &balance, double dailyLimit)
{
    if (amount > balance)
    {
        cout << "Insufficient balance!" << endl;
        return false;
    }
    if (amount > dailyLimit)
    {
        cout << "Transaction exceeds daily withdrawal limit!" << endl;
        return false;
    }
    balance -= amount;
    logTransaction();
    cout << "Withdrawal successful! New balance: " << balance << " PKR" << endl;
    return true;
}

// Transfer method
bool Transaction::transfer(double &senderBalance, double dailyLimit, double &receiverBalance)
{
    if (amount > senderBalance)
    {
        cout << "Insufficient balance!" << endl;
        return false;
    }
    if (amount > dailyLimit)
    {
        cout << "Transaction exceeds daily withdrawal limit!" << endl;
        return false;
    }
    senderBalance -= amount;
    receiverBalance += amount;
    logTransaction();
    cout << "Transfer successful! " << amount << " PKR sent to User ID: " << targetUserID << endl;
    return true;
}

// Get current date in YYYY-MM-DD format
string Transaction::getCurrentDate()
{
    time_t now = time(0);
    tm *ltm = localtime(&now);
    return to_string(1900 + ltm->tm_year) + "-" +
           to_string(1 + ltm->tm_mon) + "-" +
           to_string(ltm->tm_mday);
}