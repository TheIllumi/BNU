//db.cpp
#include <iostream>
#include "database.h"
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>

using namespace std;

const string server = "tcp://172.20.193.156:3306";
const string username = "root3";
const string password = "root3";

// Function to initialize the MySQL database connection
void initializeDatabase() {
    sql::Driver* driver;
    sql::Connection* con;
    sql::Statement* stmt;

    try {
        cout << "Attempting to connect to MySQL server..." << endl;
        driver = get_driver_instance();
        con = driver->connect(server, username, password);
        cout << "Connected to MySQL server successfully!" << endl;

        cout << "Setting schema..." << endl;
        con->setSchema("BNU_VIVA");

        stmt = con->createStatement();

        // Drop tables if they exist to avoid conflicts
        stmt->execute("DROP TABLE IF EXISTS transactions");
        stmt->execute("DROP TABLE IF EXISTS users");

        cout << "Finished dropping tables (if existed)" << endl;

        // Corrected 'users' table creation
        stmt->execute(
            "CREATE TABLE users ("
            "userID INT AUTO_INCREMENT PRIMARY KEY, "
            "name VARCHAR(50) NOT NULL, "
            "CNIC CHAR(13) NOT NULL UNIQUE, "
            "address VARCHAR(100), "
            "phone VARCHAR(15), "
            "username VARCHAR(50) UNIQUE NOT NULL, "
            "password VARCHAR(50) NOT NULL"
            ");"
        );
        cout << "Finished creating users table" << endl;

        // Corrected 'transactions' table creation
        stmt->execute(
            "CREATE TABLE transactions ("
            "transactionID INT AUTO_INCREMENT PRIMARY KEY, "
            "userID INT NOT NULL, "
            "amount DOUBLE NOT NULL, "
            "transactionType VARCHAR(50) NOT NULL, "
            "transactionDate TIMESTAMP DEFAULT CURRENT_TIMESTAMP, "
            "targetUserID INT, "
            "FOREIGN KEY (userID) REFERENCES users(userID) ON DELETE CASCADE, "
            "FOREIGN KEY (targetUserID) REFERENCES users(userID) ON DELETE CASCADE"
            ");"
        );
        cout << "Finished creating transactions table" << endl;

        delete stmt;
        delete con;
        cout << "Database initialized successfully!" << endl;
    }
    catch (sql::SQLException& e) {
        cout << "SQL error occurred: " << e.what() << endl;
    }
}