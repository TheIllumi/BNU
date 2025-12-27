#include <iostream>
#include <string>

using namespace std;

// Struct to store user profile information
struct UserProfile {
    string name;
    string email;
};

void DisplayConfirmation(string movie, int row, int seat, double cost);
void CancelBooking();
void ViewBookingHistory(string username);
void update_user_profile(UserProfile &profile);
double DisplayTicket(string movie, int row, int seat, double cost);

int main() {
    // Test the functions
    string movie = "The Matrix";
    int row = 5;
    int seat = 8;
    double cost = 12.50;

    DisplayConfirmation(movie, row, seat, cost);
    CancelBooking();

    string username = "john_doe";
    ViewBookingHistory(username);

    // Update user profile
    UserProfile user = {"John Doe", "john.doe@example.com"};
    update_user_profile(user);

    // Display updated profile
    cout << "\nUpdated Profile:\n";
    cout << "Name: " << user.name << endl;
    cout << "Email: " << user.email << endl;

    // Display ticket
    double totalCost = DisplayTicket(movie, row, seat, cost);
    cout << "Total cost of the ticket: $" << totalCost << endl;

    return 0;
}

void DisplayConfirmation(string movie, int row, int seat, double cost) {
    cout << "\nBooking Confirmation\n";
    cout << "---------------------\n";
    cout << "Movie: " << movie << endl;
    cout << "Row: " << row << endl;
    cout << "Seat: " << seat << endl;
    cout << "Total Cost: $" << cost << endl;
    cout << "Enjoy your movie!\n";
}

void CancelBooking() {
    cout << "\nBooking Cancellation\n";
    cout << "---------------------\n";
    cout << "Your booking has been successfully cancelled.\n";
    cout << "We hope to see you again soon.\n";
}

void ViewBookingHistory(string username) {
    cout << "\nBooking History for " << username << "\n";
    cout << "-----------------------------\n";

    // Static array to simulate booking history
    const int historySize = 3;
    string bookingHistory[historySize] = {
            "The Matrix - Row: 5, Seat: 8, Cost: $12.50",
            "Inception - Row: 3, Seat: 10, Cost: $10.00",
            "Interstellar - Row: 7, Seat: 4, Cost: $15.00"
    };

    // Display the booking history
    for(int i = 0; i < historySize; ++i) {
        cout << bookingHistory[i] << endl;
    }
}

void update_user_profile(UserProfile &profile) {
    cout << "\nUpdate User Profile\n";
    cout << "-------------------\n";
    cout << "Current Name: " << profile.name << endl;
    cout << "Enter new name: ";
    cin.ignore(); // to clear the buffer
    getline(cin, profile.name);

    cout << "Current Email: " << profile.email << endl;
    cout << "Enter new email: ";
    getline(cin, profile.email);

    cout << "Profile updated successfully!\n";
}

double DisplayTicket(string movie, int row, int seat, double cost) {
    cout << "\nTicket Details\n";
    cout << "--------------\n";
    cout << "Movie: " << movie << endl;
    cout << "Row: " << row << endl;
    cout << "Seat: " << seat << endl;
    cout << "Cost: $" << cost << endl;
    cout << "Enjoy your movie!\n";

    return cost;
}
