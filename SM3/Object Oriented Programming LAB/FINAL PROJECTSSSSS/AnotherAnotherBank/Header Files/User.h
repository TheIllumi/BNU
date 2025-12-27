#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

class User
{
private:
    static int userCount;
    int userID;
    string name;
    string CNIC;
    string address;
    int phone;
    int loginID;
    string password;
    double accountBalance;
    string accountType;

    // Helper functions
    bool isValidName(const string &str);
    bool isValidCNIC(const string &str);
    string trim(const string &str);
    bool isFileEmpty();
    void determineAccountType();

public:
    User();
    void registerUser();
    void loginUser();
};

#endif // USER_H