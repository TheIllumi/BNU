#ifndef CARD_H
#define CARD_H

#include <string>
using namespace std;

class Card
{
private:
    string cardNumber;
    string PIN;
    bool isFraudulent;
    int failedAttempts;

public:
    // Constructor
    Card(string cardNo, string pin);

    // Getter for card number
    string getCardNumber() const;

    // Validate the PIN
    bool validatePIN(const string &pin);

    // Mark the card as fraudulent
    void markFraudulent();

    // Get fraudulent status
    bool getFraudulentStatus() const;

    // Send a fraud report
    void sendFraudReport() const;
};

#endif // CARD_H