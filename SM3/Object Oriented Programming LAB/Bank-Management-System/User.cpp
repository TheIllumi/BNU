//User.cpp
#include "User.h"
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include <iostream>

using namespace std;

User::User() { userID = -1; }

bool User::signUp() {
    sql::Driver* driver;
    sql::Connection* con;
    sql::PreparedStatement* pstmt;

    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter CNIC (13-digit): ";
    cin >> CNIC;
    cout << "Enter Address: ";
    cin.ignore();
    getline(cin, address);
    cout << "Enter Phone: ";
    cin >> phone;
    cout << "Enter Username: ";
    cin >> username;
    cout << "Enter Password: ";
    cin >> password;

    try {
        driver = get_driver_instance();
        con = driver->connect("tcp://172.20.193.156:3306", "root3", "root3");
        con->setSchema("BNU_VIVA");

        pstmt = con->prepareStatement("INSERT INTO users(name, CNIC, address, phone, username, password) VALUES(?, ?, ?, ?, ?, ?)");
        pstmt->setString(1, name);
        pstmt->setString(2, CNIC);
        pstmt->setString(3, address);
        pstmt->setString(4, phone);
        pstmt->setString(5, username);
        pstmt->setString(6, password);
        pstmt->execute();

        cout << "Account successfully created!" << endl;

        delete pstmt;
        delete con;
        return true;
    }
    catch (sql::SQLException& e) {
        cout << "Error: " << e.what() << endl;
        return false;
    }
}

bool User::login() {
    sql::Driver* driver;
    sql::Connection* con;
    sql::PreparedStatement* pstmt;
    sql::ResultSet* res;

    cout << "Enter Username: ";
    cin >> username;
    cout << "Enter Password: ";
    cin >> password;

    try {
        driver = get_driver_instance();
        con = driver->connect("tcp://172.20.193.156:3306", "root3", "root3");
        con->setSchema("BNU_VIVA");

        pstmt = con->prepareStatement("SELECT userID FROM users WHERE username = ? AND password = ?");
        pstmt->setString(1, username);
        pstmt->setString(2, password);
        res = pstmt->executeQuery();

        if (res->next()) {
            userID = res->getInt("userID");
            cout << "Login successful! Welcome, " << username << "!" << endl;
            delete res;
            delete pstmt;
            delete con;
            return true;
        }
        else {
            cout << "Invalid username or password!" << endl;
            delete res;
            delete pstmt;
            delete con;
            return false;
        }
    }
    catch (sql::SQLException& e) {
        cout << "Error: " << e.what() << endl;
        return false;
    }
}

int User::getUserID() const {
    return userID;
}