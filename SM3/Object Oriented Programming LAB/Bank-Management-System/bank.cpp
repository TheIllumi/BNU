//bank.cpp
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "bank.h"
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>

using namespace std;

bool login(const string& username, const string& password) {
    sql::Driver* driver;
    sql::Connection* con;
    sql::PreparedStatement* pstmt;
    sql::ResultSet* res;

    try {
        driver = get_driver_instance();
        con = driver->connect("tcp://172.20.193.156:3306", "root3", "root3");
        con->setSchema("BNU_VIVA");

        pstmt = con->prepareStatement("SELECT * FROM users WHERE username = ? AND password = ?");
        pstmt->setString(1, username);
        pstmt->setString(2, password);
        res = pstmt->executeQuery();

        bool found = res->next(); // If a row is found, credentials are correct

        delete res;
        delete pstmt;
        delete con;

        return found;
    }
    catch (sql::SQLException& e) {
        cout << "Error: " << e.what() << endl;
        return false;
    }
}

void signUp(const string& username, const string& password) {
    sql::Driver* driver;
    sql::Connection* con;
    sql::PreparedStatement* pstmt;

    try {
        driver = get_driver_instance();
        con = driver->connect("tcp://172.20.193.156:3306", "root3", "root3");
        con->setSchema("BNU_VIVA");

        pstmt = con->prepareStatement("INSERT INTO users(username, password) VALUES(?, ?)");
        pstmt->setString(1, username);
        pstmt->setString(2, password);
        pstmt->execute();

        cout << "Account successfully created!" << endl;

        delete pstmt;
        delete con;
    }
    catch (sql::SQLException& e) {
        cout << "Error: " << e.what() << endl;
    }
}
