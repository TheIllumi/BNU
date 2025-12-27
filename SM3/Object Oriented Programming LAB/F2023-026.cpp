#include <sstream>
#include <string>
#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>
#include <random>
#include <iomanip>
using namespace std;

// Helper function to trim leading and trailing whitespaces
string trim(const string &str)
{
    size_t start = str.find_first_not_of(" \t");
    size_t end = str.find_last_not_of(" \t");
    return (start == string::npos || end == string::npos) ? "" : str.substr(start, end - start + 1);
}

// Base class: AccountType
class AccountType
{
protected:
    string typeName;
    double dailyWithdrawalLimit;

public:
    // Base class constructor
    AccountType(string name, double limit) : typeName(name), dailyWithdrawalLimit(limit) {}

    // Virtual destructor
    virtual ~AccountType() {}

    // Getter for typeName
    string getTypeName() const
    {
        return typeName;
    }

    // Getter for dailyWithdrawalLimit
    double getDailyWithdrawalLimit() const
    {
        return dailyWithdrawalLimit;
    }
};

// Derived class: Bronze
class Bronze : public AccountType
{
public:
    // Bronze Account constructor
    Bronze() : AccountType("Bronze", 100000) {}
};

// Derived class: Gold
class Gold : public AccountType
{
public:
    // Gold Account constructor
    Gold() : AccountType("Gold", 500000) {}
};

// Derived class: Business
class Business : public AccountType
{
public:
    // Business Account constructor
    Business() : AccountType("Business", 20000000) {}
};

// Card Class
class Card
{
private:
    string cardNumber;
    string PIN;
    bool isFraudulent;
    int failedAttempts;

public:
    Card(string cardNo, string pin)
            : cardNumber(cardNo), PIN(pin), isFraudulent(false), failedAttempts(0) {}

    string getCardNumber() const
    {
        return cardNumber;
    }

    bool validatePIN(const string &pin)
    {
        if (isFraudulent)
        {
            cout << "Transaction declined: Card is marked as fraudulent." << endl;
            return false;
        }

        if (pin == PIN)
        {
            failedAttempts = 0;
            return true;
        }
        else
        {
            failedAttempts++;
            cout << "Invalid PIN. Attempt " << failedAttempts << " of 3." << endl;

            if (failedAttempts >= 3)
            {
                markFraudulent();
                cout << "Card marked as fraudulent due to multiple failed attempts." << endl;
                sendFraudReport();
            }
            return false;
        }
    }

    void markFraudulent()
    {
        isFraudulent = true;
    }

    bool getFraudulentStatus() const
    {
        return isFraudulent;
    }

    void sendFraudReport() const
    {
        cout << "Fraud alert: A report has been sent to the banking employee for card number "
             << cardNumber << "." << endl;
    }
};

// UserClient Class
class UserClient
{
private:
    string userName;
    string userAddress;
    string userID;
    string password;
    double balance;
    double dailyWithdrawalLimit;
    AccountType *accountType;
    bool hasCompanyAccount;
    vector<Card> cards;

public:
    // Constructor
    UserClient(string name, string address, string id, string pass, AccountType *type, bool companyAccount = false)
            : userName(name), userAddress(address), userID(id), password(pass),
              accountType(type), hasCompanyAccount(companyAccount), balance(0.0)
    {
        dailyWithdrawalLimit = accountType->getDailyWithdrawalLimit();
    }

    // Add a new card to the user account
    void addCard(const string &cardNumber, const string &pin)
    {
        cards.emplace_back(cardNumber, pin);
        ofstream outFile("cards.txt", ios::app);
        if (outFile.is_open())
        {
            outFile << userID << "| " << cardNumber << "| " << pin << endl;
            outFile.close();
        }
        else
        {
            cerr << "Error: Unable to save card information!" << endl;
        }
    }

    // Deposit money to the user's balance
    void deposit(double amount)
    {
        if (amount <= 0)
        {
            cout << "Deposit amount must be positive." << endl;
            return;
        }
        balance += amount;
        cout << "Deposited: " << amount << ". New balance: " << balance << endl;
    }

    // Withdraw money from the user's balance
    void withdraw(double amount)
    {
        if (amount <= 0)
        {
            cout << "Withdrawal amount must be positive." << endl;
            return;
        }
        if (amount > balance)
        {
            cout << "Insufficient funds." << endl;
            return;
        }
        if (amount > dailyWithdrawalLimit)
        {
            cout << "Exceeds daily withdrawal limit." << endl;
            return;
        }
        balance -= amount;
        cout << "Withdrawn: " << amount << ". Remaining balance: " << balance << endl;
    }

    // Transfer funds to another user or company
    void transferFunds(string targetUserID, double amount)
    {
        if (amount <= 0)
        {
            cout << "Transfer amount must be positive." << endl;
            return;
        }
        if (amount > balance)
        {
            cout << "Insufficient funds for transfer." << endl;
            return;
        }
        balance -= amount;
        cout << "Transferred " << amount << " to User ID: " << targetUserID << ". Remaining balance: " << balance << endl;
    }

    // View the current balance
    void viewBalance() const
    {
        cout << "Current balance: " << balance << endl;
    }

    // Save the user data to a file
    void saveToFile()
    {
        ofstream outFile(userID + "_data.txt");
        if (!outFile)
        {
            cout << "Failed to save user data." << endl;
            return;
        }
        outFile << "User Name: " << userName << endl;
        outFile << "User Address: " << userAddress << endl;
        outFile << "User ID: " << userID << endl;
        outFile << "Balance: " << balance << endl;
        outFile << "Daily Withdrawal Limit: " << dailyWithdrawalLimit << endl;
        outFile << "Has Company Account: " << (hasCompanyAccount ? "Yes" : "No") << endl;
        outFile << "Cards:" << endl;
        for (const auto &card : cards)
        {
            outFile << "  Card Number: " << card.getCardNumber() << endl;
        }
        outFile.close();
        cout << "User data saved successfully." << endl;
    }

    // Set the flag for company account availability
    void setCompanyAccount(bool hasAccount)
    {
        hasCompanyAccount = hasAccount;
    }

    // Check if the user has a company account
    bool hasCompany() const
    {
        return hasCompanyAccount;
    }
};

// User Class
class User
{
private:
    static int userCount;

    // Helper function to validate alphabetic input
    bool isValidName(const string &str)
    {
        for (char c : str)
        {
            if (!isalpha(c) && c != ' ')
            {
                return false;
            }
        }
        return true;
    }

    // Helper function to validate CNIC format
    bool isValidCNIC(const string &str)
    {
        if (str.length() > 15)
            return false;
        for (char c : str)
        {
            if (!isdigit(c) && c != '-')
                return false;
        }
        return true;
    }

public:
    User() {}

    void registerUser()
    {
        int userID = ++userCount;
        string name, CNIC, address, password;
        int phone, loginID;
        double dailyWithdrawalLimit;

        AccountType *accountType = nullptr; // To store the appropriate account type

        cout << "\nEnter Name (alphabets only): ";
        cin.ignore();
        while (true)
        {
            getline(cin, name);
            if (isValidName(name))
                break;
            cout << "Invalid name. Please enter alphabets only: ";
        }

        cout << "Enter CNIC (15 characters max, numbers and '-'): ";
        while (true)
        {
            cin >> CNIC;
            if (isValidCNIC(CNIC))
                break;
            cout << "Invalid CNIC. Please use numbers and '-' only (max 15 characters): ";
        }

        cout << "Enter Address: ";
        cin.ignore();
        getline(cin, address);

        cout << "Enter Phone (numbers only): ";
        while (!(cin >> phone) || phone <= 0)
        {
            cout << "Invalid phone number. Please enter a valid number: ";
            cin.clear();
        }

        cout << "Enter Login ID (numbers only): ";
        while (!(cin >> loginID) || loginID <= 0)
        {
            cout << "Invalid Login ID. Please enter a valid number: ";
            cin.clear();
        }

        cout << "Enter Password: ";
        cin >> password;
        string confirmPassword;
        cout << "Confirm Password: ";
        cin >> confirmPassword;

        while (password != confirmPassword)
        {
            cout << "Passwords do not match. Enter Password again: ";
            cin >> password;
            cout << "Confirm Password: ";
            cin >> confirmPassword;
        }

        cout << "Enter Daily Withdrawal Limit: ";
        while (true)
        {
            if (!(cin >> dailyWithdrawalLimit) || dailyWithdrawalLimit <= 0)
            {
                cout << "Invalid amount. Please enter a valid daily withdrawal limit: ";
                cin.clear();
            }
            else
            {
                break;
            }
        }

        // Determine the account type based on the withdrawal limit
        if (dailyWithdrawalLimit < 100000)
        {
            accountType = new Bronze();
        }
        else if (dailyWithdrawalLimit >= 100000 && dailyWithdrawalLimit <= 500000)
        {
            accountType = new Gold();
        }
        else if (dailyWithdrawalLimit > 500000 && dailyWithdrawalLimit < 20000000)
        {
            accountType = new Business();
        }
        else
        {
            cout << "The withdrawal limit exceeds the maximum allowed. Please try again.\n";
            return;
        }

        // Save user data to file
        ofstream outFile("users.txt", ios::app);
        if (outFile)
        {
            if (isFileEmpty())
            {
                outFile << "UserID|Name|Address|CNIC|Phone|LoginID|Password|AccountType|DailyWithdrawalLimit\n";
            }
            outFile << userID << "|"
                    << name << "|"
                    << address << "|"
                    << CNIC << "|"
                    << phone << "|"
                    << loginID << "|"
                    << password << "|"
                    << accountType->getTypeName() << "|"
                    << accountType->getDailyWithdrawalLimit() << "\n"; // Save the account type and withdrawal limit
            outFile.close();
            cout << "\nUser registered successfully! Your User ID is: " << userID << "\n";
        }
        else
        {
            cout << "\nError: Could not save user data.\n";
        }
    }

    bool isFileEmpty()
    {
        ifstream inFile("users.txt");
        return inFile.peek() == ifstream::traits_type::eof();
    }

    UserClient *loginUser()
    {
        int inputLoginID;
        string inputPassword;

        cout << "Enter Login ID: ";
        cin >> inputLoginID;

        cout << "Enter Password: ";
        cin >> inputPassword;

        ifstream inFile("users.txt");
        if (!inFile || isFileEmpty())
        {
            cout << "No users registered yet.\n";
            return nullptr;
        }

        string line;
        bool found = false;

        // Read header line and find column indices
        getline(inFile, line); // Skip the header row

        while (getline(inFile, line))
        {
            stringstream ss(line);
            vector<string> columns;
            string value;

            while (getline(ss, value, '|'))
            {
                columns.push_back(trim(value)); // Split by delimiter and trim
            }

            if (columns.size() >= 9)
            {
                int storedLoginID = stoi(columns[5]);
                string storedPassword = columns[6];

                if (storedLoginID == inputLoginID && storedPassword == inputPassword)
                {
                    found = true;

                    // Extract user details
                    string userName = columns[1];
                    string userAddress = columns[2];
                    string userID = columns[0];
                    double accountBalance = stod(columns[7]);
                    string accountTypeStr = columns[8];

                    // Create the appropriate AccountType object
                    AccountType *accountType = nullptr;
                    if (accountTypeStr == "Bronze")
                    {
                        accountType = new Bronze();
                    }
                    else if (accountTypeStr == "Gold")
                    {
                        accountType = new Gold();
                    }
                    else if (accountTypeStr == "Business")
                    {
                        accountType = new Business();
                    }
                    else
                    {
                        accountType = new Bronze(); // Default to Bronze
                    }

                    // Create and return a UserClient object
                    return new UserClient(userName, userAddress, userID, storedPassword, accountType);
                }
            }
        }

        if (!found)
        {
            cout << "Invalid login ID or password. Please try again.\n";
        }

        return nullptr;
    }
};

int User::userCount = 0;

void displayRegularUserMenu(UserClient *regularUser)
{
    int choice;
    do
    {
        cout << "\n=== Regular User Menu ===\n";
        cout << "1. Deposit Money\n";
        cout << "2. Withdraw Money\n";
        cout << "3. View Balance\n";
        cout << "4. Logout\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
            {
                double amount;
                cout << "Enter Deposit Amount: ";
                cin >> amount;
                regularUser->deposit(amount);
                break;
            }
            case 2:
            {
                double amount;
                cout << "Enter Withdrawal Amount: ";
                cin >> amount;
                regularUser->withdraw(amount);
                break;
            }
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
    cout << "Enter Company ID: ";
    cin >> companyID;
    cout << "Enter Company Name: ";
    cin.ignore(); // ignore the newline character left in the input buffer
    getline(cin, companyName);
    cout << "Enter Company Address: ";
    getline(cin, companyAddress);
    cout << "Enter Company Tax Number: ";
    cin >> companyTaxNumber;
    cout << "Enter Company User ID: ";
    cin >> companyUserID;
    cout << "Enter Company Password: ";
    cin >> companyPassword;

    // Save the company information to the "companies.txt" file
    ofstream outFile("companies.txt", ios::app);
    if (outFile.is_open())
    {
        outFile << companyID << " | " << companyName << " | " << companyAddress << " | " << companyTaxNumber << " | " << companyUserID << " | " << companyPassword << " | " << accountBalance << endl;
        outFile.close();
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

// Function to display the UserClient menu
void displayUserClientMenu(UserClient *userClient)
{
    int choice;
    do
    {
        cout << "\n=== User Client Menu ===\n";
        cout << "1. Add Card\n";
        cout << "2. Deposit Money\n";
        cout << "3. Withdraw Money\n";
        cout << "4. Transfer Funds\n";
        cout << "5. View Balance\n";
        cout << "6. Save User Data\n";
        cout << "7. Logout\n";
        cout << "8. Regular User Login\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
            {
                string cardNumber, pin;

                // Initialize random generator and distribution once
                static random_device rd;                                                               // Random device
                static mt19937 generator(rd());                                                        // Mersenne Twister engine
                static uniform_int_distribution<int> distribution(1000000000000000, 9999999999999999); // 4-digit random numbers

                // Generate a random card number (4 digits)
                cardNumber = to_string(distribution(generator));

                // Prompt the user to enter a PIN
                cout << "Enter PIN for card " << cardNumber << ": ";
                cin >> pin;

                // Add the card to the user's account
                userClient->addCard(cardNumber, pin);

                break;
            }
            case 2:
            {
                double amount;
                cout << "Enter Deposit Amount: ";
                cin >> amount;
                userClient->deposit(amount);
                break;
            }
            case 3:
            {
                double amount;
                cout << "Enter Withdrawal Amount: ";
                cin >> amount;
                userClient->withdraw(amount);
                break;
            }
            case 4:
            {
                string targetUserID;
                double amount;
                cout << "Enter Target User ID: ";
                cin >> targetUserID;
                cout << "Enter Transfer Amount: ";
                cin >> amount;
                userClient->transferFunds(targetUserID, amount);
                break;
            }
            case 5:
                userClient->viewBalance();
                break;
            case 6:
                userClient->saveToFile();
                break;
            case 7:
                cout << "Logging out...\n";
                break;
            case 8:
            {
                string userID, password;
                cout << "Enter User ID: ";
                cin >> userID;
                cout << "Enter Password: ";
                cin >> password;

                // Verify the user's credentials
                if (verifyUserCredentials(userID, password))
                {
                    // Create a new UserClient object for the regular user
                    UserClient *regularUser = new UserClient(userID, "", "", password, nullptr, false);

                    // Display the regular user's menu
                    displayRegularUserMenu(regularUser);
                }
                else
                {
                    cout << "Invalid user ID or password.\n";
                }

                break;
            }
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 7);
}

class Transaction
{
private:
    string transactionID;
    string transactionDate;
    double amount;
    string transactionType;
    string targetUserID;
    Card *cardUsed;

public:
    // Constructor
    Transaction(string id, string type, double amt, string date, Card *card = nullptr, string targetID = "")
            : transactionID(id), transactionType(type), amount(amt), transactionDate(date), cardUsed(card), targetUserID(targetID) {}

    // Log transaction to the file
    void logTransaction()
    {
        ofstream outFile("transactions.txt", ios::app);
        if (outFile.is_open())
        {
            outFile << transactionDate << ", " << transactionID << ", " << amount
                    << ", " << transactionType;
            if (!targetUserID.empty())
            {
                outFile << ", " << targetUserID;
            }
            outFile << endl;
            outFile.close();
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
        if (amount > balance)
        {
            cout << "Insufficient balance!" << endl;
            return false;
        }
        if (amount > dailyLimit)
        {
            cout << "Transaction exceeds daily withdrawal limit!" << endl;
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
        if (amount > senderBalance)
        {
            cout << "Insufficient balance!" << endl;
            return false;
        }
        if (amount > dailyLimit)
        {
            cout << "Transaction exceeds daily withdrawal limit!" << endl;
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
        return to_string(1900 + ltm->tm_year) + "-" +
               to_string(1 + ltm->tm_mon) + "-" +
               to_string(ltm->tm_mday);
    }

    // Static function to search transactions by user ID
    static void searchTransactionsByUserID(const string &userID)
    {
        ifstream inFile("transactions.txt");
        string line;
        bool found = false;

        if (inFile.is_open())
        {
            while (getline(inFile, line))
            {
                // Split line based on commas (CSV format)
                size_t pos = line.find(",");
                string date = line.substr(0, pos);
                line.erase(0, pos + 2); // Remove date and comma

                pos = line.find(",");
                string transID = line.substr(0, pos);
                line.erase(0, pos + 2); // Remove transaction ID and comma

                pos = line.find(",");
                string amountStr = line.substr(0, pos);
                line.erase(0, pos + 2); // Remove amount and comma

                pos = line.find(",");
                string type = line.substr(0, pos);
                line.erase(0, pos + 2); // Remove transaction type and comma

                // Now check the target user ID
                string targetUserID = line;

                // If this is a matching transaction for the userID, print it
                if (line.find(userID) != string::npos)
                {
                    cout << "Transaction found: " << date << ", " << transID << ", " << amountStr
                         << ", " << type << ", Target User ID: " << targetUserID << endl;
                    found = true;
                }
            }
            if (!found)
            {
                cout << "No transactions found for User ID: " << userID << endl;
            }
            inFile.close();
        }
        else
        {
            cerr << "Error: Unable to open transactions file!" << endl;
        }
    }
};

// CompanyClient Class
class CompanyClient
{
private:
    string companyName;
    string companyAddress;
    string taxNumber;
    int companyAccID;
    string password;
    double balance;
    double dailyWithdrawalLimit;
    vector<Card> cards;

public:
    CompanyClient(string name, string address, string tax, int accID, string pass, double limit)
            : companyName(name), companyAddress(address), taxNumber(tax), companyAccID(accID), password(pass),
              balance(0), dailyWithdrawalLimit(limit) {}

    // Add card to the company account
    void addCard(const string &cardNumber, const string &pin)
    {
        cards.emplace_back(cardNumber, pin);
        ofstream outFile("cards.txt", ios::app);
        if (outFile.is_open())
        {
            outFile << companyAccID << "| " << cardNumber << "| " << pin << endl;
            outFile.close();
        }
        else
        {
            cerr << "Error: Unable to save card information!" << endl;
        }
    }

    // Retrieve the balance of another user (simulate database query)
    double getReceiverBalance(string targetUserID)
    {
        // TODO: Implement actual database or file query logic
        ifstream inFile("balances.txt");
        string line;
        double receiverBalance = 0.0;

        if (inFile.is_open())
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
        else
        {
            cerr << "Error: Unable to open balances file!" << endl;
        }

        return receiverBalance;
    }

    // Deposit money to the account
    void deposit(double amount)
    {
        if (amount <= 0)
        {
            cerr << "Error: Deposit amount must be positive!" << endl;
            return;
        }

        balance += amount;
        cout << "Deposited " << amount << " PKR successfully." << endl;
        // Log the transaction
        Transaction transaction("TXN001", "Deposit", amount, Transaction::getCurrentDate());
        transaction.deposit(balance);
    }

    // Withdraw money from the account
    void withdraw(double amount)
    {
        if (amount > dailyWithdrawalLimit)
        {
            cerr << "Error: Exceeds daily withdrawal limit!" << endl;
            return;
        }

        if (amount > balance)
        {
            cerr << "Error: Insufficient funds!" << endl;
            return;
        }

        balance -= amount;
        cout << "Withdrawn " << amount << " PKR successfully." << endl;
        // Log the transaction
        Transaction transaction("TXN002", "Withdraw", amount, Transaction::getCurrentDate());
        transaction.withdraw(balance, dailyWithdrawalLimit);
    }

    // Transfer funds to another user
    void transferFunds(string targetUserID, double amount)
    {
        if (amount <= 0)
        {
            cerr << "Error: Transfer amount must be positive!" << endl;
            return;
        }

        if (amount > balance)
        {
            cerr << "Error: Insufficient funds for transfer!" << endl;
            return;
        }

        double receiverBalance = getReceiverBalance(targetUserID);
        if (receiverBalance < 0)
        {
            cerr << "Error: Target user not found!" << endl;
            return;
        }

        balance -= amount;
        receiverBalance += amount;

        // Update the receiver's balance (simulate saving to a database)
        ofstream outFile("balances.txt", ios::app);
        if (outFile.is_open())
        {
            outFile << targetUserID << " " << receiverBalance << endl;
            outFile.close();
        }
        else
        {
            cerr << "Error: Unable to update receiver's balance!" << endl;
        }

        cout << "Transferred " << amount << " PKR to user ID: " << targetUserID << " successfully." << endl;
        // Log the transaction
        Transaction transaction("TXN003", "Transfer", amount, Transaction::getCurrentDate(), nullptr, targetUserID);
        transaction.transfer(balance, dailyWithdrawalLimit, receiverBalance);
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
        if (outFile.is_open())
        {
            outFile << companyName << "| " << companyAddress << "| " << taxNumber
                    << "| " << companyAccID << "| " << password << "| " << fixed << setprecision(2) << balance << endl;
            outFile.close();
        }
        else
        {
            cerr << "Error: Unable to save company information!" << endl;
        }
    }

    // Login function for authentication
    bool login(const string &companyID, const string &companyPass)
    {
        ifstream inFile("companies.txt");
        string line;
        bool loginSuccessful = false;

        if (inFile.is_open())
        {
            while (getline(inFile, line))
            {
                istringstream iss(line);
                string fileCompanyName, fileCompanyAddress, fileTaxNumber, fileCompanyID, filePassword;
                double fileBalance;

                getline(iss, fileCompanyName, '|');
                getline(iss, fileCompanyAddress, '|');
                getline(iss, fileTaxNumber, '|');
                getline(iss, fileCompanyID, '|');
                getline(iss, filePassword, '|');
                iss >> fileBalance;

                if (fileCompanyID == companyID && filePassword == companyPass)
                {
                    cout << "Login successful for company: " << fileCompanyName << endl;
                    loginSuccessful = true;
                    break;
                }
            }
            inFile.close();
        }
        else
        {
            cerr << "Error: Unable to open companies file!" << endl;
        }

        if (!loginSuccessful)
        {
            cout << "Invalid company ID or password.\n";
        }

        return loginSuccessful;
    }
};

class BankingEmployee
{
private:
    string employeeID;
    string password;

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
        else
        {
            cout << "Invalid credentials!" << endl;
            return false;
        }
    }

    void viewClientAccounts()
    {
        ifstream inFile("Companies.txt");
        if (inFile.is_open())
        {
            string line;
            cout << "Client Accounts:\n";
            while (getline(inFile, line))
            {
                cout << line << endl;
            }
            inFile.close();
        }
        else
        {
            cerr << "Error: Unable to read client accounts!" << endl;
        }
    }

    bool isEmployeeOfCompany(int userID)
    {
        ifstream inFile("companies_employees.txt");
        if (inFile.is_open())
        {
            string line;
            while (getline(inFile, line))
            {
                stringstream ss(line);
                int clientID, companyID;
                ss >> clientID >> companyID;

                if (clientID == userID)
                {
                    return true;
                }
            }
            inFile.close();
        }
        else
        {
            cerr << "Error: Unable to read employee data!" << endl;
        }
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
        if (inFile.is_open())
        {
            string line;
            cout << "Transaction history for account " << accountID << ":\n";
            while (getline(inFile, line))
            {
                if (line.find(accountID) != string::npos)
                {
                    cout << line << endl;
                }
            }
            inFile.close();
        }
        else
        {
            cerr << "Error: Unable to read transaction history!" << endl;
        }
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
    BankingEmployee employee("emp001", "empPass123");                                                  // Example employee login
    CompanyClient companyClient("TechCorp", "123 Tech St.", "TX12345", 1001, "companyPass123", 50000); // Example company account
    User user;                                                                                         // Instance of the User class for registering and logging in
    int choice;

    // Function to display the main menu for users
    auto displayMainMenu = []()
    {
        cout << "\n=== Main Menu ===\n";
        cout << "1. Register Regular Account\n";
        cout << "2. Register Company Account\n";
        cout << "3. Login\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
    };

    // Function to display the login menu
    auto displayLoginMenu = []()
    {
        cout << "\n=== Login Menu ===\n";
        cout << "1. Login as Regular User\n";
        cout << "2. Login as Banking Employee\n";
        cout << "3. Login as Company Client\n";
        cout << "4. Go Back\n";
        cout << "Enter your choice: ";
    };

    // Function to display the Banking Employee menu
    auto displayEmployeeMenu = [&employee]()
    {
        cout << "\n=== Banking Employee Menu ===\n";
        cout << "1. View Client Accounts\n";
        cout << "2. Approve Account\n";
        cout << "3. Reject Account\n";
        cout << "4. View Transaction History\n";
        cout << "5. Freeze Account\n";
        cout << "6. Close Account\n";
        cout << "7. Logout\n";
        cout << "Enter your choice: ";
    };

    // Function to display the Company Client menu
    auto displayCompanyClientMenu = [&companyClient]()
    {
        cout << "\n=== Company Client Menu ===\n";
        cout << "1. Deposit\n";
        cout << "2. Withdraw\n";
        cout << "3. Transfer Funds\n";
        cout << "4. View Balance\n";
        cout << "5. Logout\n";
        cout << "Enter your choice: ";
    };

    // Function to display the Regular User menu
    auto displayUserClientMenu = []()
    {
        cout << "\n=== User Client Menu ===\n";
        cout << "1. View Balance\n";
        cout << "2. Transfer Funds\n";
        cout << "3. Logout\n";
        cout << "Enter your choice: ";
    };

    // Function to handle company registration
    auto displayCompanyRegistrationMenu = []()
    {
        string companyID, companyName, companyAddress, companyTaxNumber, companyUserID, companyPassword;
        double accountBalance = 0.0;

        cout << "\n=== Company Registration Menu ===\n";
        cout << "Enter Company ID: ";
        cin >> companyID;
        cout << "Enter Company Name: ";
        cin.ignore();
        getline(cin, companyName);
        cout << "Enter Company Address: ";
        getline(cin, companyAddress);
        cout << "Enter Company Tax Number: ";
        cin >> companyTaxNumber;
        cout << "Enter Company User ID: ";
        cin >> companyUserID;
        cout << "Enter Company Password: ";
        cin >> companyPassword;

        // Save the company information to the "companies.txt" file
        ofstream outFile("companies.txt", ios::app);
        if (outFile.is_open())
        {
            outFile << companyID << ", " << companyName << ", " << companyAddress << ", " << companyTaxNumber << ", " << companyUserID << ", " << companyPassword << ", " << accountBalance << endl;
            outFile.close();
            cout << "Company registered successfully.\n";
        }
        else
        {
            cout << "Error: Unable to save company information.\n";
        }
    };

    do
    {
        displayMainMenu();
        cin >> choice;

        // Validate user input
        if (cin.fail() || choice < 1 || choice > 4)
        {
            cout << "Invalid choice. Please enter a number between 1 and 4.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice)
        {
            case 1:
            { // Register Regular Account
                cout << "Registering regular user account...\n";
                user.registerUser(); // Registering a user account
                break;
            }
            case 2:
            { // Register Company Account
                displayCompanyRegistrationMenu();
                break;
            }
            case 3:
            { // Login
                int loginChoice;
                displayLoginMenu();
                cin >> loginChoice;

                // Validate login choice
                if (cin.fail() || loginChoice < 1 || loginChoice > 4)
                {
                    cout << "Invalid choice. Please enter a number between 1 and 4.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    continue;
                }

                switch (loginChoice)
                {
                    case 1:
                    { // Login as Regular User
                        UserClient *userClient = user.loginUser();
                        if (userClient)
                        {
                            int userChoice;
                            do
                            {
                                displayUserClientMenu();
                                cin >> userChoice;

                                if (cin.fail() || userChoice < 1 || userChoice > 3)
                                {
                                    cout << "Invalid choice. Please enter a valid option.\n";
                                    cin.clear();
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                    continue;
                                }

                                switch (userChoice)
                                {
                                    case 1:
                                        userClient->viewBalance(); // Assume UserClient has a viewBalance function
                                        break;
                                    case 2:
                                    {
                                        double transferAmount;
                                        cout << "Enter transfer amount: ";
                                        cin >> transferAmount;
                                        string targetUserID;
                                        cout << "Enter target user ID: ";
                                        cin >> targetUserID;
                                        // Create a transaction and transfer funds
                                        Transaction trans("T003", "Transfer", transferAmount, Transaction::getCurrentDate(), nullptr, targetUserID);
                                        userClient->transferFunds(targetUserID, transferAmount); // Transfer funds
                                        trans.logTransaction();                                  // Log the transaction to file
                                        break;
                                    }
                                    case 3:
                                        cout << "Logging out...\n";
                                        break;
                                    default:
                                        cout << "Invalid option.\n";
                                }
                            } while (userChoice != 3);
                            delete userClient; // Clean up memory after logout
                        }
                        break;
                    }
                    case 2:
                    { // Login as Banking Employee
                        string empID, empPass;
                        cout << "Enter employee ID: ";
                        cin >> empID;
                        cout << "Enter password: ";
                        cin >> empPass;

                        if (employee.login(empID, empPass))
                        {
                            int empChoice;
                            do
                            {
                                displayEmployeeMenu();
                                cin >> empChoice;

                                if (cin.fail() || empChoice < 1 || empChoice > 7)
                                {
                                    cout << "Invalid choice. Please enter a valid number.\n";
                                    cin.clear();
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                    continue;
                                }

                                switch (empChoice)
                                {
                                    case 1:
                                        employee.viewClientAccounts();
                                        break;
                                    case 2:
                                    {
                                        string accountID;
                                        cout << "Enter account ID to approve: ";
                                        cin >> accountID;
                                        employee.approveAccount(accountID);
                                        break;
                                    }
                                    case 3:
                                    {
                                        string accountID;
                                        cout << "Enter account ID to reject: ";
                                        cin >> accountID;
                                        employee.rejectAccount(accountID);
                                        break;
                                    }
                                    case 4:
                                    {
                                        string accountID;
                                        cout << "Enter account ID to view transactions: ";
                                        cin >> accountID;
                                        employee.viewTransactionHistory(accountID);
                                        break;
                                    }
                                    case 5:
                                    {
                                        string accountID;
                                        cout << "Enter account ID to freeze: ";
                                        cin >> accountID;
                                        employee.freezeAccount(accountID);
                                        break;
                                    }
                                    case 6:
                                    {
                                        string accountID;
                                        cout << "Enter account ID to close: ";
                                        cin >> accountID;
                                        employee.closeAccount(accountID);
                                        break;
                                    }
                                    case 7:
                                        cout << "Logging out...\n";
                                        break;
                                    default:
                                        cout << "Invalid option.\n";
                                }
                            } while (empChoice != 7);
                        }
                        break;
                    }
                    case 3:
                    { // Login as Company Client
                        string companyID, companyPass;
                        cout << "Enter company ID: ";
                        cin >> companyID;
                        cout << "Enter password: ";
                        cin >> companyPass;

                        if (companyClient.login(companyID, companyPass))
                        {
                            int companyChoice;
                            do
                            {
                                displayCompanyClientMenu();
                                cin >> companyChoice;

                                if (cin.fail() || companyChoice < 1 || companyChoice > 5)
                                {
                                    cout << "Invalid choice. Please enter a valid option.\n";
                                    cin.clear();
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                    continue;
                                }

                                switch (companyChoice)
                                {
                                    case 1:
                                    { // Deposit
                                        double depositAmount;
                                        cout << "Enter deposit amount: ";
                                        cin >> depositAmount;
                                        // Create a transaction and deposit funds
                                        Transaction trans("T001", "Deposit", depositAmount, Transaction::getCurrentDate());
                                        companyClient.deposit(depositAmount); // Company client's deposit function
                                        trans.logTransaction();               // Log the transaction to file
                                        break;
                                    }
                                    case 2:
                                    { // Withdraw
                                        double withdrawAmount;
                                        cout << "Enter withdrawal amount: ";
                                        cin >> withdrawAmount;
                                        // Create a transaction and withdraw funds
                                        Transaction trans("T002", "Withdraw", withdrawAmount, Transaction::getCurrentDate());
                                        companyClient.withdraw(withdrawAmount); // Company client's withdrawal function
                                        trans.logTransaction();                 // Log the transaction to file
                                        break;
                                    }
                                    case 3:
                                    { // Transfer Funds
                                        double transferAmount;
                                        cout << "Enter transfer amount: ";
                                        cin >> transferAmount;
                                        string targetUserID;
                                        cout << "Enter target user ID: ";
                                        cin >> targetUserID;
                                        // Create a transaction and transfer funds
                                        Transaction trans("T003", "Transfer", transferAmount, Transaction::getCurrentDate(), nullptr, targetUserID);
                                        companyClient.transferFunds(targetUserID, transferAmount); // Transfer funds
                                        trans.logTransaction();                                    // Log the transaction to file
                                        break;
                                    }
                                    case 4: // View Balance
                                        companyClient.viewBalance();
                                        break;
                                    case 5: // Logout
                                        cout << "Logging out...\n";
                                        break;
                                    default:
                                        cout << "Invalid option.\n";
                                }
                            } while (companyChoice != 5);
                        }
                        break;
                    }
                    case 4:
                        cout << "Going back to main menu...\n";
                        break;

                    default:
                        cout << "Invalid choice. Please enter a number between 1 and 4.\n";
                }
                break;
            }
            case 4:
                cout << "Exiting the program. Goodbye!\n";
                break;

            default:
                cout << "Unknown error occurred.\n";
        }
    } while (choice != 4);

    return 0;
}