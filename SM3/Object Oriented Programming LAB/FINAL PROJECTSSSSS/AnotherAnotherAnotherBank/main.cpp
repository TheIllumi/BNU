#include <sstream>
#include <string>
#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>
#include <random>
#include <iomanip>
using namespace std;

string trim(const string &str)
{
    size_t start = str.find_first_not_of(" \t"), end = str.find_last_not_of(" \t");
    return (start == string::npos || end == string::npos) ? "" : str.substr(start, end - start + 1);
}

class AccountType
{
protected:
    string typeName;
    double dailyWithdrawalLimit;

public:
    AccountType(string name, double limit) : typeName(name), dailyWithdrawalLimit(limit) {}
    virtual ~AccountType() {}

    string getTypeName() const { return typeName; }
    double getDailyWithdrawalLimit() const { return dailyWithdrawalLimit; }
};

class Bronze : public AccountType { public: Bronze() : AccountType("Bronze", 100000) {} };
class Gold : public AccountType { public: Gold() : AccountType("Gold", 500000) {} };
class Business : public AccountType { public: Business() : AccountType("Business", 20000000) {} };

class Card
{
private:
    string cardNumber, PIN;
    bool isFraudulent = false;
    int failedAttempts = 0;

public:
    Card(string cardNo, string pin) : cardNumber(cardNo), PIN(pin) {}

    string getCardNumber() const { return cardNumber; }

    bool validatePIN(const string &pin)
    {
        if (isFraudulent)
        {
            cout << "Transaction declined: Card is fraudulent." << endl;
            return false;
        }

        if (pin == PIN)
        {
            failedAttempts = 0;
            return true;
        }
        else
        {
            cout << "Invalid PIN. Attempt " << ++failedAttempts << " of 3." << endl;
            if (failedAttempts >= 3) { markFraudulent(); }
            return false;
        }
    }

    void markFraudulent() { isFraudulent = true; }
    bool getFraudulentStatus() const { return isFraudulent; }

    void sendFraudReport() const
    {
        cout << "Fraud alert: A report has been sent to the bank for card " << cardNumber << "." << endl;
    }
};

class UserClient
{
private:
    string userName, userAddress, userID, password;
    double balance = 0.0, dailyWithdrawalLimit;
    AccountType *accountType;
    bool hasCompanyAccount;
    vector<Card> cards;

public:
    UserClient(string name, string address, string id, string pass, AccountType *type, bool companyAccount = false)
            : userName(name), userAddress(address), userID(id), password(pass), accountType(type), hasCompanyAccount(companyAccount)
    {
        dailyWithdrawalLimit = accountType->getDailyWithdrawalLimit();
    }

    void addCard(const string &cardNumber, const string &pin)
    {
        cards.emplace_back(cardNumber, pin);
        ofstream outFile("cards.txt", ios::app);
        if (outFile.is_open()) outFile << userID << "| " << cardNumber << "| " << pin << endl;
        else cerr << "Error: Unable to save card information!" << endl;
    }

    void deposit(double amount)
    {
        if (amount <= 0) cout << "Deposit amount must be positive." << endl;
        else { balance += amount; cout << "Deposited: " << amount << ". New balance: " << balance << endl; }
    }

    void withdraw(double amount)
    {
        if (amount <= 0) cout << "Withdrawal amount must be positive." << endl;
        else if (amount > balance) cout << "Insufficient funds." << endl;
        else if (amount > dailyWithdrawalLimit) cout << "Exceeds daily withdrawal limit." << endl;
        else { balance -= amount; cout << "Withdrawn: " << amount << ". Remaining balance: " << balance << endl; }
    }

    void transferFunds(string targetUserID, double amount)
    {
        if (amount <= 0) cout << "Transfer amount must be positive." << endl;
        else if (amount > balance) cout << "Insufficient funds for transfer." << endl;
        else { balance -= amount; cout << "Transferred " << amount << " to User ID: " << targetUserID << ". Remaining balance: " << balance << endl; }
    }

    void viewBalance() const { cout << "Current balance: " << balance << endl; }

    void saveToFile()
    {
        ofstream outFile(userID + "_data.txt");
        if (!outFile) { cout << "Failed to save user data." << endl; return; }
        outFile << "User Name: " << userName << endl << "User Address: " << userAddress << endl
                << "User ID: " << userID << endl << "Balance: " << balance << endl
                << "Daily Withdrawal Limit: " << dailyWithdrawalLimit << endl
                << "Has Company Account: " << (hasCompanyAccount ? "Yes" : "No") << endl << "Cards:" << endl;
        for (const auto &card : cards) outFile << "  Card Number: " << card.getCardNumber() << endl;
        outFile.close();
        cout << "User data saved successfully." << endl;
    }

    void setCompanyAccount(bool hasAccount) { hasCompanyAccount = hasAccount; }
    bool hasCompany() const { return hasCompanyAccount; }
};

class User
{
private:
    static int userCount;

    bool isValidName(const string &str) { for (char c : str) if (!isalpha(c) && c != ' ') return false; return true; }
    bool isValidCNIC(const string &str) { if (str.length() > 15) return false; for (char c : str) if (!isdigit(c) && c != '-') return false; return true; }

public:
    User() {}

    void registerUser()
    {
        int userID = ++userCount;
        string name, CNIC, address, password, confirmPassword;
        int phone, loginID;
        double dailyWithdrawalLimit;
        AccountType *accountType = nullptr;

        cout << "\nEnter Name (alphabets only): "; cin.ignore();
        while (true) { getline(cin, name); if (isValidName(name)) break; cout << "Invalid name. Please enter alphabets only: "; }

        cout << "Enter CNIC (15 characters max, numbers and '-'): ";
        while (true) { cin >> CNIC; if (isValidCNIC(CNIC)) break; cout << "Invalid CNIC. Please use numbers and '-' only (max 15 characters): "; }

        cout << "Enter Address: "; cin.ignore(); getline(cin, address);

        cout << "Enter Phone (numbers only): "; while (!(cin >> phone) || phone <= 0) { cout << "Invalid phone number. Please enter a valid number: "; cin.clear(); }

        cout << "Enter Login ID (numbers only): "; while (!(cin >> loginID) || loginID <= 0) { cout << "Invalid Login ID. Please enter a valid number: "; cin.clear(); }

        cout << "Enter Password: "; cin >> password;
        cout << "Confirm Password: "; cin >> confirmPassword;
        while (password != confirmPassword) { cout << "Passwords do not match. Enter Password again: "; cin >> password; cout << "Confirm Password: "; cin >> confirmPassword; }

        cout << "Enter Daily Withdrawal Limit: "; while (true) { if (!(cin >> dailyWithdrawalLimit) || dailyWithdrawalLimit <= 0) { cout << "Invalid amount. Please enter a valid daily withdrawal limit: "; cin.clear(); } else break; }

        if (dailyWithdrawalLimit < 100000) accountType = new Bronze();
        else if (dailyWithdrawalLimit <= 500000) accountType = new Gold();
        else if (dailyWithdrawalLimit < 20000000) accountType = new Business();
        else { cout << "The withdrawal limit exceeds the maximum allowed. Please try again.\n"; return; }

        ofstream outFile("users.txt", ios::app);
        if (outFile) {
            if (isFileEmpty()) outFile << "UserID|Name|Address|CNIC|Phone|LoginID|Password|AccountType|DailyWithdrawalLimit\n";
            outFile << userID << "|" << name << "|" << address << "|" << CNIC << "|" << phone << "|" << loginID << "|" << password << "|" << accountType->getTypeName() << "|" << accountType->getDailyWithdrawalLimit() << "\n";
            cout << "\nUser registered successfully! Your User ID is: " << userID << "\n";
        } else cout << "\nError: Could not save user data.\n";
    }

    bool isFileEmpty() { ifstream inFile("users.txt"); return inFile.peek() == ifstream::traits_type::eof(); }

    UserClient *loginUser()
    {
        int inputLoginID; string inputPassword;
        cout << "Enter Login ID: "; cin >> inputLoginID;
        cout << "Enter Password: "; cin >> inputPassword;

        ifstream inFile("users.txt");
        if (!inFile || isFileEmpty()) { cout << "No users registered yet.\n"; return nullptr; }

        string line;
        bool found = false;
        getline(inFile, line);

        while (getline(inFile, line))
        {
            stringstream ss(line); vector<string> columns; string value;
            while (getline(ss, value, '|')) columns.push_back(trim(value));

            if (columns.size() >= 9)
            {
                int storedLoginID = stoi(columns[5]); string storedPassword = columns[6];
                if (storedLoginID == inputLoginID && storedPassword == inputPassword)
                {
                    found = true;
                    string userName = columns[1], userAddress = columns[2], userID = columns[0];
                    string accountTypeStr = columns[8]; AccountType *accountType = nullptr;

                    if (accountTypeStr == "Bronze") accountType = new Bronze();
                    else if (accountTypeStr == "Gold") accountType = new Gold();
                    else if (accountTypeStr == "Business") accountType = new Business();
                    else accountType = new Bronze();

                    return new UserClient(userName, userAddress, userID, storedPassword, accountType);
                }
            }
        }

        if (!found) cout << "Invalid login ID or password. Please try again.\n";
        return nullptr;
    }

    void registerCompany()
    {
        string companyName, companyAddress, companyID, companyPassword;
        double companyCapital;

        cout << "\nEnter Company Name: "; cin.ignore(); getline(cin, companyName);
        cout << "Enter Company Address: "; getline(cin, companyAddress);
        cout << "Enter Company ID: "; cin >> companyID;
        cout << "Enter Company Password: "; cin >> companyPassword;
        cout << "Enter Company Capital: "; while (!(cin >> companyCapital) || companyCapital <= 0) { cout << "Invalid amount. Please enter a valid company capital: "; cin.clear(); }

        ofstream outFile("companies.txt", ios::app);
        if (outFile) {
            outFile << companyID << "|" << companyName << "|" << companyAddress << "|" << companyPassword << "|" << companyCapital << "\n";
            cout << "\nCompany registered successfully! Company ID is: " << companyID << "\n";
        } else {
            cout << "\nError: Could not save company data.\n";
        }
    }
};

int User::userCount = 0;

void displayRegularUserMenu(UserClient *regularUser)
{
    int choice;
    do
    {
        cout << "\n=== Regular User Menu ===\n"
             << "1. Deposit Money\n"
             << "2. Withdraw Money\n"
             << "3. View Balance\n"
             << "4. Logout\n"
             << "Enter your choice: ";
        cin >> choice;

        double amount;
        switch (choice)
        {
            case 1:
                cout << "Enter Deposit Amount: "; cin >> amount;
                regularUser->deposit(amount);
                break;
            case 2:
                cout << "Enter Withdrawal Amount: "; cin >> amount;
                regularUser->withdraw(amount);
                break;
            case 3:
                regularUser->viewBalance();
                break;
            case 4:
                cout << "Logging out...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);
}

void displayCompanyRegistrationMenu()
{
    string companyID, companyName, companyAddress, companyTaxNumber, companyUserID, companyPassword;
    double accountBalance = 0.0;

    cout << "\n=== Company Registration Menu ===\n";
    cout << "Enter Company ID, Name, Address, Tax Number, User ID, and Password: \n";
    cin >> companyID;
    cin.ignore(); // ignore newline
    getline(cin, companyName);
    getline(cin, companyAddress);
    cin >> companyTaxNumber >> companyUserID >> companyPassword;

    // Save to file
    ofstream outFile("companies.txt", ios::app);
    if (outFile)
    {
        outFile << companyID << " | " << companyName << " | " << companyAddress << " | "
                << companyTaxNumber << " | " << companyUserID << " | " << companyPassword << " | "
                << accountBalance << endl;
        cout << "Company registered successfully.\n";
    }
    else
    {
        cout << "Error: Unable to save company information.\n";
    }
}

bool verifyUserCredentials(const string &userID, const string &password)
{
    // TO DO: Implement user credential verification logic here
    // For now, we're just gonna return true for demonstration purposes
    return true;
}

void displayUserClientMenu(UserClient *userClient)
{
    int choice;
    do
    {
        cout << "\n=== User Client Menu ===\n"
             << "1. Add Card\n"
             << "2. Deposit Money\n"
             << "3. Withdraw Money\n"
             << "4. Transfer Funds\n"
             << "5. View Balance\n"
             << "6. Save User Data\n"
             << "7. Logout\n"
             << "8. Regular User Login\n"
             << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
            {
                // Generate a random card number and prompt for PIN
                static random_device rd;
                static mt19937 generator(rd());
                static uniform_int_distribution<int> distribution(1000000000000000, 9999999999999999);
                string cardNumber = to_string(distribution(generator)), pin;

                cout << "Enter PIN for card " << cardNumber << ": ";
                cin >> pin;
                userClient->addCard(cardNumber, pin);
                break;
            }
            case 2: case 3: case 4:
            {
                double amount;
                string targetUserID;
                if (choice == 2) cout << "Enter Deposit Amount: ";
                else if (choice == 3) cout << "Enter Withdrawal Amount: ";
                else { cout << "Enter Target User ID: "; cin >> targetUserID; cout << "Enter Transfer Amount: "; }

                cin >> amount;
                if (choice == 2) userClient->deposit(amount);
                else if (choice == 3) userClient->withdraw(amount);
                else userClient->transferFunds(targetUserID, amount);
                break;
            }
            case 5: userClient->viewBalance(); break;
            case 6: userClient->saveToFile(); break;
            case 7: cout << "Logging out...\n"; break;
            case 8:
            {
                string userID, password;
                cout << "Enter User ID: ";
                cin >> userID;
                cout << "Enter Password: ";
                cin >> password;

                if (verifyUserCredentials(userID, password))
                {
                    UserClient *regularUser = new UserClient(userID, "", "", password, nullptr, false);
                    displayRegularUserMenu(regularUser);
                }
                else
                {
                    cout << "Invalid user ID or password.\n";
                }
                break;
            }
            default: cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 7);
}

class Transaction
{
private:
    string transactionID, transactionDate, transactionType, targetUserID;
    double amount;
    Card *cardUsed;

public:
    // Constructor
    Transaction(string id, string type, double amt, string date, Card *card = nullptr, string targetID = "")
            : transactionID(id), transactionType(type), amount(amt), transactionDate(date), cardUsed(card), targetUserID(targetID) {}

    // Log transaction to the file
    void logTransaction()
    {
        ofstream outFile("transactions.txt", ios::app);
        if (outFile)
        {
            outFile << transactionDate << ", " << transactionID << ", " << amount << ", " << transactionType;
            if (!targetUserID.empty()) outFile << ", " << targetUserID;
            outFile << endl;
        }
        else
        {
            cerr << "Error: Unable to log transaction!" << endl;
        }
    }

    // Deposit method
    bool deposit(double &balance)
    {
        balance += amount;
        logTransaction();
        cout << "Deposit successful! New balance: " << balance << " PKR" << endl;
        return true;
    }

    // Withdraw method
    bool withdraw(double &balance, double dailyLimit)
    {
        if (amount > balance || amount > dailyLimit)
        {
            cout << (amount > balance ? "Insufficient balance!" : "Transaction exceeds daily withdrawal limit!") << endl;
            return false;
        }
        balance -= amount;
        logTransaction();
        cout << "Withdrawal successful! New balance: " << balance << " PKR" << endl;
        return true;
    }

    // Transfer method
    bool transfer(double &senderBalance, double dailyLimit, double &receiverBalance)
    {
        if (amount > senderBalance || amount > dailyLimit)
        {
            cout << (amount > senderBalance ? "Insufficient balance!" : "Transaction exceeds daily withdrawal limit!") << endl;
            return false;
        }
        senderBalance -= amount;
        receiverBalance += amount;
        logTransaction();
        cout << "Transfer successful! " << amount << " PKR sent to User ID: " << targetUserID << endl;
        return true;
    }

    // Get current date
    static string getCurrentDate()
    {
        time_t now = time(0);
        tm *ltm = localtime(&now);
        return to_string(1900 + ltm->tm_year) + "-" + to_string(1 + ltm->tm_mon) + "-" + to_string(ltm->tm_mday);
    }

    // Static function to search transactions by user ID
    static void searchTransactionsByUserID(const string &userID)
    {
        ifstream inFile("transactions.txt");
        string line;
        bool found = false;

        if (inFile)
        {
            while (getline(inFile, line))
            {
                size_t pos = line.find(",");
                string date = line.substr(0, pos);
                line.erase(0, pos + 2);

                pos = line.find(",");
                string transID = line.substr(0, pos);
                line.erase(0, pos + 2);

                pos = line.find(",");
                string amountStr = line.substr(0, pos);
                line.erase(0, pos + 2);

                pos = line.find(",");
                string type = line.substr(0, pos);
                line.erase(0, pos + 2);

                string targetUserID = line;

                if (line.find(userID) != string::npos)
                {
                    cout << "Transaction found: " << date << ", " << transID << ", " << amountStr << ", " << type
                         << ", Target User ID: " << targetUserID << endl;
                    found = true;
                }
            }
            if (!found) cout << "No transactions found for User ID: " << userID << endl;
            inFile.close();
        }
        else
        {
            cerr << "Error: Unable to open transactions file!" << endl;
        }
    }
};

class CompanyClient
{
private:
    string companyName, companyAddress, taxNumber, password;
    int companyAccID;
    double balance = 0, dailyWithdrawalLimit;
    vector<Card> cards;

public:
    CompanyClient(string name, string address, string tax, int accID, string pass, double limit)
            : companyName(name), companyAddress(address), taxNumber(tax), companyAccID(accID), password(pass), dailyWithdrawalLimit(limit) {}

    // Add card to the company account
    void addCard(const string &cardNumber, const string &pin)
    {
        cards.emplace_back(cardNumber, pin);
        ofstream outFile("cards.txt", ios::app);
        if (outFile) outFile << companyAccID << "| " << cardNumber << "| " << pin << endl;
        else cerr << "Error: Unable to save card information!" << endl;
    }

    // Retrieve the balance of another user (simulate database query)
    double getReceiverBalance(const string &targetUserID)
    {
        ifstream inFile("balances.txt");
        string line;
        double receiverBalance = 0.0;

        if (inFile)
        {
            while (getline(inFile, line))
            {
                istringstream iss(line);
                string userID;
                double balance;
                iss >> userID >> balance;
                if (userID == targetUserID)
                {
                    receiverBalance = balance;
                    break;
                }
            }
            inFile.close();
        }
        else cerr << "Error: Unable to open balances file!" << endl;

        return receiverBalance;
    }

    // Deposit money to the account
    void deposit(double amount)
    {
        if (amount <= 0) { cerr << "Error: Deposit amount must be positive!" << endl; return; }
        balance += amount;
        cout << "Deposited " << amount << " PKR successfully." << endl;
        Transaction("TXN001", "Deposit", amount, Transaction::getCurrentDate()).deposit(balance);
    }

    // Withdraw money from the account
    void withdraw(double amount)
    {
        if (amount > dailyWithdrawalLimit) { cerr << "Error: Exceeds daily withdrawal limit!" << endl; return; }
        if (amount > balance) { cerr << "Error: Insufficient funds!" << endl; return; }
        balance -= amount;
        cout << "Withdrawn " << amount << " PKR successfully." << endl;
        Transaction("TXN002", "Withdraw", amount, Transaction::getCurrentDate()).withdraw(balance, dailyWithdrawalLimit);
    }

    // Transfer funds to another user
    void transferFunds(const string &targetUserID, double amount)
    {
        if (amount <= 0) { cerr << "Error: Transfer amount must be positive!" << endl; return; }
        if (amount > balance) { cerr << "Error: Insufficient funds for transfer!" << endl; return; }

        double receiverBalance = getReceiverBalance(targetUserID);
        if (receiverBalance < 0) { cerr << "Error: Target user not found!" << endl; return; }

        balance -= amount;
        receiverBalance += amount;

        ofstream outFile("balances.txt", ios::app);
        if (outFile) outFile << targetUserID << " " << receiverBalance << endl;
        else cerr << "Error: Unable to update receiver's balance!" << endl;

        cout << "Transferred " << amount << " PKR to user ID: " << targetUserID << " successfully." << endl;
        Transaction("TXN003", "Transfer", amount, Transaction::getCurrentDate(), nullptr, targetUserID).transfer(balance, dailyWithdrawalLimit, receiverBalance);
    }

    // Display the current balance
    void viewBalance() const
    {
        cout << "Current balance: " << fixed << setprecision(2) << balance << " PKR" << endl;
    }

    // Save company information to file
    void saveToFile()
    {
        ofstream outFile("companies.txt", ios::app);
        if (outFile)
            outFile << companyName << "| " << companyAddress << "| " << taxNumber
                    << "| " << companyAccID << "| " << password << "| " << fixed << setprecision(2) << balance << endl;
        else cerr << "Error: Unable to save company information!" << endl;
    }

    // Login function for authentication
    bool login(const string &companyID, const string &companyPass)
    {
        ifstream inFile("companies.txt");
        string line;
        bool loginSuccessful = false;

        if (inFile)
        {
            while (getline(inFile, line))
            {
                istringstream iss(line);
                string fileCompanyID, filePassword;
                getline(iss, fileCompanyID, '|');
                getline(iss, filePassword, '|');

                if (fileCompanyID == companyID && filePassword == companyPass)
                {
                    cout << "Login successful for company: " << companyID << endl;
                    loginSuccessful = true;
                    break;
                }
            }
            inFile.close();
        }
        else cerr << "Error: Unable to open companies file!" << endl;

        if (!loginSuccessful) cout << "Invalid company ID or password.\n";
        return loginSuccessful;
    }
};

class BankingEmployee
{
private:
    string employeeID, password;

public:
    BankingEmployee(string id, string pass)
            : employeeID(id), password(pass) {}

    bool login(const string &id, const string &pass)
    {
        if (id == employeeID && pass == password)
        {
            cout << "Login successful!" << endl;
            return true;
        }
        cout << "Invalid credentials!" << endl;
        return false;
    }

    void viewClientAccounts()
    {
        ifstream inFile("Companies.txt");
        if (inFile)
        {
            string line;
            cout << "Client Accounts:\n";
            while (getline(inFile, line)) cout << line << endl;
            inFile.close();
        }
        else cerr << "Error: Unable to read client accounts!" << endl;
    }

    bool isEmployeeOfCompany(int userID)
    {
        ifstream inFile("companies_employees.txt");
        if (inFile)
        {
            string line;
            while (getline(inFile, line))
            {
                stringstream ss(line);
                int clientID, companyID;
                ss >> clientID >> companyID;
                if (clientID == userID) return true;
            }
            inFile.close();
        }
        else cerr << "Error: Unable to read employee data!" << endl;
        return false;
    }

    void approveAccount(const string &accountID)
    {
        cout << "Account " << accountID << " has been approved." << endl;
    }

    void rejectAccount(const string &accountID)
    {
        cout << "Account " << accountID << " has been rejected." << endl;
    }

    void approveLoanRequest(const string &loanID)
    {
        cout << "Loan request " << loanID << " has been approved." << endl;
    }

    void viewTransactionHistory(const string &accountID)
    {
        ifstream inFile("transactions.txt");
        if (inFile)
        {
            string line;
            cout << "Transaction history for account " << accountID << ":\n";
            while (getline(inFile, line))
            {
                if (line.find(accountID) != string::npos) cout << line << endl;
            }
            inFile.close();
        }
        else cerr << "Error: Unable to read transaction history!" << endl;
    }

    void freezeAccount(const string &accountID)
    {
        cout << "Account " << accountID << " has been frozen." << endl;
    }

    void closeAccount(const string &accountID)
    {
        cout << "Account " << accountID << " has been closed." << endl;
    }
};

int main()
{
    BankingEmployee employee("emp001", "empPass123");
    CompanyClient companyClient("TechCorp", "123 Tech St.", "TX12345", 1001, "companyPass123", 50000);
    User user;
    int choice;

    // Display Main Menu
    auto displayMainMenu = []()
    {
        cout << "\n=== Main Menu ===\n1. Register Regular Account\n2. Register Company Account\n3. Login\n4. Exit\nEnter choice: ";
    };

    // Login Flow
    auto loginFlow = [&employee, &companyClient, &user]()
    {
        int loginChoice;
        cout << "\n=== Login Menu ===\n1. User\n2. Employee\n3. Company\n4. Back\nEnter choice: ";
        cin >> loginChoice;

        if (loginChoice == 1) {
            UserClient* userClient = user.loginUser();
            if (userClient) {
                int userChoice;
                do {
                    // UserClient Menu
                    cout << "\n=== User Client Menu ===\n1. View Balance\n2. Transfer Funds\n3. Logout\nEnter choice: ";
                    cin >> userChoice;
                    switch (userChoice) {
                        case 1: userClient->viewBalance(); break;
                        case 2: {
                            string targetUserID;
                            double transferAmount;
                            cout << "Enter Target User ID: "; cin >> targetUserID;
                            cout << "Enter Amount to Transfer: "; cin >> transferAmount;
                            userClient->transferFunds(targetUserID, transferAmount); // Passing arguments to transferFunds
                            break;
                        }
                        case 3: cout << "Logging out...\n"; break;
                        default: cout << "Invalid option.\n";
                    }
                } while (userChoice != 3);
                delete userClient; // Cleanup after logout
            }
        }
        else if (loginChoice == 2) {
            string empID, empPass;
            cout << "Employee ID: "; cin >> empID; cout << "Password: "; cin >> empPass;
            if (employee.login(empID, empPass)) {
                int empChoice;
                do {
                    // Banking Employee Menu - assuming these methods are in your class
                    cout << "\n=== Banking Employee Menu ===\n1. View Client Accounts\n2. Approve Account\n3. Reject Account\n4. Logout\nEnter choice: ";
                    cin >> empChoice;
                    switch (empChoice) {
                        case 1: employee.viewClientAccounts(); break;
                        case 2: employee.approveAccount("accountID"); break;
                        case 3: employee.rejectAccount("accountID"); break;
                        case 4: cout << "Logging out...\n"; break;
                        default: cout << "Invalid option.\n";
                    }
                } while (empChoice != 4);
            }
        }
        else if (loginChoice == 3) {
            string companyID, companyPass;
            cout << "Company ID: "; cin >> companyID; cout << "Password: "; cin >> companyPass;
            if (companyClient.login(companyID, companyPass)) {
                int companyChoice;
                do {
                    // Company Client Menu - assuming these methods are in your class
                    cout << "\n=== Company Client Menu ===\n1. Deposit\n2. Withdraw\n3. Transfer Funds\n4. Logout\nEnter choice: ";
                    cin >> companyChoice;
                    switch (companyChoice) {
                        case 1: companyClient.deposit(1000); break; // Example deposit amount
                        case 2: companyClient.withdraw(500); break; // Example withdrawal amount
                        case 3: companyClient.transferFunds("targetID", 100); break; // Example transfer
                        case 4: cout << "Logging out...\n"; break;
                        default: cout << "Invalid option.\n";
                    }
                } while (companyChoice != 4);
            }
        }
    };

    do
    {
        displayMainMenu();
        cin >> choice;

        if (cin.fail() || choice < 1 || choice > 4) {
            cout << "Invalid choice.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
            case 1: user.registerUser(); break;  // Register Regular User
            case 2: user.registerCompany(); break; // Register Company
            case 3: loginFlow(); break; // Login flow
            case 4: cout << "Exiting..."; break; // Exit
        }
    } while (choice != 4);
    return 0;
}