//Tranaction.h
#pragma once
#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>  // Include this to use std::string

class Transaction {
public:
    static void logTransaction(int userID, double amount, const std::string& type, int targetUserID = -1);
};

#endif // TRANSACTION_H
