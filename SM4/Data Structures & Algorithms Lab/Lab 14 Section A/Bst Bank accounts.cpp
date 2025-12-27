// Enhanced BST for storing and managing bank accounts
#include <iostream>
using namespace std;

class BankBST
{
private:
    // Definition of a tree node with account ID and balance
    struct TreeNode
    {
        int id;
        double balance;
        TreeNode *left;
        TreeNode *right;
    };

    TreeNode *root;

    // Helper function to insert a new node into the BST
    void insert(TreeNode *&node, int id, double balance)
    {
        if (!node)
        {
            node = new TreeNode{id, balance, nullptr, nullptr};
        }
        else if (id < node->id)
        {
            insert(node->left, id, balance);
        }
        else if (id > node->id)
        {
            insert(node->right, id, balance);
        }
        else
        {
            cout << "Account already exists.\n";
        }
    }

    // Recursive search for an account by ID
    TreeNode *search(TreeNode *node, int id) const
    {
        if (!node || node->id == id)
            return node;
        else if (id < node->id)
            return search(node->left, id);
        else
            return search(node->right, id);
    }

    // Find the account with the maximum balance
    void findMaxBalance(TreeNode *node, TreeNode *&maxNode) const
    {
        if (!node)
            return;
        if (!maxNode || node->balance > maxNode->balance)
            maxNode = node;
        findMaxBalance(node->left, maxNode);
        findMaxBalance(node->right, maxNode);
    }

    // Print accounts whose balances fall in a specified range
    void printInRange(TreeNode *node, double minB, double maxB) const
    {
        if (!node)
            return;
        printInRange(node->left, minB, maxB);
        if (node->balance >= minB && node->balance <= maxB)
            cout << "ID: " << node->id << ", Balance: " << node->balance << endl;
        printInRange(node->right, minB, maxB);
    }

    // Count accounts based on thresholds (e.g. high balance, zero balance)
    void countThresholds(TreeNode *node, double threshold, int &high, int &zero) const
    {
        if (!node)
            return;
        if (node->balance > threshold)
            high++;
        if (node->balance == 0)
            zero++;
        countThresholds(node->left, threshold, high, zero);
        countThresholds(node->right, threshold, high, zero);
    }

    // Accumulate total balance and count for average calculation
    void computeAverage(TreeNode *node, double &total, int &count) const
    {
        if (!node)
            return;
        total += node->balance;
        count++;
        computeAverage(node->left, total, count);
        computeAverage(node->right, total, count);
    }

    // Print accounts above or below the average balance
    void printAboveBelowAvg(TreeNode *node, double avg) const
    {
        if (!node)
            return;
        printAboveBelowAvg(node->left, avg);
        cout << "ID: " << node->id << ", Balance: " << node->balance;
        if (node->balance > avg)
            cout << " => Above Average\n";
        else
            cout << " => Below Average\n";
        printAboveBelowAvg(node->right, avg);
    }

public:
    // Constructor initializes root
    BankBST() : root(nullptr) {}

    // Insert a new account
    void insertAccount(int id, double balance)
    {
        insert(root, id, balance);
    }

    // Display account details by ID
    void searchAccount(int id) const
    {
        TreeNode *result = search(root, id);
        if (result)
            cout << "ID: " << result->id << ", Balance: " << result->balance << endl;
        else
            cout << "Account not found.\n";
    }

    // Deposit funds into an account
    void deposit(int id, double amount)
    {
        TreeNode *result = search(root, id);
        if (result)
        {
            result->balance += amount;
            cout << "Deposited. New balance: " << result->balance << endl;
        }
        else
            cout << "Account not found.\n";
    }

    // Withdraw funds from an account if balance is sufficient
    void withdraw(int id, double amount)
    {
        TreeNode *result = search(root, id);
        if (result)
        {
            if (result->balance >= amount)
            {
                result->balance -= amount;
                cout << "Withdrawn. New balance: " << result->balance << endl;
            }
            else
            {
                cout << "Insufficient balance.\n";
            }
        }
        else
            cout << "Account not found.\n";
    }

    // Transfer funds between two accounts
    void transferFunds(int senderId, int receiverId, double amount)
    {
        TreeNode *sender = search(root, senderId);
        TreeNode *receiver = search(root, receiverId);
        if (!sender || !receiver)
        {
            cout << "One or both accounts not found.\n";
            return;
        }
        if (sender->balance < amount)
        {
            cout << "Insufficient balance in sender's account.\n";
            return;
        }
        sender->balance -= amount;
        receiver->balance += amount;
        cout << "Transferred " << amount << " from ID " << senderId << " to ID " << receiverId << endl;
    }

    // Display the account with the highest balance
    void getMaxBalanceAccount() const
    {
        TreeNode *maxNode = nullptr;
        findMaxBalance(root, maxNode);
        if (maxNode)
            cout << "Max Balance => ID: " << maxNode->id << ", Balance: " << maxNode->balance << endl;
    }

    // Display all accounts in a specific balance range
    void getAccountsInRange(double minB, double maxB) const
    {
        printInRange(root, minB, maxB);
    }

    // Count accounts above a balance threshold and accounts with zero balance
    void countAccounts(double threshold) const
    {
        int high = 0, zero = 0;
        countThresholds(root, threshold, high, zero);
        cout << "Accounts with balance > " << threshold << ": " << high << endl;
        cout << "Accounts with zero balance: " << zero << endl;
    }

    // Calculate and print average balance and categorize accounts
    void averageBalanceReport() const
    {
        double total = 0;
        int count = 0;
        computeAverage(root, total, count);
        if (count == 0)
            return;
        double avg = total / count;
        cout << "Average Balance: " << avg << endl;
        printAboveBelowAvg(root, avg);
    }
};

// Sample main function for testing the BankBST functionality
int main()
{
    BankBST tree;
    tree.insertAccount(101, 5000);  // Add account with ID 101 and balance 5000
    tree.insertAccount(102, 15000); // Add account with ID 102 and balance 15000
    tree.insertAccount(103, 1000);  // Add account with ID 103 and balance 1000

    cout << "\n--- Search ---\n";
    tree.searchAccount(102); // Search for account 102

    cout << "\n--- Deposit ---\n";
    tree.deposit(101, 2000); // Deposit 2000 into account 101

    cout << "\n--- Withdraw ---\n";
    tree.withdraw(103, 500); // Withdraw 500 from account 103

    cout << "\n--- Transfer ---\n";
    tree.transferFunds(101, 102, 3000); // Transfer 3000 from 101 to 102

    cout << "\n--- Max Balance ---\n";
    tree.getMaxBalanceAccount(); // Show account with maximum balance

    cout << "\n--- Accounts in Range (1000 to 16000) ---\n";
    tree.getAccountsInRange(1000, 16000); // Show accounts with balances in this range

    cout << "\n--- Count Accounts ---\n";
    tree.countAccounts(10000); // Count accounts with >10000 and with 0 balance

    cout << "\n--- Average Balance Report ---\n";
    tree.averageBalanceReport(); // Show average balance and categorize accounts

    return 0;
}