#ifndef BANKINGEMPLOYEE_H
#define BANKINGEMPLOYEE_H

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class BankingEmployee
{
private:
    string employeeID;
    string password;

public:
    // Constructor
    BankingEmployee(string id, string pass);

    // Login method
    bool login(const string &id, const string &pass);

    // View all client accounts
    void viewClientAccounts();

    // Approve a client account
    void approveAccount(const string &accountID);

    // Reject a client account
    void rejectAccount(const string &accountID);

    // Approve a loan request
    void approveLoanRequest(const string &loanID);

    // View transaction history of a client account
    void viewTransactionHistory(const string &accountID);

    // Freeze a client account
    void freezeAccount(const string &accountID);

    // Close a client account
    void closeAccount(const string &accountID);
};

#endif // BANKINGEMPLOYEE_H