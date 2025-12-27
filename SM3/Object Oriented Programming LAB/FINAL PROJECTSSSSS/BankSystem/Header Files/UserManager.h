// UserManager.h
#ifndef USER_MANAGER_H
#define USER_MANAGER_H

#include "UserClient.h"
#include "User.h"
#include "CompanyClient.h"
#include "AccountType.h"
#include "BankingEmployee.h"
#include "Card.h"
#include "Transaction.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class UserManager
{
private:
    vector<UserClient> users;

    UserClient *findUserByID(const std::string &userID);

public:
    void registerUser();
    void loginUser(const string &userID, const string &password);
    bool addCardToUser(const string &userID, const string &cardNumber, const std::string &pin);
    bool depositToUser(const string &userID, double amount);
    bool withdrawFromUser(const string &userID, double amount);
    bool transferFunds(const string &senderID, const string &receiverID, double amount);
    bool viewUserBalance(const string &userID);
};

#endif // USER_MANAGER_H