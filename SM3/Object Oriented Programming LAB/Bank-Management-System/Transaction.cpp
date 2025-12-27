//Transaction.cpp
#include "Transaction.h"
#include <iostream>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/prepared_statement.h>

using namespace std;

void Transaction::logTransaction(int userID, double amount, const string& type, int targetUserID) {
    try {
        sql::mysql::MySQL_Driver* driver;
        sql::Connection* con;
        sql::PreparedStatement* pstmt;

        // MySQL database credentials
        driver = sql::mysql::get_mysql_driver_instance();
        con = driver->connect("tcp://172.20.193.156:3306", "root3", "root3");
        con->setSchema("BNU_VIVA");

        pstmt = con->prepareStatement("INSERT INTO transactions (userID, amount, transactionType, targetUserID) VALUES (?, ?, ?, ?)");
        pstmt->setInt(1, userID);
        pstmt->setDouble(2, amount);
        pstmt->setString(3, type);
        pstmt->setInt(4, targetUserID);
        pstmt->executeUpdate();

        delete pstmt;
        delete con;
        cout << "Transaction logged successfully!" << endl;
    }
    catch (sql::SQLException& e) {
        cout << "Error logging transaction: " << e.what() << endl;
    }
}