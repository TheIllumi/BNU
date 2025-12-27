#ifndef ACCOUNTTYPE_H
#define ACCOUNTTYPE_H

#include <string>
using namespace std;

// Base class for Account Types
class AccountType
{
protected:
    string typeName;
    double dailyWithdrawalLimit;

public:
    // Constructor
    AccountType(string name, double limit);

    // Virtual Destructor
    virtual ~AccountType();
};

// Derived class for Bronze Account
class Bronze : public AccountType
{
public:
    Bronze();
};

// Derived class for Gold Account
class Gold : public AccountType
{
public:
    Gold();
};

// Derived class for Business Account
class Business : public AccountType
{
public:
    Business();
};

#endif // ACCOUNTTYPE_H