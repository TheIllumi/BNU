//User.h
#pragma once
#ifndef USER_H
#define USER_H

#include <string>

class User {
private:
    int userID;
    std::string name;
    std::string CNIC;
    std::string address;
    std::string phone;
    std::string username;
    std::string password;

public:
    User();
    bool signUp();
    bool login();
    int getUserID() const;
};

#endif // USER_H
