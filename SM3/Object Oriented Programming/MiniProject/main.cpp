#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

// Base User Class
class User {
protected:
    string userID;
    string name;
    string CNIC;
    string address;
    int phone;
    int loginID;
    string password;

public:
    User(string id, string name, string cnic, string addr, int phone, int login, string pass)
        : userID(id), name(name), CNIC(cnic), address(addr), phone(phone), loginID(login), password(pass) {}

    virtual bool login() {
        // Implement login logic
        return true;
    }
    virtual ~User() {}
};

// Bank Employee inherits User
class BankEmployee : public User {
public:
    BankEmployee(string id, string name, string cnic, string addr, int phone, int login, string pass)
        : User(id, name, cnic, addr, phone, login, pass) {}

    void approveAccount() {
        // Implement account approval logic
    }

    void rejectAccount() {
        // Implement account rejection logic
    }

    void viewClients() {
        // Implement logic to view clients
    }

    void approveLoan() {
        // Implement loan approval logic
    }

    void rejectLoan() {
        // Implement loan rejection logic
    }

    void freezeAccount() {
        // Implement account freeze logic
    }
};

// AccountType Class
class AccountType {
protected:
    string typeName;
    double dailyWithdrawalLimit;

public:
    AccountType(string name, double limit) : typeName(name), dailyWithdrawalLimit(limit) {}

    virtual ~AccountType() {}
};

// Derived Account Types
class Bronze : public AccountType {
public:
    Bronze() : AccountType("Bronze", 100000) {}
};

class Gold : public AccountType {
public:
    Gold() : AccountType("Gold", 500000) {}
};

class Business : public AccountType {
public:
    Business() : AccountType("Business", 20000000) {}
};

// Card Class
class Card {
private:
    string cardNumber;
    string PIN;
    bool isFraudulent;

public:
    Card(string cardNo, string pin) : cardNumber(cardNo), PIN(pin), isFraudulent(false) {}

    bool validatePIN(string pin) {
        return pin == PIN;
    }

    void markFraudulent() {
        isFraudulent = true;
    }
};

// Transaction Class
class Transaction {
private:
    string transactionID;
    string transactionDate;
    double amount;
    string transactionType;
    string targetUserID;

public:
    Transaction(string id, string date, double amt, string type, string targetID)
        : transactionID(id), transactionDate(date), amount(amt), transactionType(type), targetUserID(targetID) {}
};

// User Client inherits User
class UserClient : public User {
private:
    AccountType* accountType;
    vector<Card> cards;

public:
    UserClient(string id, string name, string cnic, string addr, int phone, int login, string pass, AccountType* accType)
        : User(id, name, cnic, addr, phone, login, pass), accountType(accType) {}

    void deposit(double amount) {
        // Implement deposit logic
    }

    bool withdraw(double amount) {
        // Implement withdraw logic
        return true;
    }

    bool transferFunds(string targetUserID, double amount) {
        // Implement fund transfer logic
        return true;
    }

    double viewBalance() {
        // Implement balance view logic
        return 0.0;
    }

    vector<Transaction> viewTransactionHistory() {
        // Implement transaction history logic
        return {};
    }
};

// Company Client inherits User
class CompanyClient : public User {
private:
    int companyAccID;
    string companyName;
    string companyAddress;
    string taxNumber;
    AccountType* accountType;
    vector<UserClient*> employees;
    vector<Card> cards;

public:
    CompanyClient(string id, string name, string cnic, string addr, int phone, int login, string pass, int accID,
                  string compName, string compAddr, string tax, AccountType* accType)
        : User(id, name, cnic, addr, phone, login, pass), companyAccID(accID), companyName(compName),
          companyAddress(compAddr), taxNumber(tax), accountType(accType) {}

    void deposit(double amount) {
        // Implement deposit logic
    }

    bool withdraw(double amount) {
        // Implement withdraw logic
        return true;
    }

    bool transferFunds(string targetUserID, double amount) {
        // Implement fund transfer logic
        return true;
    }

    void requestLoan(double amount) {
        // Implement loan request logic
    }

    double viewBalance() {
        // Implement balance view logic
        return 0.0;
    }

    vector<Transaction> viewTransactionHistory() {
        // Implement transaction history logic
        return {};
    }
};

int main() {
    // Example usage
    AccountType* bronzeAccount = new Bronze();
    UserClient user1("U001", "John Doe", "12345-6789012-3", "123 Street", 1234567890, 1001, "password", bronzeAccount);

    CompanyClient company1("C001", "Jane Doe", "98765-4321098-7", "456 Avenue", 9876543210, 2001, "pass123", 1,
                           "TechCorp", "789 Blvd", "NTN123", bronzeAccount);

    user1.deposit(5000.0);
    company1.requestLoan(100000.0);

    delete bronzeAccount;
    return 0;
}