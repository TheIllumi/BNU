#include "User.h"

// Initialize static member
int User::userCount = 0;

// Constructor
User::User() : userID(0), phone(0), loginID(0), accountBalance(0.0) {}

// Helper function to validate alphabetic input
bool User::isValidName(const string &str)
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
bool User::isValidCNIC(const string &str)
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

void User::determineAccountType()
{
    if (accountBalance < 100000)
    {
        accountType = "Bronze";
    }
    else if (accountBalance >= 100000 && accountBalance < 500000)
    {
        accountType = "Gold";
    }
    else
    {
        accountType = "Business";
    }
}

// Helper function to trim leading and trailing whitespaces
string User::trim(const string &str)
{
    size_t start = str.find_first_not_of(" \t");
    size_t end = str.find_last_not_of(" \t");
    return (start == string::npos || end == string::npos) ? "" : str.substr(start, end - start + 1);
}

// Helper function to check if a file is empty
bool User::isFileEmpty()
{
    ifstream inFile("users.txt");
    return inFile.peek() == ifstream::traits_type::eof();
}

// Function to register a user
void User::registerUser()
{
    userID = ++userCount;

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

    cout << "Enter Initial Account Balance: ";
    while (!(cin >> accountBalance) || accountBalance < 0)
    {
        cout << "Invalid balance. Please enter a valid balance: ";
        cin.clear();
    }

    determineAccountType();
    cout << "Your account type is: " << accountType << "\n";

    ofstream outFile("users.txt", ios::app);
    if (outFile)
    {
        // Add column headers if file is empty
        if (isFileEmpty())
        {
            outFile << "UserID|Name|Address|CNIC|Phone|LoginID|Password|AccountBalance|AccountType\n";
        }

        // Write user details in a tabular format
        outFile << userID << "|"
                << name << "|"
                << address << "|"
                << CNIC << "|"
                << phone << "|"
                << loginID << "|"
                << password << "|"
                << accountBalance << "|"
                << accountType << "\n";

        outFile.close();
        cout << "\nUser registered successfully! Your User ID is: " << userID << "\n";
    }
    else
    {
        cout << "\nError: Could not save user data.\n";
    }
}

// Function to log in a user
void User::loginUser()
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
        return;
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

        if (columns.size() >= 7)
        {
            int storedLoginID = stoi(columns[5]);
            string storedPassword = columns[6];

            if (storedLoginID == inputLoginID && storedPassword == inputPassword)
            {
                found = true;
                break;
            }
        }
    }

    if (found)
    {
        cout << "Login successful!\n";
    }
    else
    {
        cout << "Invalid login ID or password. Please try again.\n";
    }
}
