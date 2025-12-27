#include "Card.h"
#include <iostream>

using namespace std;

// Constructor
Card::Card(string cardNo, string pin)
    : cardNumber(cardNo), PIN(pin), isFraudulent(false), failedAttempts(0) {}

// Getter for card number
string Card::getCardNumber() const
{
    return cardNumber;
}

// Validate the PIN
bool Card::validatePIN(const string &pin)
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

// Mark the card as fraudulent
void Card::markFraudulent()
{
    isFraudulent = true;
}

// Get fraudulent status
bool Card::getFraudulentStatus() const
{
    return isFraudulent;
}

// Send a fraud report
void Card::sendFraudReport() const
{
    cout << "Fraud alert: A report has been sent to the banking employee for card number "
         << cardNumber << "." << endl;
}