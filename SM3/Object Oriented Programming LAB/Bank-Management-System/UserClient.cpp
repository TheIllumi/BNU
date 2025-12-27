#include "UserClient.h"
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <iostream>

using namespace std;

int UserClient::getUserID() {
    // This method should return the userID after successful login.
    return this->userID;  // You should set this value after login.
}

void UserClient::setUserID(int id) {
    userID = id;  // Set the userID
}

void UserClient::deposit(double amount) {
    sql::Driver* driver;
    sql::Connection* con;
    sql::PreparedStatement* pstmt;

    try {
        driver = get_driver_instance();
        con = driver->connect("tcp://172.20.193.156:3306", "root3", "root3");
        con->setSchema("BNU_VIVA");

        pstmt = con->prepareStatement("INSERT INTO transactions (amount, transactionType, userID) VALUES (?, 'Deposit', ?)");
        pstmt->setDouble(1, amount);
        pstmt->setInt(2, getUserID());
        pstmt->execute();

        con->commit();  // Commit the transaction to the database

        cout << "Deposit successful!" << endl;

        delete pstmt;
        delete con;
    }
    catch (sql::SQLException& e) {
        cout << "Error: " << e.what() << endl;
    }
}

void UserClient::withdraw(double amount) {
    sql::Driver* driver;
    sql::Connection* con;
    sql::PreparedStatement* pstmt;
    sql::ResultSet* res;

    try {
        driver = get_driver_instance();
        con = driver->connect("tcp://172.20.193.156:3306", "root3", "root3");
        con->setSchema("BNU_VIVA");

        // Query current balance
        pstmt = con->prepareStatement("SELECT SUM(amount) FROM transactions WHERE userID = ? AND transactionType = 'Deposit'");
        pstmt->setInt(1, getUserID());
        res = pstmt->executeQuery();

        double totalDeposits = 0;
        if (res->next()) {
            totalDeposits = res->getDouble(1);
        }

        pstmt = con->prepareStatement("SELECT SUM(amount) FROM transactions WHERE userID = ? AND transactionType = 'Withdrawal'");
        pstmt->setInt(1, getUserID());
        res = pstmt->executeQuery();

        double totalWithdrawals = 0;
        if (res->next()) {
            totalWithdrawals = res->getDouble(1);
        }

        double currentBalance = totalDeposits - totalWithdrawals;
        if (currentBalance < amount) {
            cout << "Insufficient balance!" << endl;
            return;  // Stop withdrawal if balance is not enough
        }

        // Proceed with withdrawal
        pstmt = con->prepareStatement("INSERT INTO transactions (amount, transactionType, userID) VALUES (?, 'Withdrawal', ?)");
        pstmt->setDouble(1, amount);
        pstmt->setInt(2, getUserID());
        pstmt->execute();

        con->commit();  // Commit the transaction to the database

        cout << "Withdrawal successful!" << endl;

        delete pstmt;
        delete con;
    }
    catch (sql::SQLException& e) {
        cout << "Error: " << e.what() << endl;
    }
}

void UserClient::transferFunds(int targetUserID, double amount) {
    sql::Driver* driver;
    sql::Connection* con;
    sql::PreparedStatement* pstmt;

    try {
        driver = get_driver_instance();
        con = driver->connect("tcp://172.20.193.156:3306", "root3", "root3");
        con->setSchema("BNU_VIVA");

        // Same logic as withdrawal for checking balance before transfer
        pstmt = con->prepareStatement("SELECT SUM(amount) FROM transactions WHERE userID = ? AND transactionType = 'Deposit'");
        pstmt->setInt(1, getUserID());
        sql::ResultSet* res = pstmt->executeQuery();

        double totalDeposits = 0;
        if (res->next()) {
            totalDeposits = res->getDouble(1);
        }

        pstmt = con->prepareStatement("SELECT SUM(amount) FROM transactions WHERE userID = ? AND transactionType = 'Withdrawal'");
        pstmt->setInt(1, getUserID());
        res = pstmt->executeQuery();

        double totalWithdrawals = 0;
        if (res->next()) {
            totalWithdrawals = res->getDouble(1);
        }

        double currentBalance = totalDeposits - totalWithdrawals;
        if (currentBalance < amount) {
            cout << "Insufficient balance for transfer!" << endl;
            return;  // Stop transfer if balance is not enough
        }

        pstmt = con->prepareStatement("INSERT INTO transactions (amount, transactionType, userID, targetUserID) VALUES (?, 'Transfer', ?, ?)");
        pstmt->setDouble(1, amount);
        pstmt->setInt(2, getUserID());
        pstmt->setInt(3, targetUserID);
        pstmt->execute();

        con->commit();  // Commit the transaction to the database

        cout << "Transfer successful!" << endl;

        delete pstmt;
        delete con;
    }
    catch (sql::SQLException& e) {
        cout << "Error: " << e.what() << endl;
    }
}

void UserClient::viewBalance() {
    sql::Driver* driver;
    sql::Connection* con;
    sql::PreparedStatement* pstmt;
    sql::ResultSet* res;

    try {
        driver = get_driver_instance();
        con = driver->connect("tcp://172.20.193.156:3306", "root3", "root3");
        con->setSchema("BNU_VIVA");

        pstmt = con->prepareStatement("SELECT SUM(amount) FROM transactions WHERE userID = ? AND transactionType = 'Deposit'");
        pstmt->setInt(1, getUserID());
        res = pstmt->executeQuery();

        double totalDeposits = 0;
        if (res->next()) {
            totalDeposits = res->getDouble(1);
        }

        pstmt = con->prepareStatement("SELECT SUM(amount) FROM transactions WHERE userID = ? AND transactionType = 'Withdrawal'");
        pstmt->setInt(1, getUserID());
        res = pstmt->executeQuery();

        double totalWithdrawals = 0;
        if (res->next()) {
            totalWithdrawals = res->getDouble(1);
        }

        double balance = totalDeposits - totalWithdrawals;
        cout << "Your current balance is: " << balance << endl;

        delete pstmt;
        delete res;
        delete con;
    }
    catch (sql::SQLException& e) {
        cout << "Error: " << e.what() << endl;
    }
}

void UserClient::viewTransactionHistory() {
    sql::Driver* driver;
    sql::Connection* con;
    sql::PreparedStatement* pstmt;
    sql::ResultSet* res;

    try {
        driver = get_driver_instance();
        con = driver->connect("tcp://172.20.193.156:3306", "root3", "root3");
        con->setSchema("BNU_VIVA");

        pstmt = con->prepareStatement("SELECT transactionID, amount, transactionType, transactionDate, targetUserID FROM transactions WHERE userID = ?");
        pstmt->setInt(1, getUserID());
        res = pstmt->executeQuery();

        cout << "Transaction History:" << endl;
        while (res->next()) {
            int transactionID = res->getInt("transactionID");
            double amount = res->getDouble("amount");
            string transactionType = res->getString("transactionType");
            string transactionDate = res->getString("transactionDate");
            int targetUserID = res->getInt("targetUserID");

            cout << "Transaction ID: " << transactionID << ", Amount: " << amount << ", Type: " << transactionType
                << ", Date: " << transactionDate << ", Target User ID: " << targetUserID << endl;
        }

        delete pstmt;
        delete res;
        delete con;
    }
    catch (sql::SQLException& e) {
        cout << "Error: " << e.what() << endl;
    }
}
