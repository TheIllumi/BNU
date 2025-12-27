//UserClient.h
#pragma once
#pragma once
#ifndef USERCLIENT_H
#define USERCLIENT_H

#include "User.h"

// UserClient.h

class UserClient {
private:
    int userID;  // Store userID of logged-in user

public:
    int getUserID();
    void setUserID(int id);
    void deposit(double amount);
    void withdraw(double amount);
    void transferFunds(int targetUserID, double amount);
    void viewBalance();
    void viewTransactionHistory();
};

#endif // USERCLIENT_H
