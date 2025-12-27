#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include "Card.h"
using namespace std;

class Transaction
{
private:
    string transactionID;
    string transactionDate;
    double amount;
    string transactionType;
    string targetUserID;
    Card *cardUsed;

    // Helper function to log transaction to a file
    void logTransaction();

public:
    // Constructor
    Transaction(string id, string type, double amt, string date, Card *card = nullptr, string targetID = "");

    // Deposit method
    bool deposit(double &balance);

    // Withdraw method
    bool withdraw(double &balance, double dailyLimit);

    // Transfer method
    bool transfer(double &senderBalance, double dailyLimit, double &receiverBalance);

    // Get current date in YYYY-MM-DD format
    static string getCurrentDate();
};

#endif // TRANSACTION_H