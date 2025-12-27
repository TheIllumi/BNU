#include "AccountType.h"
#include "BankingEmployee.h"
#include "Card.h"
#include "CompanyClient.h"
#include "Transaction.h"
#include "User.h"
#include "UserClient.h"
#include "UserManager.h"
#include <iostream>
#include <vector>

using namespace std;

void displayInitialMenu()
{
    cout << "\n====== Welcome to the Bank ======" << endl;
    cout << "1. Sign Up" << endl;
    cout << "2. Log In" << endl;
    cout << "3. Exit" << endl;
    cout << "Select an option: ";
}

void displayBankingMenu()
{
    cout << "\n====== Banking Menu ======" << endl;
    cout << "1. Add Card to Your Account" << endl;
    cout << "2. Deposit Money" << endl;
    cout << "3. Withdraw Money" << endl;
    cout << "4. Transfer Funds" << endl;
    cout << "5. View Balance" << endl;
    cout << "6. Logout" << endl;
    cout << "Select an option: ";
}

int main()
{
    UserManager userManager;
    BankingEmployee employee("admin", "password123");

    int initialChoice;
    do
    {
        displayInitialMenu();
        cin >> initialChoice;

        switch (initialChoice)
        {
        case 1:
            userManager.registerUser();
            break;

        case 2:
        {
            string userID, password;
            cout << "Enter User ID: ";
            cin >> userID;
            cout << "Enter Password: ";
            cin >> password;

            if (userManager.loginUser(userID, password))
            {
                int bankingChoice;
                do
                {
                    displayBankingMenu();
                    cin >> bankingChoice;

                    switch (bankingChoice)
                    {
                    case 1:
                    {
                        string cardNumber, pin;
                        cout << "Enter Card Number: ";
                        cin >> cardNumber;
                        cout << "Enter Card PIN: ";
                        cin >> pin;

                        if (userManager.addCardToUser(userID, cardNumber, pin))
                            cout << "Card added successfully!" << endl;
                        else
                            cout << "Failed to add card!" << endl;
                        break;
                    }

                    case 2:
                    {
                        double amount;
                        cout << "Enter Deposit Amount: ";
                        cin >> amount;

                        if (userManager.depositToUser(userID, amount))
                            cout << "Deposit successful!" << endl;
                        else
                            cout << "Deposit failed!" << endl;
                        break;
                    }

                    case 3:
                    {
                        double amount;
                        cout << "Enter Withdrawal Amount: ";
                        cin >> amount;

                        if (userManager.withdrawFromUser(userID, amount))
                            cout << "Withdrawal successful!" << endl;
                        else
                            cout << "Insufficient funds or withdrawal failed!" << endl;
                        break;
                    }

                    case 4:
                    {
                        string receiverID;
                        double amount;
                        cout << "Enter Receiver User ID: ";
                        cin >> receiverID;
                        cout << "Enter Transfer Amount: ";
                        cin >> amount;

                        if (userManager.transferFunds(userID, receiverID, amount))
                            cout << "Transfer successful!" << endl;
                        else
                            cout << "Transfer failed!" << endl;
                        break;
                    }

                    case 5:
                        if (!userManager.viewUserBalance(userID))
                            cout << "Failed to retrieve balance!" << endl;
                        break;

                    case 6:
                        cout << "Logged out successfully!" << endl;
                        break;

                    default:
                        cout << "Invalid choice! Please try again." << endl;
                    }
                } while (bankingChoice != 6);
            }
            else
            {
                cout << "Login failed! Invalid credentials." << endl;
            }
            break;
        }

        case 3:
            cout << "Thank you for using the banking system. Goodbye!" << endl;
            break;

        default:
            cout << "Invalid choice! Please try again." << endl;
        }
    } while (initialChoice != 3);

    return 0;
}
